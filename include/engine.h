#ifndef ATG_ENGINE_SIM_ENGINE_H
#define ATG_ENGINE_SIM_ENGINE_H

#include "part.h"

#include "piston.h"
#include "connecting_rod.h"
#include "crankshaft.h"
#include "cylinder_bank.h"
#include "cylinder_head.h"
#include "exhaust_system.h"
#include "ignition_module.h"
#include "intake.h"
#include "combustion_chamber.h"
#include "units.h"
#include "throttle.h"

#include <string>

class Simulator;
class Vehicle;
class Transmission;
class Engine : public Part {
    public:
        struct Parameters {
            int cylinderBanks;
            int cylinderCount;
            int crankshaftCount;
            int exhaustSystemCount;
            int intakeCount;

            std::string name;

            double starterTorque = units::torque(90.0, units::ft_lb);
            double starterSpeed = units::rpm(200);
            double redline = units::rpm(6500);
            double dynoMinSpeed = units::rpm(1000);
            double dynoMaxSpeed = units::rpm(6500);
            double dynoHoldStep = units::rpm(100);

            Throttle *throttle;

            double initialSimulationFrequency;
            double initialHighFrequencyGain;
            double initialNoise;
            double initialJitter;
        };

    public:
        Engine();
        virtual ~Engine();

        void initialize(const Parameters &params);
        virtual void destroy();

        std::string getName() const { return m_name; }

        virtual Crankshaft const*getOutputCrankshaft() const;
        virtual Crankshaft* getOutputCrankshaft();

        virtual void setSpeedControl(double s);
        virtual double getSpeedControl();
        virtual void setThrottle(double throttle);
        virtual double getThrottle() const;
        virtual double getThrottlePlateAngle() const;
        virtual void calculateDisplacement();
        double getDisplacement() const { return m_displacement; }
        virtual double getIntakeFlowRate() const;
        virtual void update(double dt);

        virtual double getManifoldPressure() const;
        virtual double getIntakeAfr() const;
        virtual double getExhaustO2() const;
        virtual double getRpm() const;
        virtual double getSpeed() const;
        virtual bool isSpinningCw() const;

        virtual void resetFuelConsumption();
        virtual double getTotalFuelMassConsumed() const;
        double getTotalVolumeFuelConsumed() const;

        inline double getStarterTorque() const { return m_starterTorque; }
        inline double getStarterSpeed() const { return m_starterSpeed; }
        inline double getRedline() const { return m_redline; }
        inline double getDynoMinSpeed() const { return m_dynoMinSpeed; }
        inline double getDynoMaxSpeed() const { return m_dynoMaxSpeed; }
        inline double getDynoHoldStep() const { return m_dynoHoldStep; }

        int getCylinderBankCount() const { return m_cylinderBankCount; }
        int getCylinderCount() const { return m_cylinderCount; }
        int getCrankshaftCount() const { return m_crankshaftCount; }
        int getExhaustSystemCount() const { return m_exhaustSystemCount; }
        int getIntakeCount() const { return m_intakeCount; }
        int getMaxDepth() const;

        Crankshaft* getCrankshaft(int i) { return &m_crankshafts[i]; }
        Crankshaft const* getCrankshaft(int i) const { return &m_crankshafts[i]; }

        CylinderBank *getCylinderBank(int i)  { return &m_cylinderBanks[i]; }
        CylinderHead *getHead(int i)  { return &m_heads[i]; }
        Piston *getPiston(int i)  { return &m_pistons[i]; }
        ConnectingRod *getConnectingRod(int i)  { return &m_connectingRods[i]; }
        IgnitionModule *getIgnitionModule() { return &m_ignitionModule; }
        ExhaustSystem *getExhaustSystem(int i)  { return &m_exhaustSystems[i]; }
        Intake *getIntake(int i)  { return &m_intakes[i]; }
        CombustionChamber *getChamber(int i)  { return &m_combustionChambers[i]; }
        Fuel *getFuel() { return &m_fuel; }

        double getSimulationFrequency() const { return m_initialSimulationFrequency; }
        double getInitialHighFrequencyGain() const { return m_initialHighFrequencyGain; }
        double getInitialNoise() const { return m_initialNoise; }
        double getInitialJitter() const { return m_initialJitter; }

        virtual Simulator *createSimulator(Vehicle *vehicle, Transmission *transmission);

    protected:
        std::string m_name;

        Ptr<Crankshaft> m_crankshafts;
        int m_crankshaftCount;

        Ptr<CylinderBank> m_cylinderBanks;
        Ptr<CylinderHead> m_heads;
        int m_cylinderBankCount;

        Ptr<Piston> m_pistons;
        Ptr<ConnectingRod> m_connectingRods;
        Ptr<CombustionChamber> m_combustionChambers;
        int m_cylinderCount;

        double m_starterTorque;
        double m_starterSpeed;
        double m_redline;
        double m_dynoMinSpeed;
        double m_dynoMaxSpeed;
        double m_dynoHoldStep;

        double m_initialSimulationFrequency;
        double m_initialHighFrequencyGain;
        double m_initialNoise;
        double m_initialJitter;

        Ptr<ExhaustSystem > m_exhaustSystems;
        int m_exhaustSystemCount;

        Ptr < Intake > m_intakes;
        int m_intakeCount;

        IgnitionModule m_ignitionModule;
        Fuel m_fuel;

        Ptr < Throttle > m_throttle;

        double m_throttleValue;
        double m_displacement;
};

#endif /* ATG_ENGINE_SIM_ENGINE_H */
