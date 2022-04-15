#include <iostream>
#include "networklayer.h"

NetworkLayer::NetworkLayer(QNetworkAccessManager &netwokManager): QObject(), _networkManager(netwokManager) {}

void NetworkLayer::makeWeatherRequest(const WeatherRequestData &data)
{
    /* Настраиваем запрос */
    QUrl url;
    url.setHost("https://wttr.in/Dunedin?2");
    url.setPath(QString(data.regionName.c_str()));
    url.setQuery(QString("?") + data.dayFromNow);
    QNetworkRequest request(url);
    /* Можно также передать body, зоголовки*/

    /* Отправляем get запрос */
    auto reply = _networkManager.get(request);

    /* Устанавливаем callback который вызовется после получения ответа */
    connect(reply, &QNetworkReply::finished, [this]() {
        onWeatherReply(static_cast<QNetworkReply *>(sender()));
    });

}

void NetworkLayer::onWeatherReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        std::cout << "Запрос не удался" << std::endl;
        return;
    }

    /* body ответа (тут может быть буфер с json)*/
    auto forecastData = reply->readAll();
    std::cout << forecastData.data() << std::endl;
}
