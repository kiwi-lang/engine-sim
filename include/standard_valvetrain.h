#ifndef ATG_ENGINE_SIM_STANDARD_VALVETRAIN_H
#define ATG_ENGINE_SIM_STANDARD_VALVETRAIN_H

#include "valvetrain.h"
#include "wrapped_pointer.h"

class StandardValvetrain : public Valvetrain {
public:
    struct Parameters {
        Camshaft *intakeCamshaft;
        Camshaft *exhaustCamshaft;
    };

public:
    StandardValvetrain();
    virtual ~StandardValvetrain();

    void initialize(const Parameters &parameters);

    virtual double intakeValveLift(int cylinder) override;
    virtual double exhaustValveLift(int cylinder) override;

    virtual Ptr<Camshaft> getActiveIntakeCamshaft() override;
    virtual Ptr<Camshaft> getActiveExhaustCamshaft() override;

public:
    Ptr<Camshaft> m_intakeCamshaft;
    Ptr<Camshaft> m_exhaustCamshaft;
};

#endif /* ATG_ENGINE_SIM_STANDARD_VALVETRAIN_H */
