#include "StreamDataEmulator.hpp"
#include <pelican/utility/ConfigNode.h>
#include <cmath>
#include <iostream>

StreamDataEmulator::StreamDataEmulator(const pelican::ConfigNode& config)
: AbstractUdpEmulator(config), packetCounter_(0), totalSamples_(0)
{
    // Load options (with defaults).
    numSamples_     = config.getOption("packet", "samples", "256").toULong();
    packetInterval_ = config.getOption("packet", "interval", "2560").toULong();
    signalPeriod_   = config.getOption("signal", "period", "20").toULong();

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
//    std::cout << "SignalEmulator::getPacketData()" << std::endl;

    // Set pointer to the output data.
    ptr  = packet_.data();
    size = packet_.size();

    // Set variable part of the packet header.
    *reinterpret_cast<long int*>(ptr + 16) = packetCounter_;

    // Fill the packet data.
    char* data = ptr + 32;
    for (int i = 0; i < numSamples_; ++i)
    {
        float value = (totalSamples_ + i) % signalPeriod_;
        reinterpret_cast<float*>(data)[i] = value;
        std::cout << "stream value: " << value << std::endl;

    }

    ++packetCounter_;
    totalSamples_ += numSamples_;
}

unsigned long StreamDataEmulator::interval()
{
    return packetInterval_;
}
