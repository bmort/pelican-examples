#include <pelican/emulator/EmulatorDriver.h>
#include <pelican/utility/ConfigNode.h>
#include <pelican/utility/Config.h>

#include "StreamDataEmulator.hpp"
#include "ServiceDataEmulator.hpp"

#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QObject>

using pelican::ConfigNode;
using pelican::EmulatorDriver;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    int streamInterval = 50000;
    int serviceInterval = streamInterval * 20;

    ConfigNode service_config(QString(
            "<ServiceDataEmulator>"
            "    <packet samples=\"200\" interval=\"%1\" />"
            "    <data period=\"3\" numPackets=\"2\" />"
            "    <connection host=\"127.0.0.1\" port=\"2002\" />"
            "</ServiceDataEmulator>").arg(serviceInterval)
    );
    EmulatorDriver serviceDriver(new ServiceDataEmulator(service_config));

    // This sleep ensures the a service packet arrives at the server first.
    sleep(1);

    ConfigNode stream_config(QString(
            "<StreamDataEmulator>"
            "    <packet samples=\"1000\" interval=\"%1\" />"
            "    <data period=\"13\" numPackets=\"20\" />"
            "    <connection host=\"127.0.0.1\" port=\"2001\" />"
            "</StreamDataEmulator>").arg(streamInterval)
    );
    EmulatorDriver streamDriver(new StreamDataEmulator(stream_config));


//    QObject::connect(&streamDriver, SIGNAL(finished()), &app, SLOT(quit()));

    return app.exec();
}

