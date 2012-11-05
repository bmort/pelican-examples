#include "ServiceDataChunker.hpp"
#include <pelican/utility/Config.h>
#include <QtNetwork/QUdpSocket>

#include <iostream>
using namespace std;

ServiceDataChunker::ServiceDataChunker(const pelican::ConfigNode& config)
: AbstractChunker(config), bytesRead_(0)
{
    // Set the packet size and number of packets to be placed in a chunk
    // from the configuration.
    // Note: The host, port and data type are set in the base class.
    packetSize_ = config.getOption("data", "packetSize").toInt();
    packets_ = config.getOption("data", "packets", "1").toInt();
}

QIODevice* ServiceDataChunker::newDevice()
{
    // Return an opened QUdpSocket.
    QUdpSocket* socket = new QUdpSocket;
    socket->bind(QHostAddress(host()), port());

    // Wait for the socket to bind.
    while (socket->state() != QUdpSocket::BoundState) {}

    return socket;
}

void ServiceDataChunker::next(QIODevice* device)
{
    QUdpSocket* socket = static_cast<QUdpSocket*>(device);
    bytesRead_ = 0;

    int chunkSize = packetSize_ * packets_;

    // Get writable buffer space for chunk.
    pelican::WritableData chunk = getDataStorage(chunkSize);

    if (chunk.isValid())
    {
        // Get pointer to start of chunk memory.
        char* ptr = (char*)chunk.ptr();

        // Read datagrams for chunk from the socket.
        while (isActive() && bytesRead_ < chunkSize)
        {
            // Read the datagram, but avoid using pendingDatagramSize()
            if (!socket->hasPendingDatagrams())
            {
                // MUST wait for the next datagram
                socket->waitForReadyRead(100);
                continue;
            }
            qint64 maxlength = chunkSize - bytesRead_;
            qint64 length = socket->readDatagram(ptr + bytesRead_, maxlength);
            if (length > 0)
                bytesRead_ += length;
        }
    }

    // Discard the datagram if there is no space.
    else
    {
        cerr << "WARNING: ServiceDataChunker::next() Discarding data, "
                "chunk not valid!" << endl;
        socket->readDatagram(0, 0);
    }
}
