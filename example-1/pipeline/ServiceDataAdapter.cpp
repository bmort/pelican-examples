#include "ServiceDataAdapter.hpp"
#include "ServiceData.hpp"
#include <iostream>


ServiceDataAdapter::ServiceDataAdapter(const pelican::ConfigNode& config)
: AbstractServiceAdapter(config)
{
    packetSize_ = headerSize_ + 4;
}

void ServiceDataAdapter::deserialise(QIODevice* device)
{
    std::cout << "ServiceDataAdapter::deserialise()" << std::endl;
    ServiceData* blob = (ServiceData*) dataBlob();

    char headerData[headerSize_];

    float data;

    while (device->bytesAvailable() < packetSize_)
        device->waitForReadyRead(-1);

    // Read the packet header from the device and dump it.
    device->read(headerData, headerSize_);

    // Read the data into the data blob.
    device->read(reinterpret_cast<char*>(&data), packetSize_ - headerSize_);

    blob->setValue(data);
}
