#include "ServiceDataChunker.hpp"
#include <pelican/utility/Config.h>
#include <QtNetwork/QUdpSocket>

#include <iostream>

ServiceDataChunker::ServiceDataChunker(const pelican::ConfigNode& config)
: AbstractChunker(config), chunkSize_(0), bytesRead_(0)
{
    // Set the chunk size from the configuration.
    // The host, port and data type are set in the base class.
    chunkSize_ = config.getOption("data", "chunkSize").toInt();
    qDebug() << "Chunk size = " << chunkSize_;
}

QIODevice* ServiceDataChunker::newDevice()
{
    qDebug() << "ServiceDataChunker::newDevice()";
    // Return an opened QUdpSocket.
    QUdpSocket* socket = new QUdpSocket;
    socket->bind(QHostAddress(host()), port());

    // Wait for the socket to bind.
    while (socket->state() != QUdpSocket::BoundState) {}

    return socket;
}

void ServiceDataChunker::next(QIODevice* device)
{
   qDebug() << "\nServiceDataBuffer::next() ============ START";

    QUdpSocket* socket = static_cast<QUdpSocket*>(device);
    bytesRead_ = 0;

    // Get writable buffer space for chunk.
    pelican::WritableData chunk = getDataStorage(chunkSize_);
    qDebug() << "Chunk isValid? " << chunk.isValid();
    pelican::WritableData chunk2 = getDataStorage(chunkSize_);
    qDebug() << "Chunk2 isValid? " << chunk2.isValid();

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
        std::cerr << "WARNING ServiceDataChunker::next() Discarding data, "
                "chunk not valid!" << std::endl;
        socket->readDatagram(0, 0);
    }
//    std::cout << " - bytes read: " << bytesRead_ << std::endl;
    qDebug() << "ServiceDataBuffer::next() ============ DONE " << bytesRead_;
}
