// -*- Mode: C++ -*-
#include "NtpClient.hpp"

#include <QDateTime>
#include <QNetworkDatagram>
#include <QNetworkRequest>
#include <QtEndian>
#include <algorithm>
#include <cmath>
#include <random>
#include <QLocale>

namespace
{
  bool env_flag_enabled(char const *name, bool default_value)
  {
    auto const raw = QString::fromLocal8Bit(qgetenv(name)).trimmed().toLower();
    if (raw.isEmpty()) return default_value;
    if (raw == "0" || raw == "false" || raw == "off" || raw == "no") return false;
    if (raw == "1" || raw == "true" || raw == "on" || raw == "yes") return true;
    return default_value;
  }

  double env_double(char const *name, double default_value, double min_value, double max_value)
  {
    bool ok = false;
    auto const raw = QString::fromLocal8Bit(qgetenv(name)).trimmed();
    auto value = raw.toDouble(&ok);
    if (!ok) return default_value;
    return qBound(min_value, value, max_value);
  }

  int env_int(char const *name, int default_value, int min_value, int max_value)
  {
    bool ok = false;
    auto const raw = QString::fromLocal8Bit(qgetenv(name)).trimmed();
    auto value = raw.toInt(&ok);
    if (!ok) return default_value;
    return qBound(min_value, value, max_value);
  }

  double median_of(QVector<double> values)
  {
    if (values.isEmpty()) return 0.0;
    std::sort(values.begin(), values.end());
    int const n = values.size();
    if (n % 2 == 0) {
      return (values[n/2 - 1] + values[n/2]) / 2.0;
    }
    return values[n/2];
  }

  QVector<double> densest_cluster(QVector<double> values, double windowMs)
  {
    if (values.isEmpty()) return {};
    std::sort(values.begin(), values.end());

    int bestStart = 0;
    int bestCount = 1;
    int start = 0;
    for (int end = 0; end < values.size(); ++end) {
      while (values[end] - values[start] > windowMs && start < end) {
        ++start;
      }
      int count = end - start + 1;
      if (count > bestCount) {
        bestCount = count;
        bestStart = start;
      }
    }

    QVector<double> cluster;
    cluster.reserve(bestCount);
    for (int i = 0; i < bestCount; ++i) {
      cluster.append(values[bestStart + i]);
    }
    return cluster;
  }
}

NtpClient::NtpClient(QObject *parent)
  : QObject(parent)
  , m_servers({
      // NTP Pool Project - global
      "0.pool.ntp.org",
      "1.pool.ntp.org",
      "2.pool.ntp.org",
      "3.pool.ntp.org",
      // NTP Pool - Europe
      "0.europe.pool.ntp.org",
      "1.europe.pool.ntp.org",
      "2.europe.pool.ntp.org",
      "3.europe.pool.ntp.org",
      // NIST (USA) - stratum 1
      "time.nist.gov",
      // Google Public NTP - stratum 1, smeared leap seconds
      "time.google.com",
      "time1.google.com",
      "time2.google.com",
      "time3.google.com",
      "time4.google.com",
      // Cloudflare NTP - anycast, low latency
      "time.cloudflare.com",
      // Apple NTP
      "time.apple.com",
      // Microsoft NTP
      "time.windows.com",
      // Facebook/Meta NTP - stratum 1
      "time.facebook.com",
      // European national institutes
      "ntp1.inrim.it",        // INRIM Italy - stratum 1 cesium
      "ntp2.inrim.it",        // INRIM Italy - stratum 1 cesium
      "ptbtime1.ptb.de",      // PTB Germany - stratum 1
      "ptbtime2.ptb.de",      // PTB Germany - stratum 1
      "ptbtime3.ptb.de",      // PTB Germany - stratum 1
      "ntp.ubuntu.com",       // Ubuntu/Canonical
    })
{
  m_weakSyncEnabled = env_flag_enabled("FT2_NTP_WEAK_SYNC", true);
  m_weakDeadbandMs = env_double("FT2_NTP_WEAK_DEADBAND_MS", 20.0, 1.0, 500.0);
  m_weakStrongStepMs = env_double("FT2_NTP_WEAK_STRONG_MS", 350.0, 5.0, 2000.0);
  m_weakEmergencyStepMs = env_double("FT2_NTP_WEAK_EMERGENCY_MS", 2000.0, 200.0, 10000.0);
  m_weakConfirmNeeded = env_int("FT2_NTP_WEAK_CONFIRM", 2, 1, 5);
  m_weakStrongConfirmNeeded = env_int("FT2_NTP_WEAK_STRONG_CONFIRM", 4, 1, 10);
  m_clusterWindowMs = env_double("FT2_NTP_CLUSTER_WINDOW_MS", 180.0, 20.0, 1000.0);
  m_lockWindowMs = env_double("FT2_NTP_LOCK_WINDOW_MS", 180.0, 20.0, 1000.0);
  m_httpLockToleranceMs = env_double("FT2_NTP_HTTP_LOCK_TOL_MS", 220.0, 50.0, 2000.0);
  m_sparseJumpMs = env_double("FT2_NTP_SPARSE_JUMP_MS", 50.0, 10.0, 500.0);
  m_sparseJumpConfirmNeeded = env_int("FT2_NTP_SPARSE_JUMP_CONFIRM", 4, 1, 10);
  m_httpHoldoffMs = env_int("FT2_NTP_HTTP_HOLDOFF_MS", 900000, 60000, 7200000);

  m_refreshTimer.setInterval(REFRESH_INTERVAL_MS);
  connect(&m_refreshTimer, &QTimer::timeout, this, &NtpClient::onRefreshTimeout);

  m_queryTimeoutTimer.setInterval(QUERY_TIMEOUT_MS);
  m_queryTimeoutTimer.setSingleShot(true);
  connect(&m_queryTimeoutTimer, &QTimer::timeout, this, &NtpClient::onQueryTimeout);

  connect(&m_socket, &QUdpSocket::readyRead, this, &NtpClient::onReadyRead);

  // HTTP fallback network manager
  m_nam = new QNetworkAccessManager(this);
  connect(m_nam, &QNetworkAccessManager::finished, this, &NtpClient::onHttpReply);
}

