#include <QtCore/QCoreApplication>
#include <pelican/core/PipelineApplication.h>

#include "Pipeline.hpp"
#include "DirectDataClient.hpp"
#include "StreamDataAdapter.hpp"
#include "ServiceDataAdapter.hpp"

#include <iostream>

using namespace std;
using pelican::PipelineApplication;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    if (argc != 2)
    {
        cerr << "Please specify an XML configuration file." << endl;
        return 0;
    }

    try
    {
        PipelineApplication pApp(argc, argv);
        pApp.registerPipeline(new Pipeline);
        pApp.setDataClient("DirectDataClient");
        pApp.start();
    }
    catch (const QString& err)
    {
        cerr << "ERROR: " << err.toStdString() << endl;
    }

    return 0;
}

