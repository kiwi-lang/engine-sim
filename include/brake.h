#ifndef ATG_ENGINE_SIM_Brake_H
#define ATG_ENGINE_SIM_Brake_H

#include "scs.h"

#include "part_crankshaft.h"

class Brake : public atg_scs::Constraint {
    public:
        Brake();
        virtual ~Brake();

        void connectCrankshaft(Crankshaft *crankshaft);
        virtual void calculate(Output *output, atg_scs::SystemState *state);
        double getTorque() const;

        double m_rotationSpeed;
        double m_ks;
        double m_kd;
        double m_maxTorque;

        bool m_hold;
        bool m_enabled;
};

#endif /* ATG_ENGINE_SIM_DYNAMOMETER_H */
