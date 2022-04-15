#include <QCoreApplication>
#include "networklayer.h"

#include <QTimer>
#include <QObject>
#include <iostream>



int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QNetworkAccessManager networkManager(&app);
    NetworkLayer networkLayer(networkManager);

    networkLayer.makeWeatherRequest({
                                        "Moscow",
                                        0
                                    });
    QTimer::singleShot(2000, &app, []() {
                          std::cout << "bay" << std::endl;
                      });

    return app.exec();
}
