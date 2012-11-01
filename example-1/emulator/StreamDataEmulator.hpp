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
        quint32 packetCounter_;
        quint32 totalSamples_;
        quint32 numSamples_;
        quint32 packetInterval_;
        quint32 signalPeriod_;
        QByteArray packet_;
};

#endif // SIGNAL_EMULATOR_HPP_


