#include "SinWave.h"


void SinWave::prepare(const double rate, const int numChannels)
{
    sampleRate = static_cast<float>(rate);
    phases.resize(numChannels, 0.0f);
    smoothedFreq.reset(sampleRate, 0.05f);
    smoothedFreq.setCurrentAndTargetValue(getFrequency());
}

void SinWave::process(juce::AudioBuffer<float>& buffer)
{
    assert(buffer.getNumChannels() == phases.size());

    float doublePi = 2.0f * std::numbers::pi_v<float>;
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float frequency = smoothedFreq.getNextValue();
            const float phaseInc = (doublePi * frequency) / sampleRate;
            channelData[sample] = amplitude * std::sin(phases[channel]);

            phases[channel] += phaseInc;

            if (phases[channel] >= doublePi)
                phases[channel] -= doublePi;
        }
    }
}