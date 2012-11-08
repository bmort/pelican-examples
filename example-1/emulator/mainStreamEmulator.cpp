#include <pelican/emulator/EmulatorDriver.h>
#include <pelican/utility/ConfigNode.h>
#include <pelican/utility/Config.h>

#include "StreamDataEmulator.hpp"

#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QObject>

using pelican::ConfigNode;
using pelican::EmulatorDriver;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    int packetInterval = 50000;
    int numPackets = 5;
    int numSamplesPerPacket = 1000;
    int sampleRepeatPeriod=13;

    ConfigNode stream_config(QString(
            "<StreamDataEmulator>"
            "    <packet samples=\"%1\" interval=\"%2\" />"
            "    <data period=\"%3\" numPackets=\"%5\" />"
            "    <connection host=\"127.0.0.1\" port=\"2001\" />"
            "</StreamDataEmulator>")
            .arg(numSamplesPerPacket)
            .arg(packetInterval)
            .arg(sampleRepeatPeriod)
            .arg(numPackets)
    );
    EmulatorDriver streamDriver(new StreamDataEmulator(stream_config));

    QObject::connect(&streamDriver, SIGNAL(finished()), &app, SLOT(quit()));

    return app.exec();
}

