#include "DirectDataClient.hpp"

#include "SignalChunker.hpp"

DirectDataClient::DirectDataClient(const pelican::ConfigNode& node,
        const pelican::DataTypes& types, const pelican::Config* config)
: DirectStreamDataClient(node, types, config)
{
    addChunker("Stream1", "SignalChunker", "Stream1ConfigName");
}

DirectDataClient::~DirectDataClient()
{
}
