#include "../include/convolution_filter.h"

#include <assert.h>
#include <string.h>

ConvolutionFilter::ConvolutionFilter() {
    m_shiftRegister = nullptr;
    m_impulseResponse = nullptr;

    m_shiftOffset = 0;
    m_sampleCount = 0;
}

ConvolutionFilter::~ConvolutionFilter() {
}

void ConvolutionFilter::initialize(int samples) {
    assert (samples > 0);
    
    m_sampleCount = samples;
    m_shiftOffset = 0;
    m_shiftRegister.make(samples);
    m_impulseResponse.make(samples);


    m_shiftRegister.fill(0);
    m_impulseResponse.fill(0);
}

void ConvolutionFilter::destroy() {
    m_shiftRegister.destroy();
    m_impulseResponse.destroy();
}

float ConvolutionFilter::f(float sample) {
    m_shiftRegister[m_shiftOffset] = sample;

    float result = 0;
    for (int i = 0; i < m_sampleCount - m_shiftOffset; ++i) {
        result += m_impulseResponse[i] * m_shiftRegister[i + m_shiftOffset];
    }

    for (int i = m_sampleCount - m_shiftOffset; i < m_sampleCount; ++i) {
        result += m_impulseResponse[i] * m_shiftRegister[i - (m_sampleCount - m_shiftOffset)];
    }

    m_shiftOffset = (m_shiftOffset - 1 + m_sampleCount) % m_sampleCount;

    return result;
}
