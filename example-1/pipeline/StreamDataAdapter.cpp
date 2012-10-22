#include "StreamDataAdapter.hpp"
#include "StreamData.hpp"
#include <iostream>


StreamDataAdapter::StreamDataAdapter(const pelican::ConfigNode& config)
: AbstractStreamAdapter(config)
{
    samplesPerPacket_ = config.getOption("packet", "samples").toUInt();
    packetSize_ = headerSize_ + samplesPerPacket_ * sizeof(float);
}

void StreamDataAdapter::deserialise(QIODevice* device)
{
    std::cout << "StreamDataAdapter::deserialise()" << std::endl;

    StreamData* blob = (StreamData*) dataBlob();
    unsigned packets = chunkSize() / packetSize_;
    blob->resize(packets * samplesPerPacket_);

    char headerData[headerSize_];
    char* data = (char*) blob->ptr();

    int bytesRead = 0;
    for (int p = 0; p < packets; ++p)
    {
        while (device->bytesAvailable() < packetSize_)
            device->waitForReadyRead(-1);

        // Read the packet header from the device and dump it.
        device->read(headerData, headerSize_);

        // Read the data into the data blob.
        bytesRead += device->read(data + bytesRead, packetSize_ - headerSize_);
    }
}
