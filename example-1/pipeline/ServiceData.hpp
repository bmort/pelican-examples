#ifndef SERVICE_DATA_HPP_
#define SERVICE_DATA_HPP_

#include "pelican/data/DataBlob.h"
#include <QtCore/QVector>

class ServiceData : public pelican::DataBlob
{
    public:
        ServiceData();
        float value() const;
        void setValue(float value);

    private:
        float value_;
};

namespace pelican {
PELICAN_DECLARE_DATABLOB(ServiceData);
}

#endif /* SERVICE_DATA_HPP_ */
