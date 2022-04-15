#include <iostream>
#include "networklayer.h"

NetworkLayer::NetworkLayer(QNetworkAccessManager &netwokManager): QObject(), _networkManager(netwokManager) {}

void NetworkLayer::makeWeatherRequest(const WeatherRequestData &data)
{
    /* Настраиваем запрос */
    QUrl url;
    url.setScheme("http");
    url.setHost("wttr.in");
    url.setPath(QString::fromStdString(data.regionName));
    url.setQuery(QString("?") + data.dayFromNow);
    QNetworkRequest request(url);

    /* Отправляем get запрос */
    auto reply = _networkManager.get(request);
    reply->setParent(_networkManager.parent());

    /* Устанавливаем callback который вызовется после получения ответа */
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        onWeatherReply(reply);
    });

}

void NetworkLayer::onWeatherReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        std::cout << "The request failed" << std::endl;
        return;
    }

    /* body ответа (тут может быть буфер с json)*/
    auto forecastData = reply->readAll();
    std::cout << forecastData.data() << std::endl;
}
