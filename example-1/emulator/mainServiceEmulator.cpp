#include <pelican/emulator/EmulatorDriver.h>
#include <pelican/utility/ConfigNode.h>
#include <pelican/utility/Config.h>

#include "ServiceDataEmulator.hpp"

#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QObject>

using pelican::ConfigNode;
using pelican::EmulatorDriver;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    int packetInterval = 50000;
    int numPackets = 2;
    int numSamplesPerPacket = 200;
    int sampleRepeatPeriod=3;

    ConfigNode service_config(QString(
            "<ServiceDataEmulator>"
            "    <packet samples=\"%1\" interval=\"%2\" />"
            "    <data period=\"%3\" numPackets=\"%5\" />"
            "    <connection host=\"127.0.0.1\" port=\"2002\" />"
            "</ServiceDataEmulator>")
            .arg(numSamplesPerPacket)
            .arg(packetInterval)
            .arg(sampleRepeatPeriod)
            .arg(numPackets)
    );
    EmulatorDriver serviceDriver(new ServiceDataEmulator(service_config));

    QObject::connect(&serviceDriver, SIGNAL(finished()), &app, SLOT(quit()));

    return app.exec();
}
