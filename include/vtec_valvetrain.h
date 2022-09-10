#ifndef ATG_ENGINE_SIM_VTEC_STANDARD_VALVETRAIN_H
#define ATG_ENGINE_SIM_VTEC_STANDARD_VALVETRAIN_H

#include "valvetrain.h"
#include "wrapped_pointer.h"

class Engine;
class VtecValvetrain : public Valvetrain {
public:
    struct Parameters {
        double MinRpm;
        double MinSpeed;
        double ManifoldVacuum;
        double MinThrottlePosition;

        Camshaft *IntakeCamshaft;
        Camshaft *ExhaustCamshaft;

        Camshaft *VtecIntakeCamshaft;
        Camshaft *VtexExhaustCamshaft;

        Engine *Engine;
    };

public:
    VtecValvetrain();
    virtual ~VtecValvetrain();

    void initialize(const Parameters &parameters);

    virtual double intakeValveLift(int cylinder) override;
    virtual double exhaustValveLift(int cylinder) override;

    virtual Ptr<Camshaft> getActiveIntakeCamshaft() override;
    virtual Ptr<Camshaft> getActiveExhaustCamshaft() override;

private:
    bool isVtecEnabled() const;

    Ptr <Camshaft> m_intakeCamshaft;
    Ptr <Camshaft> m_exhaustCamshaft;

    Ptr <Camshaft> m_vtecIntakeCamshaft;
    Ptr <Camshaft> m_vtecExhaustCamshaft;

    Ptr <Engine> m_engine;

    double m_minRpm;
    double m_minSpeed;
    double m_manifoldVacuum;
    double m_minThrottlePosition;
};

#endif /* ATG_ENGINE_SIM_VTEC_STANDARD_VALVETRAIN_H */
