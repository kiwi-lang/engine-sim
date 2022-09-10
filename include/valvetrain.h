#ifndef ATG_ENGINE_SIM_VALVETRAIN_H
#define ATG_ENGINE_SIM_VALVETRAIN_H

#include "wrapped_pointer.h"

class Camshaft;
class Valvetrain {
public:
    Valvetrain();
    virtual ~Valvetrain();

    virtual double intakeValveLift(int cylinder) = 0;
    virtual double exhaustValveLift(int cylinder) = 0;

    virtual Ptr<Camshaft> getActiveIntakeCamshaft() = 0;
    virtual Ptr<Camshaft> getActiveExhaustCamshaft() = 0;
};

#endif /* ATG_ENGINE_SIM_VALVETRAIN_H */
