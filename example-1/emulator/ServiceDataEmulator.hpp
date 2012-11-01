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
        unsigned long interval();
        void emulationFinished();

    private:
        unsigned long packetCounter_;
        unsigned long packetInterval_;
        QByteArray packet_;
};

#endif // SERVICE_DATA_EMULATOR_HPP_
