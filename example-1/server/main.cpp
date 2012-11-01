#include <pelican/server/PelicanServer.h>
#include <pelican/comms/PelicanProtocol.h>
#include <pelican/utility/Config.h>

#include "StreamDataChunker.hpp"
#include "ServiceDataChunker.hpp"

#include <QtCore/QCoreApplication>
#include <iostream>

using namespace pelican;
using namespace std;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    if (argc != 2)
    {
        cerr << "Please specify an XML configuration file." << endl;
        return 0;
    }

    QString configFile(argv[1]);
    try
    {
        Config config(configFile);

        PelicanServer server(&config);
//        server.setVerbosity(10000);
//        server.setVerbosity(0);

        server.addStreamChunker("StreamDataChunker");
        server.addServiceChunker("ServiceDataChunker");

        AbstractProtocol* protocol = new PelicanProtocol;
        server.addProtocol(protocol, 2000);

        server.start();

        while (!server.isReady()) {}
        return app.exec();
    }

    catch (const QString& err)
    {
        cerr << "ERROR: " << err.toStdString() << endl;
    }

    return 0;
}
