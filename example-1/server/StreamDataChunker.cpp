#include "StreamDataChunker.hpp"
#include <pelican/utility/Config.h>
#include <QtNetwork/QUdpSocket>

#include <iostream>
using namespace std;


StreamDataChunker::StreamDataChunker(const pelican::ConfigNode& config)
: AbstractChunker(config), chunkSize_(0), bytesRead_(0), chunkCounter_(0)
{
    // The host, port and data type are set in the base class.

    // Set the chunk size from the configuration.
    int numPackets = config.getOption("data", "packets", 0).toInt();
    qint64 packetSize = config.getOption("data", "packetSize", 0).toInt();
    chunkSize_ = numPackets * packetSize;
}

QIODevice* StreamDataChunker::newDevice()
{
    // Return an opened QUdpSocket.
    QUdpSocket* socket = new QUdpSocket;
    socket->bind(QHostAddress(host()), port());

    // Wait for the socket to bind.
    while (socket->state() != QUdpSocket::BoundState) {}

    return socket;
}

void StreamDataChunker::next(QIODevice* device)
{
    qDebug() << "StreamDataChunker::next() [" << chunkCounter_++ << "]";

    QUdpSocket* socket = static_cast<QUdpSocket*>(device);
    bytesRead_ = 0;

    // Get writable buffer space for chunk.
    pelican::WritableData chunk = getDataStorage(chunkSize_);
    if (chunk.isValid())
    {
        // Get pointer to start of chunk memory.
        char* ptr = (char*)chunk.ptr();

        // Read datagrams for chunk from the socket.
        while (isActive() && bytesRead_ < chunkSize_)
        {
            // Read the datagram, but avoid using pendingDatagramSize()
            if (!socket->hasPendingDatagrams())
            {
                // MUST wait for the next datagram
                socket->waitForReadyRead(100);
                continue;
            }
            qint64 maxlength = chunkSize_ - bytesRead_;
            qint64 length = socket->readDatagram(ptr + bytesRead_, maxlength);
            if (length > 0)
                bytesRead_ += length;
        }
    }

    // Discard the datagram if there is no space.
    else
    {
        socket->readDatagram(0, 0);
    }
}
