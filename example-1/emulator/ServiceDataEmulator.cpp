#include "ServiceDataEmulator.hpp"
#include <pelican/utility/ConfigNode.h>
#include <QtCore/QByteArray>
#include <cmath>
#include <iostream>

ServiceDataEmulator::ServiceDataEmulator(const pelican::ConfigNode& config)
: AbstractUdpEmulator(config), packetCounter_(0)
{
    // Load options (with defaults).
    packetInterval_ = config.getOption("packet", "interval", "10000").toULong();

    // Set the packet size in bytes (+32 for the header).
    packet_.resize(400 * sizeof(float) + 32);

    // Set constant parts of the packet header data
    char* ptr = packet_.data();
    *reinterpret_cast<int*>(ptr + 0)  = packet_.size();
    *reinterpret_cast<int*>(ptr + 4)  = 32;
    *reinterpret_cast<int*>(ptr + 8)  = 1;
    *reinterpret_cast<int*>(ptr + 12) = sizeof(float);
}


ServiceDataEmulator::~ServiceDataEmulator()
{
}

void ServiceDataEmulator::emulationFinished()
{
    std::cout << "ServiceDataEmulator::emulationFinished()" << std::endl;
}

void ServiceDataEmulator::getPacketData(char*& ptr, unsigned long& size)
{
    if (packetCounter_ >= 1)
    {
        ptr = 0;
        size = 0;
        return;
    }

    // Set pointer to the output data.
    ptr  = packet_.data();
    size = packet_.size();

    // Set variable part of the packet header.
    *reinterpret_cast<long int*>(ptr + 16) = packetCounter_;

    // Fill the packet data.
    char* data = ptr + 32;
    float value = 1 + packetCounter_ % 5;
    for (int i = 0; i < 400; ++i)
    {
        reinterpret_cast<float*>(data)[i] = value;
    }
    std::cout << "Service value: " << value << std::endl;

    ++packetCounter_;
}

unsigned long ServiceDataEmulator::interval()
{
    return packetInterval_;
}
