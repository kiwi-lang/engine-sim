#include "../include/crankshaft.h"

#include "../include/constants.h"

#include <cmath>
#include <assert.h>

Crankshaft::Crankshaft() {
    m_rodJournalCount = 0;
    m_throw = 0.0;
    m_m = 0.0;
    m_I = 0.0;
    m_flywheelMass = 0.0;
    m_p_x = m_p_y = 0.0;
    m_tdc = 0.0;
    m_frictionTorque = 0.0;
}

Crankshaft::~Crankshaft() {
    assert(m_rodJournalAngles == nullptr);
}

void Crankshaft::initialize(const Parameters &params) {
    m_m = params.mass;
    m_flywheelMass = params.flywheelMass;
    m_I = params.momentOfInertia;
    m_throw = params.crankThrow;
    m_rodJournalCount = params.rodJournals;
    m_rodJournalAngles.make(m_rodJournalCount);
    m_p_x = params.pos_x;
    m_p_y = params.pos_y;
    m_tdc = params.tdc;
    m_frictionTorque = params.frictionTorque;
}

void Crankshaft::destroy() {
    m_rodJournalAngles.destroy();
}

void Crankshaft::getRodJournalPositionLocal(int i, double *x, double *y) {
    const double theta = m_rodJournalAngles[i];

    *x = std::cos(theta) * m_throw;
    *y = std::sin(theta) * m_throw;
}

void Crankshaft::getRodJournalPositionGlobal(int i, double *x, double *y) {
    double lx, ly;
    getRodJournalPositionLocal(i, &lx, &ly);

    *x = lx + m_body.p_x;
    *y = ly + m_body.p_y;
}

void Crankshaft::resetAngle() {
    m_body.theta = std::fmod(m_body.theta, 4 * constants::pi);
}

void Crankshaft::setRodJournalAngle(int i, double angle) {
    assert(i < m_rodJournalCount && i >= 0);

    m_rodJournalAngles[i] = angle;
}

double Crankshaft::getAngle() const {
    return m_body.theta - m_tdc;
}

double Crankshaft::getCycleAngle(double offset) {
    const double wrapped = std::fmod(-getAngle() + offset, 4 * constants::pi);
    return (wrapped < 0)
        ? wrapped + 4 * constants::pi
        : wrapped;
}
