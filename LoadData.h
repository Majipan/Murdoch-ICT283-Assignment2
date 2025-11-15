
#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include "WindData.h"

class LoadData {
public:
    /**
     * @brief Load wind records into the given container
     */
    void load(WindlogType& wind_data) const;
};

#endif
