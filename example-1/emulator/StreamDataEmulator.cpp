#include "StreamDataEmulator.hpp"
#include <pelican/utility/ConfigNode.h>
#include <cmath>
#include <iostream>

using namespace std;

StreamDataEmulator::StreamDataEmulator(const pelican::ConfigNode& config)
: AbstractUdpEmulator(config), packetCounter_(0), totalSamples_(0)
{
    // Load options (with defaults).
    numSamples_     = config.getOption("packet", "samples", "10").toULong();
    packetInterval_ = config.getOption("packet", "interval", "10000").toULong();
    dataPeriod_     = config.getOption("data", "period", "100").toULong();
    nPackets_       = config.getOption("data", "numPackets", "-1").toInt();

    // Set the packet size in bytes (+32 for the header).
    packet_.resize(numSamples_ * sizeof(float) + 32);

    // Set constant parts of the packet header data
    char* ptr = packet_.data();
    *reinterpret_cast<int*>(ptr + 0)  = packet_.size();
    *reinterpret_cast<int*>(ptr + 4)  = 32;
    *reinterpret_cast<int*>(ptr + 8)  = numSamples_;
    *reinterpret_cast<int*>(ptr + 12) = sizeof(float);
}

StreamDataEmulator::~StreamDataEmulator()
{
}


void StreamDataEmulator::getPacketData(char*& ptr, unsigned long& size)
{
    // Set pointer to the output data.
    ptr  = packet_.data();
    size = packet_.size();

    // Set variable part of the packet header.
    *reinterpret_cast<long int*>(ptr + 16) = packetCounter_;

    // Fill the packet data.
    char* data = ptr + 32;
    for (int i = 0; i < numSamples_; ++i)
    {
        float value = (totalSamples_ + i) % dataPeriod_;
        reinterpret_cast<float*>(data)[i] = value;
    }

    qDebug() << "Stream: [" << packetCounter_ << "] Bytes sent = " << size
             << " (total = "
             << size * packetCounter_ << ")";

    ++packetCounter_;
    totalSamples_ += numSamples_;
}

void StreamDataEmulator::emulationFinished()
{
    cout << "StreamDataEmulator::emulationFinished()" << endl;
    cout << " -- Packets sent = " << packetCounter_ << endl;
    cout << " -- Packet size  = " << packet_.size() << endl;
    cout << " -- Total bytes sent = " << packetCounter_ * packet_.size() <<  endl;
}

int StreamDataEmulator::nPackets()
{
    return nPackets_;
}

unsigned long StreamDataEmulator::interval()
{
    return packetInterval_;
}
