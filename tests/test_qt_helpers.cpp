#include <QtTest>
#include <QDateTime>
#include <QDebug>

#include "otpgenerator.h"
#include "qt_helpers.hpp"

class TestQtHelpers
  : public QObject
{
  Q_OBJECT

public:

private:
  Q_SLOT void round_15s_date_time_up ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 22, 500}};
    QCOMPARE (qt_round_date_time_to (dt, 15000), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 30)));
  }

  Q_SLOT void truncate_15s_date_time_up ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 22, 500}};
    QCOMPARE (qt_truncate_date_time_to (dt, 15000), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 15)));
  }

  Q_SLOT void round_15s_date_time_down ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 22, 499}};
    QCOMPARE (qt_round_date_time_to (dt, 15000), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 15)));
  }

  Q_SLOT void truncate_15s_date_time_down ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 22, 499}};
    QCOMPARE (qt_truncate_date_time_to (dt, 15000), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 15)));
  }

  Q_SLOT void round_15s_date_time_on ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 15}};
    QCOMPARE (qt_round_date_time_to (dt, 15000), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 15)));
  }

  Q_SLOT void truncate_15s_date_time_on ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 15}};
    QCOMPARE (qt_truncate_date_time_to (dt, 15000), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 15)));
  }

  Q_SLOT void round_15s_date_time_under ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 14, 999}};
    QCOMPARE (qt_round_date_time_to (dt, 15000), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 15)));
  }

  Q_SLOT void truncate_15s_date_time_under ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 14, 999}};
    QCOMPARE (qt_truncate_date_time_to (dt, 15000), QDateTime (QDate (2020, 8, 6), QTime (14, 15)));
  }

  Q_SLOT void round_15s_date_time_over ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 15, 1}};
    QCOMPARE (qt_round_date_time_to (dt, 15000), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 15)));
  }

  Q_SLOT void truncate_15s_date_time_over ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 15, 1}};
    QCOMPARE (qt_truncate_date_time_to (dt, 15000), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 15)));
  }

  Q_SLOT void round_7p5s_date_time_up ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 26, 250}};
    QCOMPARE (qt_round_date_time_to (dt, 7500), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 30)));
  }

  Q_SLOT void truncate_7p5s_date_time_up ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 26, 250}};
    QCOMPARE (qt_truncate_date_time_to (dt, 7500), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 22, 500)));
  }

  Q_SLOT void round_7p5s_date_time_down ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 26, 249}};
    QCOMPARE (qt_round_date_time_to (dt, 7500), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 22, 500)));
  }

  Q_SLOT void truncate_7p5s_date_time_down ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 26, 249}};
    QCOMPARE (qt_truncate_date_time_to (dt, 7500), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 22, 500)));
  }

  Q_SLOT void round_7p5s_date_time_on ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 22, 500}};
    QCOMPARE (qt_round_date_time_to (dt, 7500), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 22, 500)));
  }

  Q_SLOT void truncate_7p5s_date_time_on ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 22, 500}};
    QCOMPARE (qt_truncate_date_time_to (dt, 7500), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 22, 500)));
  }

  Q_SLOT void round_7p5s_date_time_under ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 22, 499}};
    QCOMPARE (qt_round_date_time_to (dt, 7500), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 22, 500)));
  }

  Q_SLOT void truncate_7p5s_date_time_under ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 22, 499}};
    QCOMPARE (qt_truncate_date_time_to (dt, 7500), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 15)));
  }

  Q_SLOT void round_7p5s_date_time_over ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 22, 501}};
    QCOMPARE (qt_round_date_time_to (dt, 7500), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 22, 500)));
  }

  Q_SLOT void truncate_7p5s_date_time_over ()
  {
    QDateTime dt {QDate {2020, 8, 6}, QTime {14, 15, 22, 501}};
    QCOMPARE (qt_truncate_date_time_to (dt, 7500), QDateTime (QDate (2020, 8, 6), QTime (14, 15, 22, 500)));
  }

  Q_SLOT void is_multicast_address_data ()
  {
    QTest::addColumn<QString> ("addr");
    QTest::addColumn<bool> ("result");

    QTest::newRow ("loopback") << "127.0.0.1" << false;
    QTest::newRow ("looback IPv6") << "::1" << false;
    QTest::newRow ("lowest-") << "223.255.255.255" << false;
    QTest::newRow ("lowest") << "224.0.0.0" << true;
    QTest::newRow ("lowest- IPv6") << "feff:ffff:ffff:ffff:ffff:ffff:ffff:ffff" << false;
    QTest::newRow ("lowest IPv6") << "ff00::" << true;
    QTest::newRow ("highest") << "239.255.255.255" << true;
    QTest::newRow ("highest+") << "240.0.0.0" << false;
    QTest::newRow ("highest IPv6") << "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff" << true;
  }

  Q_SLOT void is_multicast_address ()
  {
    QFETCH (QString, addr);
    QFETCH (bool, result);

    QCOMPARE (::is_multicast_address (QHostAddress {addr}), result);
  }

  Q_SLOT void is_MAC_ambiguous_multicast_address_data ()
  {
    QTest::addColumn<QString> ("addr");
    QTest::addColumn<bool> ("result");

    QTest::newRow ("loopback") << "127.0.0.1" << false;
    QTest::newRow ("looback IPv6") << "::1" << false;

    QTest::newRow ("lowest- R1") << "223.255.255.255" << false;
    QTest::newRow ("lowest R1") << "224.0.0.0" << false;
    QTest::newRow ("highest R1") << "224.0.0.255" << false;
    QTest::newRow ("highest+ R1") << "224.0.1.0" << false;
    QTest::newRow ("lowest- R1A") << "224.127.255.255" << false;
    QTest::newRow ("lowest R1A") << "224.128.0.0" << true;
    QTest::newRow ("highest R1A") << "224.128.0.255" << true;
    QTest::newRow ("highest+ R1A") << "224.128.1.0" << false;

    QTest::newRow ("lowest- R2") << "224.255.255.255" << false;
    QTest::newRow ("lowest R2") << "225.0.0.0" << true;
    QTest::newRow ("highest R2") << "225.0.0.255" << true;
    QTest::newRow ("highest+ R2") << "225.0.1.0" << false;
    QTest::newRow ("lowest- R2A") << "225.127.255.255" << false;
    QTest::newRow ("lowest R2A") << "225.128.0.0" << true;
    QTest::newRow ("highest R2A") << "225.128.0.255" << true;
    QTest::newRow ("highest+ R2A") << "225.128.1.0" << false;

    QTest::newRow ("lowest- R3") << "238.255.255.255" << false;
    QTest::newRow ("lowest R3") << "239.0.0.0" << true;
    QTest::newRow ("highest R3") << "239.0.0.255" << true;
    QTest::newRow ("highest+ R3") << "239.0.1.0" << false;
    QTest::newRow ("lowest- R3A") << "239.127.255.255" << false;
    QTest::newRow ("lowest R3A") << "239.128.0.0" << true;
    QTest::newRow ("highest R3A") << "239.128.0.255" << true;
    QTest::newRow ("highest+ R3A") << "239.128.1.0" << false;

    QTest::newRow ("lowest- IPv6") << "feff:ffff:ffff:ffff:ffff:ffff:ffff:ffff" << false;
    QTest::newRow ("lowest IPv6") << "ff00::" << false;
    QTest::newRow ("highest") << "239.255.255.255" << false;
    QTest::newRow ("highest+") << "240.0.0.0" << false;
    QTest::newRow ("highest IPv6") << "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff" << false;
  }

  Q_SLOT void is_MAC_ambiguous_multicast_address ()
  {
    QFETCH (QString, addr);
    QFETCH (bool, result);

    QCOMPARE (::is_MAC_ambiguous_multicast_address (QHostAddress {addr}), result);
  }

  Q_SLOT void hotp_rfc_4226_vectors ()
  {
    OTPGenerator generator;
    QByteArray const secret {"12345678901234567890"};
    QStringList const expected {
      "755224",
      "287082",
      "359152",
      "969429",
      "338314",
      "254676",
      "287922",
      "162583",
      "399871",
      "520489",
    };

    for (int counter = 0; counter < expected.size (); ++counter) {
      QCOMPARE (QString::fromLatin1 (generator.generateHOTP (secret, counter, 6)), expected.at (counter));
    }
  }

  Q_SLOT void totp_rfc_6238_sha1_vectors ()
  {
    OTPGenerator generator;
    QString const secret {"GEZDGNBVGY3TQOJQGEZDGNBVGY3TQOJQ"};

    struct TotpVector
    {
      qint64 seconds;
      char const * expected;
    };

    TotpVector const vectors[] {
      {59, "94287082"},
      {1111111109, "07081804"},
      {1111111111, "14050471"},
      {1234567890, "89005924"},
      {2000000000, "69279037"},
      {20000000000LL, "65353130"},
    };

    for (auto const& vector : vectors) {
      QDateTime const dt = QDateTime::fromSecsSinceEpoch (vector.seconds, Qt::UTC);
      QCOMPARE (generator.generateTOTP (secret, dt, 8), QString::fromLatin1 (vector.expected));
    }
  }

  Q_SLOT void totp_rfc_6238_sha256_vectors ()
  {
    OTPGenerator generator;
    QByteArray const secret {"12345678901234567890123456789012"};

    struct TotpVector
    {
      qint64 seconds;
      char const * expected;
    };

    TotpVector const vectors[] {
      {59, "46119246"},
      {1111111109, "68084774"},
      {1111111111, "67062674"},
      {1234567890, "91819424"},
      {2000000000, "90698825"},
      {20000000000LL, "77737706"},
    };

    for (auto const& vector : vectors) {
      QDateTime const dt = QDateTime::fromSecsSinceEpoch (vector.seconds, Qt::UTC);
      QCOMPARE (QString::fromLatin1 (generator.generateTOTP (secret, dt, 8, QCryptographicHash::Sha256)),
                QString::fromLatin1 (vector.expected));
    }
  }

  Q_SLOT void totp_rfc_6238_sha512_vectors ()
  {
    OTPGenerator generator;
    QByteArray const secret {"1234567890123456789012345678901234567890123456789012345678901234"};

    struct TotpVector
    {
      qint64 seconds;
      char const * expected;
    };

    TotpVector const vectors[] {
      {59, "90693936"},
      {1111111109, "25091201"},
      {1111111111, "99943326"},
      {1234567890, "93441116"},
      {2000000000, "38618901"},
      {20000000000LL, "47863826"},
    };

    for (auto const& vector : vectors) {
      QDateTime const dt = QDateTime::fromSecsSinceEpoch (vector.seconds, Qt::UTC);
      QCOMPARE (QString::fromLatin1 (generator.generateTOTP (secret, dt, 8, QCryptographicHash::Sha512)),
                QString::fromLatin1 (vector.expected));
    }
  }
};

QTEST_MAIN (TestQtHelpers);

#include "test_qt_helpers.moc"
