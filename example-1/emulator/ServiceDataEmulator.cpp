#include "ServiceDataEmulator.hpp"
#include <pelican/utility/ConfigNode.h>
#include <QtCore/QByteArray>
#include <cmath>
#include <iostream>

using namespace std;

ServiceDataEmulator::ServiceDataEmulator(const pelican::ConfigNode& config)
: AbstractUdpEmulator(config), packetCounter_(0)
{
    // Load options (with defaults).
    packetInterval_ = config.getOption("packet", "interval", "10000").toULong();
    numSamples_ = config.getOption("packet", "samples", "200").toInt();
    numPackets_ = config.getOption("data", "numPackets", "-1").toInt();
    dataPeriod_ = config.getOption("data", "period", "5").toInt();

    // Set the packet size in bytes (+32 for the header).
    packet_.resize(numSamples_ * sizeof(float));
}


ServiceDataEmulator::~ServiceDataEmulator()
{
}


void ServiceDataEmulator::getPacketData(char*& data, unsigned long& size)
{
    // Set pointer to the output data.
    data = packet_.data();
    size = packet_.size();

    // Fill the packet data.
    float value = 1 + (packetCounter_ % dataPeriod_);
    for (int i = 0; i < numSamples_; ++i)
        reinterpret_cast<float*>(data)[i] = value + (0.1/(float)numSamples_);

    cout << "ServiceData, bytes sent = " << size << endl;

    ++packetCounter_;
}

void ServiceDataEmulator::emulationFinished()
{
    cout << "ServiceDataEmulator::emulationFinished(). " << endl;
    cout << " -- Packets sent = " << packetCounter_ << endl;
    cout << " -- Packet size  = " << packet_.size() << endl;
    cout << " -- Total bytes sent = " << packetCounter_ * packet_.size() <<  endl;
}

int ServiceDataEmulator::nPackets()
{
    return numPackets_;
}

unsigned long ServiceDataEmulator::interval()
{
    return packetInterval_;
}
