#ifndef SERVICE_DATA_HPP_
#define SERVICE_DATA_HPP_

#include "pelican/data/DataBlob.h"
#include <QtCore/QVector>

class ServiceData : public pelican::DataBlob
{
    public:
        ServiceData() : DataBlob("ServiceData") { }
        float value(int idx = 0) const { return values_[idx]; }
        void resize(int n) { values_.resize(n); }
        float* ptr() { return values_.data(); }
        const float* ptr() const { return values_.data(); }
        QVector<float>& values() { return values_; }
        const QVector<float>& values() const { return values_; }
        int size() const { return values_.size(); }

    private:
        QVector<float> values_;
};

namespace pelican {
PELICAN_DECLARE_DATABLOB(ServiceData)
}

#endif /* SERVICE_DATA_HPP_ */
