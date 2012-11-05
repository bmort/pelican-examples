#include "ServiceDataAdapter.hpp"
#include "ServiceData.hpp"
#include <iostream>

using namespace std;

ServiceDataAdapter::ServiceDataAdapter(const pelican::ConfigNode& config)
: AbstractServiceAdapter(config)
{
    numSamples_ = config.getOption("chunk", "numSamples").toInt();
}

void ServiceDataAdapter::deserialise(QIODevice* device)
{
    ServiceData* blob = (ServiceData*)dataBlob();
    blob->resize(numSamples_);
    float* data = blob->ptr();

    size_t chunkSize = numSamples_ * sizeof(float);

    while (device->bytesAvailable() < chunkSize)
        device->waitForReadyRead(-1);

    // Read the data into the data blob.
    device->read(reinterpret_cast<char*>(data), chunkSize);
}