NtpClient::~NtpClient()
{
  m_refreshTimer.stop();
  m_queryTimeoutTimer.stop();
  m_socket.close();
}

void NtpClient::setEnabled(bool enabled)
{
  m_enabled = enabled;
  if (enabled) {
    if (m_socket.state() == QAbstractSocket::UnconnectedState) {
      m_socket.bind();  // bind to any available port
    }
    syncNow();
    m_refreshTimer.start(m_refreshIntervalMs);
  } else {
    m_refreshTimer.stop();
    m_queryTimeoutTimer.stop();
    m_pendingQueries.clear();
    m_collectedOffsets.clear();
    m_httpOffsets.clear();
    m_httpSendTimes.clear();
    m_httpPendingCount = 0;
    m_pendingDnsLookups = 0;
    m_activeLookupIds.clear();
    m_queriedAddresses.clear();
    m_synced = false;
    resetWeakSyncState();
    resetSparseJumpState();
    m_lastGoodSyncMs = 0;
    m_socket.close();
  }
}

void NtpClient::setInitialOffset(double offsetMs)
{
  m_offsetMs = offsetMs;
  // Seed from last session, but allow the first live sync sample to re-lock immediately.
  m_hasOffsetLock = false;
  resetWeakSyncState();
  resetSparseJumpState();
}

void NtpClient::setCustomServer(QString const& server)
{
  m_customServer = server.trimmed();
}

void NtpClient::setRefreshInterval(int ms)
{
  m_refreshIntervalMs = qBound(10000, ms, 300000);
  if (m_refreshTimer.isActive()) {
    m_refreshTimer.start(m_refreshIntervalMs);
  }
}

void NtpClient::syncNow()
{
  if (!m_enabled) return;

  m_pendingQueries.clear();
  m_collectedOffsets.clear();
  m_httpOffsets.clear();
  m_httpSendTimes.clear();
  m_httpPendingCount = 0;
  m_pendingDnsLookups = 0;
  m_activeLookupIds.clear();
  m_queriedAddresses.clear();

  // Select a random subset of servers (max 8) to avoid overloading
  QStringList selected = m_servers;
  std::random_device rd;
  std::mt19937 rng(rd());
  std::shuffle(selected.begin(), selected.end(), rng);

  // Optional preferred server (queried first).
  if (!m_customServer.isEmpty()) {
    selected.removeAll(m_customServer);
    selected.prepend(m_customServer);
  }

  int queryCount = qMin(selected.size(), SERVERS_PER_QUERY);

  // Start async DNS lookup for selected servers
  for (int i = 0; i < queryCount; ++i) {
    ++m_pendingDnsLookups;
    auto lookup_id = QHostInfo::lookupHost(selected[i], this, SLOT(onDnsLookupResult(QHostInfo)));
    m_activeLookupIds.insert(lookup_id);
  }
}

