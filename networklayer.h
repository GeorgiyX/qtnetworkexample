#ifndef NETWORKLAYER_H
#define NETWORKLAYER_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>


struct WeatherRequestData {
    std::string regionName;
    unsigned dayFromNow;
};

class NetworkLayer : public QObject {
    Q_OBJECT

public:

    NetworkLayer(QNetworkAccessManager &network);

    void makeWeatherRequest(const WeatherRequestData &data);
    void onWeatherReply(QNetworkReply *reply);

private:
    QNetworkAccessManager &_networkManager;
};

#endif // NETWORKLAYER_H
