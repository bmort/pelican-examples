#ifndef SERVICE_DATA_ADAPTER_HPP_
#define SERVICE_DATA_ADAPTER_HPP_

#include <pelican/core/AbstractServiceAdapter.h>

class ServiceDataAdapter : public pelican::AbstractServiceAdapter
{
    public:
        ServiceDataAdapter(const pelican::ConfigNode&);
        void deserialise(QIODevice*);

    private:
        static const unsigned headerSize_ = 32;
        unsigned packetSize_;
};

namespace pelican {
PELICAN_DECLARE_ADAPTER(ServiceDataAdapter)
}

#endif /* SERVICE_DATA_ADAPTER_HPP_ */
