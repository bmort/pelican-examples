#include <QtCore/QCoreApplication>

#include <pelican/core/PipelineApplication.h>

#include "Pipeline.hpp"
#include "StreamDataAdapter.hpp"
#include "ServiceDataAdapter.hpp"

using namespace std;
using pelican::PipelineApplication;

struct CleanExit
{
  CleanExit()
  {
    signal(SIGINT, &CleanExit::exitQt);
    signal(SIGTERM, &CleanExit::exitQt);
    signal(SIGKILL, &CleanExit::exitQt);
  }

  static void exitQt(int signal)
  {
    QCoreApplication::exit(signal);
  }
};


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    CleanExit cleanExit;

    if (argc != 2)
    {
        cerr << "Please specify an XML configuration file." << endl;
        return 0;
    }

    try
    {
        PipelineApplication pApp(argc, argv);
        pApp.registerPipeline(new Pipeline);
        pApp.setDataClient("PelicanServerClient");
        pApp.start();
    }
    catch (const QString& err)
    {
        cerr << "ERROR: " << err.toStdString() << endl;
    }

    return 0;
}

