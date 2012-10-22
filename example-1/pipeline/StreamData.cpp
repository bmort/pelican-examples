#include "StreamData.hpp"

#include <QtCore/QDataStream>

StreamData::StreamData() : DataBlob("SignalData")
{
}

const float* StreamData::ptr() const
{
    return data_.size() > 0 ? data_.constData() : 0;
}

float* StreamData::ptr()
{
    return data_.size() > 0 ? data_.data() : 0;
}

void StreamData::resize(int length)
{
    data_.resize(length);
}

int StreamData::size() const
{
    return data_.size();
}

void StreamData::serialise(QIODevice& out) const
{
    QDataStream stream(&out);

    // Write the number of samples in the time series.
    quint32 numSamples = size();
    stream << numSamples;

    // Write the data to the output device.
    const float* data = ptr();
    for (int i = 0; i < numSamples; ++i)
    {
        stream << data[i];
    }
}

void StreamData::deserialise(QIODevice& in, QSysInfo::Endian)
{
    QDataStream stream(&in);

    // Read the number of samples in the time series.
    quint32 numSamples = 0;
    stream >> numSamples;

    // Read data into the blob
    resize(numSamples);
    float* data = ptr();
    for (int i = 0; i < numSamples; ++i)
    {
        stream >> data[i];
    }
}
