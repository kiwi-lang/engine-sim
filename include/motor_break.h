#ifndef ATG_ENGINE_SIM_MOTORBREAK_H
#define ATG_ENGINE_SIM_MOTORBREAK_H

#include "../include/scs.h"

#include "../include/crankshaft.h"

class MotorBreak : public atg_scs::Constraint
{
public:
    MotorBreak();
    virtual ~MotorBreak();

    void connectCrankshaft(Crankshaft *crankshaft);
    virtual void calculate(Output *output, atg_scs::SystemState *state);

    double m_ks;
    double m_kd;
    double m_maxTorque;
    double m_rotationSpeed;
    bool m_enabled;
};

#endif /* ATG_ENGINE_SIM_DYNAMOMETER_H */
