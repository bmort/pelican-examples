#include "ServiceData.hpp"
#include <QtCore/QDataStream>

ServiceData::ServiceData() : DataBlob("ServiceData"), value_(0.0)
{
}

float ServiceData::value() const
{
    return value_;
}

void ServiceData::setValue(float value)
{
    value_ = value;
}
