#include "../include/impulse_response.h"

ImpulseResponse::ImpulseResponse() {
    m_volume = 1.0;
    m_size = 0;
    m_buffer = nullptr;
}

ImpulseResponse::~ImpulseResponse() {
    /* void */
    if (m_size > 0) {
        delete m_buffer;
    }
}

void ImpulseResponse::initialize(
    const std::string &filename,
    double volume)
{
    m_filename = filename;
    m_volume = volume;
}

#if 1
const int16_t* ImpulseResponse::GetImpulseResponse(std::size_t& size) {
    if (m_size == 0 || m_buffer == nullptr) {
        ysWindowsAudioWaveFile waveFile;
        waveFile.OpenFile(getFilename().c_str());
        waveFile.InitializeInternalBuffer(waveFile.GetSampleCount());
        waveFile.FillBuffer(0);
        waveFile.CloseFile();

        m_size = waveFile.GetSampleCount();
        m_buffer = new int16_t[m_size];
        memcpy(m_buffer, waveFile.GetBuffer(), m_size * sizeof(int16_t));
 
        waveFile.DestroyInternalBuffer();


        // Clip the Impulse now
        unsigned int clippedLength = 0;
        for (unsigned int i = 0; i < m_size; ++i) {
            if (std::abs(m_buffer[i]) > 100) {
                clippedLength = i + 1;
            }
        }
        m_size = clippedLength;
    }

    size = m_size;
    return m_buffer;
}
#endif