void NtpClient::onDnsLookupResult(QHostInfo hostInfo)
{
  if (!m_activeLookupIds.contains(hostInfo.lookupId())) {
    return;
  }
  m_activeLookupIds.remove(hostInfo.lookupId());
  --m_pendingDnsLookups;

  if (hostInfo.error() != QHostInfo::NoError) {
    Q_EMIT errorOccurred(QString("DNS lookup failed for %1: %2")
                         .arg(hostInfo.hostName(), hostInfo.errorString()));
  } else {
    auto const addresses = hostInfo.addresses();
    if (!addresses.isEmpty()) {
      // Prefer IPv4 on macOS because some environments resolve many NTP hosts
      // to IPv6 endpoints that are not reachable from the current socket path.
      QHostAddress selectedAddress;
      for (auto const& address : addresses) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) {
          selectedAddress = address;
          break;
        }
      }
      if (selectedAddress.isNull()) {
        selectedAddress = addresses.first();
      }
      sendQuery(selectedAddress);
      // Start timeout timer when first query is sent
      if (!m_queryTimeoutTimer.isActive()) {
        m_queryTimeoutTimer.start();
      }
    }
  }

  // If all lookups are done and no UDP query is pending, finalize now
  // so we can move promptly to HTTP fallback.
  if (m_pendingDnsLookups <= 0
      && m_pendingQueries.isEmpty()
      && m_collectedOffsets.isEmpty()
      && !m_queryTimeoutTimer.isActive()) {
    onQueryTimeout();
  }
}

void NtpClient::sendQuery(QHostAddress const& address)
{
  auto key = address.toString();
  if (m_queriedAddresses.contains(key)) {
    return;
  }
  m_queriedAddresses.insert(key);

  QByteArray packet(NTP_PACKET_SIZE, '\0');
  packet[0] = 0x23;  // LI=0, VN=4, Mode=3 (client)

  // Record T1 (client send time)
  qint64 t1Ms = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();

  // Write T1 into Transmit Timestamp (bytes 40-47).
  quint32 t1Sec, t1Frac;
  msToNtpTimestamp(t1Ms, t1Sec, t1Frac);
  qToBigEndian(t1Sec, reinterpret_cast<uchar*>(packet.data() + 40));
  qToBigEndian(t1Frac, reinterpret_cast<uchar*>(packet.data() + 44));

  PendingQuery pq;
  pq.t1Ms = t1Ms;
  pq.t1Sec = t1Sec;
  pq.t1Frac = t1Frac;
  m_pendingQueries.insert(key, pq);

  m_socket.writeDatagram(packet, address, NTP_PORT);
}

void NtpClient::onReadyRead()
{
  while (m_socket.hasPendingDatagrams()) {
    QNetworkDatagram datagram = m_socket.receiveDatagram();
    QByteArray data = datagram.data();

    // Validate packet size
    if (data.size() < NTP_PACKET_SIZE) continue;

    // Record T4 (client receive time)
    qint64 t4Ms = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();

    QString senderKey = datagram.senderAddress().toString();
    if (!m_pendingQueries.contains(senderKey)) continue;

    qint64 t1Ms = m_pendingQueries.value(senderKey).t1Ms;
    quint32 sentT1Sec = m_pendingQueries.value(senderKey).t1Sec;
    quint32 sentT1Frac = m_pendingQueries.value(senderKey).t1Frac;
    m_pendingQueries.remove(senderKey);

    // Validate stratum (byte 1): must be 1-15
    quint8 stratum = static_cast<quint8>(data[1]);
    if (stratum == 0 || stratum > 15) continue;

    // Extract T2 (server receive timestamp, bytes 32-39)
    quint32 t2Sec = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(data.constData() + 32));
    quint32 t2Frac = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(data.constData() + 36));

    // Extract T3 (server transmit timestamp, bytes 40-47)
    quint32 t3Sec = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(data.constData() + 40));
    quint32 t3Frac = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(data.constData() + 44));

    // Validate originate timestamp echoed by server (bytes 24-31).
    quint32 t1EchoSec = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(data.constData() + 24));
    quint32 t1EchoFrac = qFromBigEndian<quint32>(reinterpret_cast<const uchar*>(data.constData() + 28));
    if (t1EchoSec != sentT1Sec || t1EchoFrac != sentT1Frac) continue;

    double t2Ms = ntpTimestampToMs(t2Sec, t2Frac);
    double t3Ms = ntpTimestampToMs(t3Sec, t3Frac);

    // Calculate offset: ((T2-T1) + (T3-T4)) / 2
    double offset = ((t2Ms - t1Ms) + (t3Ms - t4Ms)) / 2.0;
    double rtt = (t4Ms - t1Ms) - (t3Ms - t2Ms);

    if (rtt > m_maxRttMs) continue;

    // Sanity gate: discard offsets > 1 hour
    if (std::abs(offset) > MAX_OFFSET_MS) continue;

    m_collectedOffsets.append(offset);

    // If all responses received, compute result immediately
    if (m_pendingQueries.isEmpty()) {
      m_queryTimeoutTimer.stop();
      onQueryTimeout();  // reuse the same finalization logic
    }
  }
}

