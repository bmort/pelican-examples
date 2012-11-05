#include "Pipeline.hpp"
#include "StreamData.hpp"
#include "ServiceData.hpp"

#include <iostream>

using namespace std;

Pipeline::Pipeline()
: AbstractPipeline(), amplifier_(0), dataOut_(0), gains_(0), count_(0)
{
}

void Pipeline::init()
{
    requestRemoteData("StreamData");
    requestRemoteData("ServiceData");
}

void Pipeline::run(QHash<QString, pelican::DataBlob*>& data)
{
    cout << "Pipeline::run() start. [" << count_ << "]" << endl;

    StreamData* stream = (StreamData*) data["StreamData"];
    ServiceData* service = (ServiceData*) data["ServiceData"];

    cout << "--> stream size  = " << stream->size() << endl;
    cout << "    value[0]     = " << stream->ptr()[0] << endl;
    cout << "    value[1]     = " << stream->ptr()[1] << endl;
    cout << "    value[2]     = " << stream->ptr()[2] << endl;
    cout << "    value[3]     = " << stream->ptr()[3] << endl;
    cout << "    value[4]     = " << stream->ptr()[4] << endl;
    cout << "--> service size = " << service->size() << endl;
    cout << "    value[0]     = " << service->ptr()[0] << endl;

    ++count_;
    cout << "Pipeline::run() complete. " << endl << endl;
}
