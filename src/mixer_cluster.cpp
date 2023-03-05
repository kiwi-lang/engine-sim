#include "../include/mixer_cluster.h"

#include "../include/units.h"
#include "../include/gauge.h"
#include "../include/constants.h"
#include "../include/engine_sim_application.h"

#include <sstream>

MixerCluster::MixerCluster() {
    m_volumeGauge = nullptr,
    m_convolutionGauge = nullptr,
    m_highFreqFilterGauge = nullptr,
    m_levelerGauge = nullptr;
    m_noise0Gauge = nullptr;
    m_noise1Gauge = nullptr;
    m_simulator = nullptr;
}

MixerCluster::~MixerCluster() {
    /* void */
}

void MixerCluster::initialize(EngineSimApplication *app) {
    UiElement::initialize(app);

    constexpr float shortenAngle = (float)units::angle(1.0, units::deg);

    m_volumeGauge = addElement<LabeledGauge>();
    m_volumeGauge->m_title = "Vol.";
    m_volumeGauge->m_unit = "";
    m_volumeGauge->m_precision = 1;
    m_volumeGauge->setLocalPosition({ 0, 0 });
    m_volumeGauge->m_gauge->m_min = 0;
    m_volumeGauge->m_gauge->m_max = 100;
    m_volumeGauge->m_gauge->m_minorStep = 5;
    m_volumeGauge->m_gauge->m_majorStep = 10;
    m_volumeGauge->m_gauge->m_maxMinorTick = 1000000;
    m_volumeGauge->m_gauge->m_thetaMin = (float)constants::pi * 1.2f;
    m_volumeGauge->m_gauge->m_thetaMax = -(float)constants::pi * 0.2f;
    m_volumeGauge->m_gauge->m_needleWidth = 4.0f;
    m_volumeGauge->m_gauge->m_gamma = 1.0f;
    m_volumeGauge->m_gauge->m_needleKs = 1000.0f;
    m_volumeGauge->m_gauge->m_needleKd = 20.0f;
    m_volumeGauge->m_gauge->setBandCount(0);

    m_levelerGauge = addElement<LabeledGauge>();
    m_levelerGauge->m_title = "Lvl.";
    m_levelerGauge->m_unit = "";
    m_levelerGauge->m_precision = 1;
    m_levelerGauge->setLocalPosition({ 0, 0 });
    m_levelerGauge->m_gauge->m_min = 0;
    m_levelerGauge->m_gauge->m_max = 100;
    m_levelerGauge->m_gauge->m_minorStep = 5;
    m_levelerGauge->m_gauge->m_majorStep = 10;
    m_levelerGauge->m_gauge->m_maxMinorTick = 1000000;
    m_levelerGauge->m_gauge->m_thetaMin = (float)constants::pi * 1.2f;
    m_levelerGauge->m_gauge->m_thetaMax = -(float)constants::pi * 0.2f;
    m_levelerGauge->m_gauge->m_needleWidth = 4.0f;
    m_levelerGauge->m_gauge->m_gamma = 1.0f;
    m_levelerGauge->m_gauge->m_needleKs = 1000.0f;
    m_levelerGauge->m_gauge->m_needleKd = 20.0f;
    m_levelerGauge->m_gauge->setBandCount(0);

    m_convolutionGauge = addElement<LabeledGauge>();
    m_convolutionGauge->m_title = "Conv.";
    m_convolutionGauge->m_unit = "";
    m_convolutionGauge->m_precision = 1;
    m_convolutionGauge->setLocalPosition({ 0, 0 });
    m_convolutionGauge->m_gauge->m_min = 0;
    m_convolutionGauge->m_gauge->m_max = 100;
    m_convolutionGauge->m_gauge->m_minorStep = 5;
    m_convolutionGauge->m_gauge->m_majorStep = 10;
    m_convolutionGauge->m_gauge->m_maxMinorTick = 1000000;
    m_convolutionGauge->m_gauge->m_thetaMin = (float)constants::pi * 1.2f;
    m_convolutionGauge->m_gauge->m_thetaMax = -(float)constants::pi * 0.2f;
    m_convolutionGauge->m_gauge->m_needleWidth = 4.0f;
    m_convolutionGauge->m_gauge->m_gamma = 1.0f;
    m_convolutionGauge->m_gauge->m_needleKs = 1000.0f;
    m_convolutionGauge->m_gauge->m_needleKd = 20.0f;
    m_convolutionGauge->m_gauge->setBandCount(0);

    m_highFreqFilterGauge = addElement<LabeledGauge>();
    m_highFreqFilterGauge->m_title = "+HF";
    m_highFreqFilterGauge->m_unit = "";
    m_highFreqFilterGauge->m_precision = 2;
    m_highFreqFilterGauge->setLocalPosition({ 0, 0 });
    m_highFreqFilterGauge->m_gauge->m_min = 0;
    m_highFreqFilterGauge->m_gauge->m_max = 10;
    m_highFreqFilterGauge->m_gauge->m_minorStep = 1;
    m_highFreqFilterGauge->m_gauge->m_majorStep = 2;
    m_highFreqFilterGauge->m_gauge->m_maxMinorTick = 10;
    m_highFreqFilterGauge->m_gauge->m_thetaMin = (float)constants::pi * 1.2f;
    m_highFreqFilterGauge->m_gauge->m_thetaMax = -(float)constants::pi * 0.2f;
    m_highFreqFilterGauge->m_gauge->m_needleWidth = 4.0f;
    m_highFreqFilterGauge->m_gauge->m_gamma = 1.0f;
    m_highFreqFilterGauge->m_gauge->m_needleKs = 1000.0f;
    m_highFreqFilterGauge->m_gauge->m_needleKd = 20.0f;
    m_highFreqFilterGauge->m_gauge->setBandCount(0);

    m_noise0Gauge = addElement<LabeledGauge>();
    m_noise0Gauge->m_title = "~ LF";
    m_noise0Gauge->m_unit = "";
    m_noise0Gauge->m_precision = 1;
    m_noise0Gauge->setLocalPosition({ 0, 0 });
    m_noise0Gauge->m_gauge->m_min = 0;
    m_noise0Gauge->m_gauge->m_max = 100;
    m_noise0Gauge->m_gauge->m_minorStep = 5;
    m_noise0Gauge->m_gauge->m_majorStep = 10;
    m_noise0Gauge->m_gauge->m_maxMinorTick = 1000000;
    m_noise0Gauge->m_gauge->m_thetaMin = (float)constants::pi * 1.2f;
    m_noise0Gauge->m_gauge->m_thetaMax = -(float)constants::pi * 0.2f;
    m_noise0Gauge->m_gauge->m_needleWidth = 4.0f;
    m_noise0Gauge->m_gauge->m_gamma = 1.0f;
    m_noise0Gauge->m_gauge->m_needleKs = 1000.0f;
    m_noise0Gauge->m_gauge->m_needleKd = 20.0f;
    m_noise0Gauge->m_gauge->setBandCount(0);

    m_noise1Gauge = addElement<LabeledGauge>();
    m_noise1Gauge->m_title = "~ HF";
    m_noise1Gauge->m_unit = "";
    m_noise1Gauge->m_precision = 1;
    m_noise1Gauge->setLocalPosition({ 0, 0 });
    m_noise1Gauge->m_gauge->m_min = 0;
    m_noise1Gauge->m_gauge->m_max = 100;
    m_noise1Gauge->m_gauge->m_minorStep = 5;
    m_noise1Gauge->m_gauge->m_majorStep = 10;
    m_noise1Gauge->m_gauge->m_maxMinorTick = 1000000;
    m_noise1Gauge->m_gauge->m_thetaMin = (float)constants::pi * 1.2f;
    m_noise1Gauge->m_gauge->m_thetaMax = -(float)constants::pi * 0.2f;
    m_noise1Gauge->m_gauge->m_needleWidth = 4.0f;
    m_noise1Gauge->m_gauge->m_gamma = 1.0f;
    m_noise1Gauge->m_gauge->m_needleKs = 1000.0f;
    m_noise1Gauge->m_gauge->m_needleKd = 20.0f;
    m_noise1Gauge->m_gauge->setBandCount(0);
}