void NtpClient::onRefreshTimeout()
{
  syncNow();
}

void NtpClient::onQueryTimeout()
{
  m_queryTimeoutTimer.stop();
  m_pendingQueries.clear();
  m_activeLookupIds.clear();

  if (m_collectedOffsets.isEmpty()) {
    // NTP failed — track consecutive failures
    ++m_ntpConsecutiveFailures;
    if (m_ntpConsecutiveFailures >= 3) {
      auto const nowMs = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
      bool const holdByRecentLock =
          m_hasOffsetLock
          && (m_lastGoodSyncMs <= 0 || (nowMs - m_lastGoodSyncMs) < m_httpHoldoffMs);

      if (holdByRecentLock) {
        m_synced = true;
        Q_EMIT syncStatusChanged(
            true,
            QString("NTP hold: no response (%1), keeping %2 ms; HTTP fallback delayed")
                .arg(m_ntpConsecutiveFailures)
                .arg(m_offsetMs, 0, 'f', 1));
      } else {
        m_synced = false;
        Q_EMIT syncStatusChanged(false, "NTP: no response from servers");
        // After repeated failures, try HTTP fallback as last resort.
        httpTimeFallback();
      }
    } else {
      bool const holdingLock = m_hasOffsetLock;
      m_synced = holdingLock;
      Q_EMIT syncStatusChanged(holdingLock, QString("NTP hold: no response this cycle (%1/3), keeping %2 ms")
                               .arg(m_ntpConsecutiveFailures)
                               .arg(m_offsetMs, 0, 'f', 1));
    }

    // Use faster retry interval when not synced
    m_refreshTimer.setInterval(REFRESH_RETRY_MS);
    return;
  }

  // NTP succeeded — reset failure counter
  m_ntpConsecutiveFailures = 0;

  QVector<double> coherent = m_collectedOffsets;
  if (coherent.size() >= 3) {
    auto cluster = densest_cluster(coherent, m_clusterWindowMs);
    if (cluster.size() >= 2 && cluster.size() < coherent.size()) {
      coherent = cluster;
    }
  }

  if (m_hasOffsetLock && coherent.size() >= 2) {
    QVector<double> nearLock;
    for (auto const& v : coherent) {
      if (std::abs(v - m_offsetMs) <= m_lockWindowMs) {
        nearLock.append(v);
      }
    }
    if (nearLock.size() >= 2) {
      coherent = nearLock;
    }
  }

  int n = coherent.size();
  double median = median_of(coherent);

  if (n >= 3) {
    auto minmax = std::minmax_element(coherent.begin(), coherent.end());
    double range = *minmax.second - *minmax.first;
    if (range > (m_clusterWindowMs * 1.5)) {
      Q_EMIT syncStatusChanged(true, QString("NTP hold: incoherent set (range %1 ms), keeping %2 ms")
                               .arg(range, 0, 'f', 1)
                               .arg(m_offsetMs, 0, 'f', 1));
      return;
    }
  }

  if (m_hasOffsetLock) {
    double const deltaFromLock = std::abs(median - m_offsetMs);
    if (deltaFromLock > (m_httpLockToleranceMs * 2.0) && n < 4) {
      Q_EMIT syncStatusChanged(
          true,
          QString("NTP hold: large jump %1 ms with only %2 servers, keeping %3 ms")
              .arg(deltaFromLock, 0, 'f', 1)
              .arg(n)
              .arg(m_offsetMs, 0, 'f', 1));
      return;
    }

    // With sparse server sets (2-3), require repeated confirmations for medium jumps.
    if (n <= 3 && deltaFromLock >= m_sparseJumpMs) {
      int const direction = (median - m_offsetMs) > 0.0 ? 1 : -1;
      if (direction == m_sparseJumpDirection) {
        ++m_sparseJumpConfirmCount;
      } else {
        m_sparseJumpDirection = direction;
        m_sparseJumpConfirmCount = 1;
      }
      if (m_sparseJumpConfirmCount < m_sparseJumpConfirmNeeded) {
        Q_EMIT syncStatusChanged(
            true,
            QString("NTP hold: sparse jump pending %1/%2 (delta %3 ms, %4 srv), keeping %5 ms")
                .arg(m_sparseJumpConfirmCount)
                .arg(m_sparseJumpConfirmNeeded)
                .arg(median - m_offsetMs, 0, 'f', 1)
                .arg(n)
                .arg(m_offsetMs, 0, 'f', 1));
        return;
      }
      resetSparseJumpState();
    } else {
      resetSparseJumpState();
    }
  } else {
    resetSparseJumpState();
  }

  m_synced = true;
  m_lastServerCount = n;
  m_lastGoodSyncMs = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();

  // Restore normal refresh interval after successful sync
  m_refreshTimer.setInterval(m_refreshIntervalMs);

  QString weak_reason;
  if (weakSyncShouldApply(median, &weak_reason)) {
    m_offsetMs = median;
    m_hasOffsetLock = true;
    Q_EMIT offsetUpdated(m_offsetMs);
    Q_EMIT syncStatusChanged(true, QString("NTP synced: %1 servers, offset %2 ms%3")
                             .arg(n)
                             .arg(median, 0, 'f', 1)
                             .arg(weak_reason.isEmpty() ? QString{} : QString(" [%1]").arg(weak_reason)));
  } else {
    Q_EMIT syncStatusChanged(true, QString("NTP weak-sync hold: %1 servers, candidate %2 ms, active %3 ms [%4]")
                             .arg(n)
                             .arg(median, 0, 'f', 1)
                             .arg(m_offsetMs, 0, 'f', 1)
                             .arg(weak_reason));
  }
}

