#include "DirectDataClient.hpp"

#include "StreamDataChunker.hpp"
#include "ServiceDataChunker.hpp"
#include "StreamDataAdapter.hpp"
#include "ServiceDataAdapter.hpp"

#include <iostream>

DirectDataClient::DirectDataClient(const pelican::ConfigNode& node,
        const pelican::DataTypes& types, const pelican::Config* config)
: DirectStreamDataClient(node, types, config)
{
    try
    {
        addStreamChunker("StreamDataChunker", "");
        addServiceChunker("ServiceDataChunker", "");
    }
    catch (const QString& err)
    {
        std::cerr << "ERROR: " << err.toStdString() << std::endl;
    }
}

DirectDataClient::~DirectDataClient()
{
}

