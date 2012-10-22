#ifndef DIRECT_DATA_CLIENT_HPP_
#define DIRECT_DATA_CLIENT_HPP_

#include <pelican/core/DirectStreamDataClient.h>

class DirectDataClient : public pelican::DirectStreamDataClient
{
    public:
        DirectDataClient(const pelican::ConfigNode& node,
                const pelican::DataTypes& types,
                const pelican::Config* config);

        ~DirectDataClient();
};

namespace pelican {
PELICAN_DECLARE_CLIENT(DirectDataClient)
}

#endif /* DIRECT_DATA_CLIENT_HPP_ */
