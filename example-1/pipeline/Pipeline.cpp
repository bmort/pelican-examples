#include "Pipeline.hpp"
#include "StreamData.hpp"
#include "ServiceData.hpp"

#include <iostream>

using namespace std;

Pipeline::Pipeline()
: AbstractPipeline(), amplifier_(0), dataOut_(0), gains_(0)
{
}

void Pipeline::init()
{
    requestRemoteData("StreamData");
    requestRemoteData("ServiceData");
}

void Pipeline::run(QHash<QString, pelican::DataBlob*>& data)
{
    cout << "Pipeline::run() start. " << endl;
//    StreamData* stream = (StreamData*) data["StreamData"];
    ServiceData* service = (ServiceData*) data["ServiceData"];
    cout << " Service data value = " << service->value() << endl;

    cout << "Pipeline::run() complete. " << endl << endl;
}
