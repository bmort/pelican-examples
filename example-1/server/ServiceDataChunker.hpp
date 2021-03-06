#ifndef SERVICE_DATA_CHUNKER_HPP_
#define SERVICE_DATA_CHUNKER_HPP_

#include <pelican/server/AbstractChunker.h>

class ServiceDataChunker : public pelican::AbstractChunker
{
    public:
        ServiceDataChunker(const pelican::ConfigNode& config);

        // Creates the input device (usually a socket).
        virtual QIODevice* newDevice();

        // Obtains a chunk of data from the device.
        virtual void next(QIODevice*);

    private:
        quint64 packetSize_;
        int packets_;
        quint64 bytesRead_;
        int chunkCounter_;
};

namespace pelican {
PELICAN_DECLARE_CHUNKER(ServiceDataChunker)
}

#endif /* SERVICE_DATA_CHUNKER_HPP_ */
