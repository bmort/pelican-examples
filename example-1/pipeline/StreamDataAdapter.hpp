#ifndef STREAM_DATA_ADAPTER_HPP_
#define STREAM_DATA_ADAPTER_HPP_

#include <pelican/core/AbstractStreamAdapter.h>

class StreamDataAdapter : public pelican::AbstractStreamAdapter
{
    public:
        StreamDataAdapter(const pelican::ConfigNode&);
        void deserialise(QIODevice*);

    private:
        static const unsigned headerSize_ = 32;
        unsigned samplesPerPacket_;
        unsigned packetSize_;
};

namespace pelican {
PELICAN_DECLARE_ADAPTER(StreamDataAdapter)
}

#endif /* STREAM_DATA_ADAPTER_HPP_ */
