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

    int interval = 500000;

    // Emulator to generate a stream data signal source
    ConfigNode stream_config(QString(
            "<StreamDataEmulator>"
            "    <packet samples=\"10\" interval=\"%1\" />"
            "    <signal period=\"100\" />"
            "    <connection host=\"127.0.0.1\" port=\"2001\" />"
            "</StreamDataEmulator>").arg(interval)
    );
    EmulatorDriver driver1(new StreamDataEmulator(stream_config));

    // Emulator to generate gains
    ConfigNode service_config(QString(
            "<ServiceDataEmulator>"
            "    <packet interval=\"%1\" />"
            "    <connection host=\"127.0.0.1\" port=\"2002\" />"
            "</ServiceDataEmulator>").arg(interval * 2)
    );
    EmulatorDriver driver2(new ServiceDataEmulator(service_config));
    QObject::connect(&driver2, SIGNAL(finished()), qApp, SLOT(quit()));

    return app.exec();
}

