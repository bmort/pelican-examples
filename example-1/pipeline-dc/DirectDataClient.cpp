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
    qDebug() << "DirectDataClient::DirectDataClient()";

    // FIXME HOW TO ADAPTERS GET ADDED...?

    QList<pelican::DataSpec> s = types.dataSpec();
//    config->summary();
//    qDebug() << "  = node type: " << node.type();
//    qDebug() << "  = node name: " << node.name();

    qDebug() << "  = Number of types (types.dataSpec().size()): " << s.size();

    try {
        // XXX: WHY does addChunker fail...?
        // -- this method doesn't exist on the server as the server does not
        //    know the if a chunk is stream or service data automatically.
        // -- this knowledge is possible in the client as adapters know
        //    if they are service or stream data as they should inherit from
        //    AbstractServiceAdapter or AbstractStreamAdapter...?
        // -- The data buffers should also know this if they exist at this point...
        // -- The addChunker fails as it doens't know at this point
        //    what type (service/stream) a chunker is...
        // -- This requires that the adapters are already loaded...?
//        addChunker("StreamData", "StreamDataChunker", ""); // NOTE THIS FAILS...
        addStreamChunker("StreamDataChunker", "");
//        addServiceChunker("ServiceDataChunker", "");
    }
    catch (const QString& err)
    {
        std::cerr << "ERROR: " << err.toStdString() << std::endl;
    }

    // FIXME For the PelicanServerClient the constructor does not return
    // Until the dataspec is matched??
    // -- Run the server pipeline and look at the printing
    // from the PipelineDriver::setDataClient() method.
    // -- This function returns immediately...?
    // >>> TODO trace where the PelicanServerClient is waiting...
    //    as this client should probably do the same until data is ready...?


    // TODO
    // -- write a unit test on the DirectStreamDataClient::addChunker() method...
    // -- Work out what is different between the existing unit tests on
    //    on the directStreamDataClient and the DirectDataClient example...
    //    --- the tests use lower level methods... how do these map to
    //        what the pipeline app / pipeline driver is doing.
    // -- Look at the test binary directClientMain.cpp
    //       -- difference is related to starting the pipeline driver before
    //          something is ready...?

    qDebug() << "  = dataSpec().allData() " << dataSpec().allData();
}

DirectDataClient::~DirectDataClient()
{
}

