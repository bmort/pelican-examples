#ifndef SERVICE_DATA_EMULATOR_HPP_
#define SERVICE_DATA_EMULATOR_HPP_

#include <pelican/emulator/AbstractUdpEmulator.h>
#include <QtCore/QByteArray>

class ServiceDataEmulator : public pelican::AbstractUdpEmulator
{
    public:
        ServiceDataEmulator(const pelican::ConfigNode& configNode);
        ~ServiceDataEmulator();
        void getPacketData(char*& ptr, unsigned long& size);
        void emulationFinished();
        unsigned long interval();
        int nPackets();

    private:
        unsigned long packetCounter_;
        unsigned long packetInterval_;
        QByteArray packet_;
        int numSamples_;
        int numPackets_;
        int dataPeriod_;
};

#endif // SERVICE_DATA_EMULATOR_HPP_