// ---- HTTP Time Fallback ----
// When UDP NTP (port 123) is blocked by firewall, use HTTP HEAD requests
// to get approximate time from the Date header. Accuracy ~200-500ms.
void NtpClient::httpTimeFallback()
{
  if (!m_enabled) return;

  // HTTP time sources — port 80/443 almost never blocked
  static const QStringList httpServers = {
    "https://www.google.com",
    "https://www.cloudflare.com",
    "https://www.microsoft.com",
    "https://www.apple.com",
  };

  m_httpOffsets.clear();
  m_httpPendingCount = httpServers.size();

  for (const auto &url : httpServers) {
    QNetworkRequest req{QUrl{url}};
    req.setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                     QNetworkRequest::NoLessSafeRedirectPolicy);
    // Record send time
    QNetworkReply *reply = m_nam->head(req);
    m_httpSendTimes.insert(reply, QDateTime::currentDateTimeUtc().toMSecsSinceEpoch());
    // Timeout individual requests after 5s
    QTimer::singleShot(5000, reply, [reply]() {
      if (reply->isRunning()) reply->abort();
    });
  }
}

void NtpClient::onHttpReply(QNetworkReply *reply)
{
  reply->deleteLater();
  --m_httpPendingCount;

  qint64 t4Ms = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();

  if (reply->error() == QNetworkReply::NoError && m_httpSendTimes.contains(reply)) {
    qint64 t1Ms = m_httpSendTimes.value(reply);
    m_httpSendTimes.remove(reply);

    // Parse Date header: "Mon, 17 Feb 2026 14:30:00 GMT"
    QByteArray dateHeader = reply->rawHeader("Date");
    if (!dateHeader.isEmpty()) {
      // Try RFC 2822 format
      QDateTime serverTime = QLocale::c().toDateTime(
        QString::fromLatin1(dateHeader).trimmed(),
        "ddd, dd MMM yyyy HH:mm:ss 'GMT'");
      serverTime.setTimeSpec(Qt::UTC);

      if (serverTime.isValid()) {
        qint64 serverMs = serverTime.toMSecsSinceEpoch();
        qint64 rtt = t4Ms - t1Ms;
        // Estimate: server time corresponds to midpoint of round-trip
        double offset = static_cast<double>(serverMs) - static_cast<double>(t1Ms + rtt / 2);
        // HTTP Date has 1-second resolution, so only trust offsets within 1 hour
        if (std::abs(offset) < MAX_OFFSET_MS) {
          m_httpOffsets.append(offset);
        }
      }
    }
  } else {
    m_httpSendTimes.remove(reply);
  }

  // All HTTP replies received — compute result
  if (m_httpPendingCount <= 0) {
    if (!m_httpOffsets.isEmpty()) {
      int n = m_httpOffsets.size();
      double median = median_of(m_httpOffsets);

      if (m_hasOffsetLock) {
        if (n < 3) {
          m_synced = true;
          Q_EMIT syncStatusChanged(
              true,
              QString("HTTP hold: only %1 server(s), keeping locked %2 ms")
                  .arg(n)
                  .arg(m_offsetMs, 0, 'f', 1));
        } else {
          double const deltaFromLock = std::abs(median - m_offsetMs);
          if (deltaFromLock > m_httpLockToleranceMs) {
            m_synced = true;
            Q_EMIT syncStatusChanged(
                true,
                QString("HTTP hold: coarse jump %1 ms exceeds tolerance %2 ms, keeping %3 ms")
                    .arg(deltaFromLock, 0, 'f', 1)
                    .arg(m_httpLockToleranceMs, 0, 'f', 0)
                    .arg(m_offsetMs, 0, 'f', 1));
          } else {
            m_synced = true;
            m_ntpConsecutiveFailures = 0;
            m_lastServerCount = n;
            m_lastGoodSyncMs = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
            m_refreshTimer.setInterval(m_refreshIntervalMs);
            QString weak_reason;
            if (weakSyncShouldApply(median, &weak_reason)) {
              m_offsetMs = median;
              m_hasOffsetLock = true;
              Q_EMIT offsetUpdated(m_offsetMs);
              Q_EMIT syncStatusChanged(true, QString("HTTP time sync: %1 servers, offset %2 ms%3")
                                       .arg(n)
                                       .arg(median, 0, 'f', 0)
                                       .arg(weak_reason.isEmpty() ? QString{} : QString(" [%1]").arg(weak_reason)));
            } else {
              Q_EMIT syncStatusChanged(true, QString("HTTP weak-sync hold: %1 servers, candidate %2 ms, active %3 ms [%4]")
                                       .arg(n)
                                       .arg(median, 0, 'f', 0)
                                       .arg(m_offsetMs, 0, 'f', 0)
                                       .arg(weak_reason));
            }
          }
        }
      } else {
        m_synced = true;
        m_ntpConsecutiveFailures = 0;
        m_lastServerCount = n;
        m_lastGoodSyncMs = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
        m_refreshTimer.setInterval(m_refreshIntervalMs);
        QString weak_reason;
        if (weakSyncShouldApply(median, &weak_reason)) {
          m_offsetMs = median;
          m_hasOffsetLock = true;
          Q_EMIT offsetUpdated(m_offsetMs);
          Q_EMIT syncStatusChanged(true, QString("HTTP time sync: %1 servers, offset %2 ms%3")
                                   .arg(n)
                                   .arg(median, 0, 'f', 0)
                                   .arg(weak_reason.isEmpty() ? QString{} : QString(" [%1]").arg(weak_reason)));
        } else {
          Q_EMIT syncStatusChanged(true, QString("HTTP weak-sync hold: %1 servers, candidate %2 ms, active %3 ms [%4]")
                                   .arg(n)
                                   .arg(median, 0, 'f', 0)
                                   .arg(m_offsetMs, 0, 'f', 0)
                                   .arg(weak_reason));
        }
      }
    } else {
      if (m_hasOffsetLock) {
        m_synced = true;
        Q_EMIT syncStatusChanged(true, QString("HTTP hold: fallback failed, keeping %1 ms")
                                 .arg(m_offsetMs, 0, 'f', 1));
      } else {
        m_synced = false;
        Q_EMIT syncStatusChanged(false, "HTTP time fallback failed");
      }
    }
    m_httpSendTimes.clear();
  }
}

