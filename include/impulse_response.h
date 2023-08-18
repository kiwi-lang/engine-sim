#ifndef ATG_ENGINE_SIM_IMPULSE_RESPONSE_H
#define ATG_ENGINE_SIM_IMPULSE_RESPONSE_H

#include <string>

class ImpulseResponse
{
    public:
    ImpulseResponse();
    virtual ~ImpulseResponse();

    void        initialize(const std::string &filename, double volume);
    std::string getFilename() const { return m_filename; }
    double      getVolume() const { return m_volume; }

    public:
    std::string m_filename;
    double      m_volume;

#if 1
    const int16_t *GetImpulseResponse(std::size_t& size);

    int16_t *      m_buffer;
    std::size_t    m_size;
#endif
};

#endif /* ATG_ENGINE_SIM_IMPULSE_RESPONSE_H */
