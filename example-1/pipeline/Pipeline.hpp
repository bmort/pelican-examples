#ifndef PIPELINE_HPP_
#define PIPELINE_HPP_

#include <pelican/core/AbstractPipeline.h>

class StreamData;
class ServiceData;
class SignalAmplifier;

class Pipeline : public pelican::AbstractPipeline
{
    public:
        Pipeline();
        void init();
        void run(QHash<QString, pelican::DataBlob*>&);

    private:
        SignalAmplifier* amplifier_;
        StreamData* dataOut_;
        ServiceData* gains_;
        quint32 count_;
};

#endif /* PIPELINE_HPP_ */