void MixerCluster::destroy() {
    UiElement::destroy();
}

void MixerCluster::update(float dt) {
    UiElement::update(dt);
}

void MixerCluster::render() {
    Grid grid;
    grid.h_cells = 6;
    grid.v_cells = 1;

    Synthesizer::AudioParameters parameters = m_simulator->synthesizer().getAudioParameters();

    m_volumeGauge->m_bounds = grid.get(m_bounds, 0, 0);
    m_volumeGauge->m_gauge->m_value = (float)parameters.volume * 100.0f;

    m_convolutionGauge->m_bounds = grid.get(m_bounds, 1, 0);
    m_convolutionGauge->m_gauge->m_value = (float)parameters.convolution * 100.0f;

    m_highFreqFilterGauge->m_bounds = grid.get(m_bounds, 2, 0);
    m_highFreqFilterGauge->m_gauge->m_value = (float)parameters.dF_F_mix * 1000.0f;

    m_noise0Gauge->m_bounds = grid.get(m_bounds, 3, 0);
    m_noise0Gauge->m_gauge->m_value = (float)parameters.airNoise * 100.0f;

    m_noise1Gauge->m_bounds = grid.get(m_bounds, 4, 0);
    m_noise1Gauge->m_gauge->m_value = (float)parameters.inputSampleNoise * 100.0f;

    const double gain = m_simulator->synthesizer().getLevelerGain();
    m_levelerGauge->m_bounds = grid.get(m_bounds, 5, 0);
    m_levelerGauge->m_gauge->m_value =
        100.0f * (float)((gain - parameters.levelerMinGain) / parameters.levelerMaxGain);

    UiElement::render();
}
