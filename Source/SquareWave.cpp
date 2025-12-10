#include "SquareWave.h"

void SquareWave::prepare(double rate, int numChannels)
{
    sampleRate = static_cast<float>(rate);
    phases.resize(numChannels, 0.0f);
}
void SquareWave::process(juce::AudioBuffer<float>& buffer)
{
    float twoPi = 2.0f * std::numbers::pi_v<float>;

    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
        auto* data = buffer.getWritePointer(ch);
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            const float value = (std::sin(phases[ch]) >= 0.0f) ? amplitude : -amplitude;
            data[i] = value;

            const float phaseInc = (twoPi * frequency) / sampleRate;
            phases[ch] += phaseInc;
            if (phases[ch] >= twoPi)
                phases[ch] -= twoPi;
        }
    }
}