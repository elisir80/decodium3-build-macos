#include "Cloudlog.hpp"

#include <future>
#include <chrono>

#include <QHash>
#include <QString>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QFileInfo>
#include <QPointer>
#include <QSaveFile>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QCoreApplication>

#include "pimpl_impl.hpp"

#include "moc_Cloudlog.cpp"

#include "Configuration.hpp"

namespace
{
  // Dictionary mapping call sign to date of last upload to LotW
  using dictionary = QHash<QString, QDate>;
  constexpr qint64 kMaxCloudlogReplyBytes = 64 * 1024;

  QUrl ensure_https_cloudlog_url (QString base, QString const& endpoint_path, QString * error = nullptr)
  {
    base = base.trimmed ();
    if (base.isEmpty ())
      {
        if (error) *error = QObject::tr ("Cloudlog URL is empty");
        return {};
      }

    if (!base.contains ("://"))
      {
        base.prepend ("https://");
      }

    QUrl endpoint {base};
    if (!endpoint.isValid () || endpoint.host ().isEmpty ())
      {
        if (error) *error = QObject::tr ("Cloudlog URL is invalid: %1").arg (base);
        return {};
      }

    endpoint.setScheme ("https");
    endpoint.setPath ("/index.php/api/" + endpoint_path);
    return endpoint;
  }
}

class Cloudlog::impl final
  : public QObject
{
  Q_OBJECT

public:
  impl (Cloudlog * self, Configuration const * config, QNetworkAccessManager * network_manager)
    : self_ {self}
    , config_ {config}
    , network_manager_ {network_manager}
  {
  }

  void logQso (QByteArray ADIF)
  {
    QString url_error;
    QUrl const u = ensure_https_cloudlog_url (config_->cloudlog_api_url (), "qso", &url_error);
    if (!u.isValid ())
      {
        qWarning () << "Cloudlog upload aborted:" << url_error;
        return;
      }

    QJsonObject payload;
    payload.insert ("key", config_->cloudlog_api_key ());
    payload.insert ("station_profile_id", QVariant (config_->cloudlog_api_station_id ()).toString ());
    payload.insert ("type", "adif");
    payload.insert ("string", QString::fromUtf8 (ADIF) + "<eor>");
    QByteArray const data = QJsonDocument (payload).toJson (QJsonDocument::Compact);

    QNetworkRequest request {u};
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    reply_ = network_manager_->post(request, data);
    connect (reply_.data (), &QNetworkReply::finished, this, &Cloudlog::impl::reply_logqso);

  }

  void testApi (QString const& url, QString const& apiKey)
  {
    QString apiUrl = url;
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
    if (QNetworkAccessManager::Accessible != network_manager_->networkAccessible ())
      {
        // try and recover network access for QNAM
        network_manager_->setNetworkAccessible (QNetworkAccessManager::Accessible);
      }
#endif

    QString url_error;
    QUrl endpoint = ensure_https_cloudlog_url (apiUrl, "auth/" + QString::fromLatin1 (QUrl::toPercentEncoding (apiKey)), &url_error);
    if (!endpoint.isValid ())
      {
        qWarning () << "Cloudlog API test aborted:" << url_error;
        Q_EMIT self_->apikey_invalid ();
        return;
      }

    QNetworkRequest request {endpoint};
    request.setRawHeader ("User-Agent", "Decodium3SE-KP5 Cloudlog API");
    request.setOriginatingObject (this);
    reply_ = network_manager_->get (request);
    connect (reply_.data (), &QNetworkReply::finished, this, &Cloudlog::impl::reply_apitest);
  }

  void reply_apitest()
  {
    QString result;
    if (reply_ && reply_->isFinished ())
      {
        auto const length_header = reply_->header (QNetworkRequest::ContentLengthHeader);
        if (length_header.isValid () && length_header.toLongLong () > kMaxCloudlogReplyBytes)
          {
            qWarning () << "Cloudlog API reply too large";
            reply_->abort ();
            return;
          }
        auto body = reply_->read (kMaxCloudlogReplyBytes + 1);
        if (body.size () > kMaxCloudlogReplyBytes)
          {
            qWarning () << "Cloudlog API reply exceeds limit";
            reply_->abort ();
            return;
          }
        result = QString::fromUtf8 (body);
        if (result.contains("<status>Valid</status>"))
          {
            if (result.contains("<rights>rw</rights>"))
              {
                // fprintf(stderr, "API key OK\n");
                Q_EMIT self_->apikey_ok ();
              } else {
                // fprintf(stderr, "API key not writable!\n");
		Q_EMIT self_->apikey_ro ();
              }
          } else {
            // fprintf(stderr, "API key invalid!\n");
	    Q_EMIT self_->apikey_invalid ();
          }
      }
  }

  void reply_logqso()
  {
    QString result;
    if (reply_ && reply_->isFinished ())
      {
        auto const length_header = reply_->header (QNetworkRequest::ContentLengthHeader);
        if (length_header.isValid () && length_header.toLongLong () > kMaxCloudlogReplyBytes)
          {
            qWarning () << "Cloudlog upload reply too large";
            reply_->abort ();
            return;
          }
        auto body = reply_->read (kMaxCloudlogReplyBytes + 1);
        if (body.size () > kMaxCloudlogReplyBytes)
          {
            qWarning () << "Cloudlog upload reply exceeds limit";
            reply_->abort ();
            return;
          }
        result = QString::fromUtf8 (body);
        QJsonDocument data = QJsonDocument::fromJson(result.toUtf8());
        QJsonObject obj = data.object();
        if (obj["status"] == "failed") {
          auto * msgBox = new QMessageBox {QMessageBox::Warning,
                                           tr ("Cloudlog Error!"),
                                           tr ("QSO could not be sent to Cloudlog!\nPlease check your log.")};
          msgBox->setAttribute (Qt::WA_DeleteOnClose, true);
          msgBox->setDetailedText (tr ("Reason: %1").arg (obj["reason"].toString ()));
          msgBox->open ();
        }
      }
  }

  void abort ()
  {
    if (reply_ && reply_->isRunning ())
      {
        reply_->abort ();
      }
  }

  Cloudlog * self_;
  Configuration const * config_;
  QNetworkAccessManager * network_manager_;
  QPointer<QNetworkReply> reply_;
};

#include "Cloudlog.moc"

Cloudlog::Cloudlog (Configuration const * config, QNetworkAccessManager * network_manager, QObject * parent)
  : QObject {parent}
  , m_ {this, config, network_manager}
{
}

Cloudlog::~Cloudlog ()
{
}

void Cloudlog::testApi (QString const& url, QString const& apiKey)
{
  m_->testApi (url, apiKey);
}

void Cloudlog::logQso (QByteArray ADIF)
{
  m_->logQso(ADIF);
}