double NtpClient::ntpTimestampToMs(quint32 seconds, quint32 fraction)
{
  // Convert NTP timestamp (epoch 1900) to milliseconds since Unix epoch (1970)
  qint64 unixSeconds = static_cast<qint64>(seconds) - static_cast<qint64>(NTP_EPOCH_OFFSET);
  double fracMs = static_cast<double>(fraction) * 1000.0 / 4294967296.0;  // 2^32
  return static_cast<double>(unixSeconds) * 1000.0 + fracMs;
}

void NtpClient::msToNtpTimestamp(qint64 msEpoch, quint32 &seconds, quint32 &fraction)
{
  // Convert milliseconds since Unix epoch to NTP timestamp (epoch 1900)
  qint64 sec = msEpoch / 1000;
  qint64 ms = msEpoch % 1000;
  seconds = static_cast<quint32>(sec + static_cast<qint64>(NTP_EPOCH_OFFSET));
  fraction = static_cast<quint32>(static_cast<double>(ms) / 1000.0 * 4294967296.0);  // 2^32
}

void NtpClient::resetWeakSyncState()
{
  m_weakConfirmCount = 0;
  m_weakLastDirection = 0;
}

void NtpClient::resetSparseJumpState()
{
  m_sparseJumpConfirmCount = 0;
  m_sparseJumpDirection = 0;
}

