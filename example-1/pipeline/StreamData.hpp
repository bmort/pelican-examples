#ifndef STREAM_DATA_HPP_
#define STREAM_DATA_HPP_

#include "pelican/data/DataBlob.h"
#include <QtCore/QVector>

class StreamData : public pelican::DataBlob
{
    public:
        StreamData();
        const float* ptr() const;
        float* ptr();
        void resize(int length);
        int size() const;
        void serialise(QIODevice&) const;
        void deserialise(QIODevice&, QSysInfo::Endian);

    private:
        QVector<float> data_;
};

namespace pelican {
PELICAN_DECLARE_DATABLOB(StreamData);
}

#endif /* STREAM_DATA_HPP_ */
