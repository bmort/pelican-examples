#ifndef SIGNAL_EMULATOR_HPP_
#define SIGMAL_EMULATOR_HPP_

#include <pelican/emulator/AbstractUdpEmulator.h>
#include <QtCore/QByteArray>

class StreamDataEmulator : public pelican::AbstractUdpEmulator
{
    public:
        StreamDataEmulator(const pelican::ConfigNode& configNode);
        ~StreamDataEmulator();
        void getPacketData(char*& ptr, unsigned long& size);
        unsigned long interval();

    private:
        unsigned long packetCounter_;
        unsigned long long totalSamples_;
        unsigned long numSamples_;
        unsigned long packetInterval_;
        unsigned long signalPeriod_;
        QByteArray packet_;
};

#endif // SIGNAL_EMULATOR_HPP_


