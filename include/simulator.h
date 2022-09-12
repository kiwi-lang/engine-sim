#ifndef ATG_ENGINE_SIM_SIMULATOR_H
#define ATG_ENGINE_SIM_SIMULATOR_H

#include "engine.h"
#include "transmission.h"
#include "combustion_chamber.h"
#include "vehicle.h"
#include "synthesizer.h"
#include "dynamometer.h"
#include "starter_motor.h"
#include "derivative_filter.h"
#include "vehicle_drag_constraint.h"
#include "motor_break.h"

#include "scs.h"

#include <chrono>

class Simulator
{
public:
    enum class SystemType
    {
        NsvOptimized,
        Generic
    };

    struct Parameters
    {
        SystemType SystemType = SystemType::NsvOptimized;
    };

public:
    Simulator();
    ~Simulator();

    void initialize(const Parameters &params);
    void loadSimulation(Engine *engine, Vehicle *vehicle, Transmission *transmission);
    void releaseSimulation();

    void startFrame(double dt);
    bool simulateStep();
    double getTotalExhaustFlow() const;
    int readAudioOutput(int samples, int16_t *target);
    int getFrameIterationCount() const { return i_steps; }
    void endFrame();
    void destroy();

    void startAudioRenderingThread();
    void endAudioRenderingThread();

    double getSynthesizerInputLatency() const { return m_synthesizer.getLatency(); }
    double getSynthesizerInputLatencyTarget() const;

    int getCurrentIteration() const { return m_currentIteration; }

    int i_steps;

    double getAverageProcessingTime() const { return m_physicsProcessingTime; }

    Ptr<Engine> getEngine() const { return m_engine; }
    Ptr<Transmission> getTransmission() const { return m_transmission; }
    Ptr<Vehicle> getVehicle() const { return m_vehicle; }
    Ptr<atg_scs::RigidBodySystem> getSystem() { return m_system; }

    void setSimulationFrequency(int frequency) { m_simulationFrequency = frequency; }
    int getSimulationFrequency() const { return m_simulationFrequency; }

    void setFluidSimulationSteps(int steps) { m_fluidSimulationSteps = steps; }
    int getFluidSimulationSteps() const { return m_fluidSimulationSteps; }
    int getFluidSimulationFrequency() const { return m_fluidSimulationSteps * m_simulationFrequency; }

    double getTimestep() const { return 1.0 / m_simulationFrequency; }

    void setTargetSynthesizerLatency(double latency) { m_targetSynthesizerLatency = latency; }
    double getTargetSynthesizerLatency() const { return m_targetSynthesizerLatency; }

    void setSimulationSpeed(double simSpeed) { m_simulationSpeed = simSpeed; }
    double getSimulationSpeed() const { return m_simulationSpeed; }

    double getFilteredDynoTorque() const { return m_dynoTorque; }
    double getDynoPower() const { return m_engine ? m_dynoTorque * m_engine->getSpeed() : 0; }
    double getAverageOutputSignal() const;

    Ptr<Synthesizer> getSynthesizer() { return &m_synthesizer; }

    Dynamometer m_dyno;
    StarterMotor m_starterMotor;
    DerivativeFilter m_derivativeFilter;
    MotorBreak m_motor_break;

    void initializeSynthesizer(Synthesizer::Parameters synthParams);

protected:
    void placeAndInitialize();
    void placeCylinder(int i);

protected:
    void updateFilteredEngineSpeed(double dt);
    void writeToSynthesizer();

protected:
    Ptr<atg_scs::RigidBodySystem> m_system;
    Synthesizer m_synthesizer;

    Ptr<atg_scs::FixedPositionConstraint> m_crankConstraints;
    Ptr<atg_scs::ClutchConstraint> m_crankshaftLinks;
    Ptr<atg_scs::RotationFrictionConstraint> m_crankshaftFrictionConstraints;
    Ptr<atg_scs::LineConstraint> m_cylinderWallConstraints;
    Ptr<atg_scs::LinkConstraint> m_linkConstraints;
    atg_scs::RigidBody m_vehicleMass;
    VehicleDragConstraint m_vehicleDrag;

    std::chrono::steady_clock::time_point m_simulationStart;
    std::chrono::steady_clock::time_point m_simulationEnd;
    int m_currentIteration;

    Ptr<Engine> m_engine;
    Ptr<Transmission> m_transmission;
    Ptr<Vehicle> m_vehicle;

    double m_physicsProcessingTime;

    int m_simulationFrequency;
    int m_fluidSimulationSteps;

    double m_targetSynthesizerLatency;
    double m_simulationSpeed;
    Ptr<double> m_exhaustFlowStagingBuffer;
    double m_filteredEngineSpeed;
    double m_dynoTorque;
};

#endif /* ATG_ENGINE_SIM_SIMULATOR_H */
