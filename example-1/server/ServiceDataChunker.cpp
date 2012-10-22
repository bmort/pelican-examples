#include "ServiceDataChunker.hpp"
#include <pelican/utility/Config.h>
#include <QtNetwork/QUdpSocket>

#include <iostream>

ServiceDataChunker::ServiceDataChunker(const pelican::ConfigNode& config)
: AbstractChunker(config), chunkSize_(0), bytesRead_(0)
{
//    std::cout << "GainChunker::GainChunker()" << std::endl;
    // Set the chunk size from the configuration.
    // The host, port and data type are set in the base class.
    chunkSize_ = config.getOption("data", "chunkSize").toInt();
}

QIODevice* ServiceDataChunker::newDevice()
{
//    std::cout << "GainChunker::newDevice()" << std::endl;
    // Return an opened QUdpSocket.
    QUdpSocket* socket = new QUdpSocket;
    socket->bind(QHostAddress(host()), port());

    // Wait for the socket to bind.
    while (socket->state() != QUdpSocket::BoundState) {}

    return socket;
}

void ServiceDataChunker::next(QIODevice* device)
{
//    std::cout << "GainChunker::next()" << std::endl;

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
//    std::cout << " - bytes read: " << bytesRead_ << std::endl;
}
