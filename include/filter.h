#ifndef ATG_ENGINE_SIM_FILTER_H
#define ATG_ENGINE_SIM_FILTER_H

#include "wrapped_pointer.h"

class Filter {
    public:
        Filter();
        virtual ~Filter();

        virtual float f(float sample);
        virtual void destroy();
};

#endif /* ATG_ENGINE_SIM_FILTER_H */
