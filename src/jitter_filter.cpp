#include "../include/jitter_filter.h"

JitterFilter::JitterFilter() {
    m_history = nullptr;
    m_maxJitter = 0;
    m_offset = 0;
    m_jitterScale = 0.0f;
}

JitterFilter::~JitterFilter() {
    /* void */
    m_history.destroy();
}

void JitterFilter::initialize(
    int maxJitter,
    float cutoffFrequency,
    float audioFrequency)
{
    m_maxJitter = maxJitter;

    m_history.make(maxJitter);
    m_offset = 0;
    m_history.fill(0);

    m_noiseFilter.setCutoffFrequency(cutoffFrequency, audioFrequency);
}

float JitterFilter::f(float sample) {
    return fast_f(sample);
}