bool NtpClient::weakSyncShouldApply(double candidateOffsetMs, QString *reason)
{
  if (reason) reason->clear();

  if (!m_weakSyncEnabled) {
    if (reason) *reason = "weak-sync disabled";
    return true;
  }

  if (!m_hasOffsetLock) {
    resetWeakSyncState();
    if (reason) *reason = "bootstrap";
    return true;
  }

  auto const delta = candidateOffsetMs - m_offsetMs;
  auto const abs_delta = std::abs(delta);

  if (abs_delta < m_weakDeadbandMs) {
    resetWeakSyncState();
    if (reason) *reason = QString("deadband <%1ms (delta %2ms)")
                             .arg(m_weakDeadbandMs, 0, 'f', 1)
                             .arg(delta, 0, 'f', 1);
    return false;
  }

  if (abs_delta >= m_weakStrongStepMs) {
    if (abs_delta >= m_weakEmergencyStepMs) {
      resetWeakSyncState();
      if (reason) *reason = QString("emergency step >=%1ms (delta %2ms)")
                               .arg(m_weakEmergencyStepMs, 0, 'f', 1)
                               .arg(delta, 0, 'f', 1);
      return true;
    }

    int const direction = delta > 0.0 ? 1 : -1;
    if (direction == m_weakLastDirection) {
      ++m_weakConfirmCount;
    } else {
      m_weakLastDirection = direction;
      m_weakConfirmCount = 1;
    }
    int const needed = qMax(m_weakStrongConfirmNeeded, m_weakConfirmNeeded);
    if (m_weakConfirmCount < needed) {
      if (reason) *reason = QString("pending strong confirm %1/%2 (delta %3ms)")
                               .arg(m_weakConfirmCount)
                               .arg(needed)
                               .arg(delta, 0, 'f', 1);
      return false;
    }

    resetWeakSyncState();
    if (reason) *reason = QString("strong confirmed %1/%2 (delta %3ms)")
                             .arg(needed)
                             .arg(needed)
                             .arg(delta, 0, 'f', 1);
    return true;
  }

  int const direction = delta > 0.0 ? 1 : -1;
  if (direction == m_weakLastDirection) {
    ++m_weakConfirmCount;
  } else {
    m_weakLastDirection = direction;
    m_weakConfirmCount = 1;
  }

  if (m_weakConfirmCount < m_weakConfirmNeeded) {
    if (reason) *reason = QString("pending confirm %1/%2 (delta %3ms)")
                             .arg(m_weakConfirmCount)
                             .arg(m_weakConfirmNeeded)
                             .arg(delta, 0, 'f', 1);
    return false;
  }

  resetWeakSyncState();
  if (reason) *reason = QString("confirmed %1/%2 (delta %3ms)")
                           .arg(m_weakConfirmNeeded)
                           .arg(m_weakConfirmNeeded)
                           .arg(delta, 0, 'f', 1);
  return true;
}
