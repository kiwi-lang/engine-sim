#include "../include/camshaft.h"

#include "../include/crankshaft.h"
#include "../include/constants.h"
#include "../include/units.h"

#include <cmath>
#include <assert.h>

Camshaft::Camshaft() {
    m_lobes = 0;
    m_advance = 0;
    m_baseRadius = 0;
}

Camshaft::~Camshaft() {
    assert(!m_lobeAngles.valid());
}

void Camshaft::initialize(const Parameters &params) {
    m_lobeAngles.make(params.Lobes);
    memset(m_lobeAngles.get(), 0, sizeof(double) * params.Lobes);

    m_lobes = params.Lobes;
    m_crankshaft = params.Crankshaft;
    m_lobeProfile = params.LobeProfile;
    m_advance = params.Advance;
    m_baseRadius = params.BaseRadius;
}

void Camshaft::destroy() 
{
    m_lobeAngles.destroy();

    m_lobes = 0;
}

double Camshaft::valveLift(int lobe) const {
    return sampleLobe(getAngle() + m_lobeAngles[lobe]);
}

double Camshaft::sampleLobe(double theta) const {
    double clampedTheta = std::fmod(theta, 2 * constants::pi);
    if (clampedTheta < 0) clampedTheta += 2 * constants::pi;
    if (clampedTheta >= constants::pi) clampedTheta -= 2 * constants::pi;

    return m_lobeProfile->sampleTriangle(clampedTheta);
}

double Camshaft::getAngle() const {
    const double angle =
        std::fmod((m_crankshaft->getAngle() + m_advance) * 0.5, 2 * constants::pi);
    return (angle < 0)
        ?  angle + 2 * constants::pi
        :  angle;
}
