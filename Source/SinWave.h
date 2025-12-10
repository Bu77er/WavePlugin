#pragma once
#include <numbers>
#include <cassert>
#include "juce_audio_basics/juce_audio_basics.h"
#include "Oscillator.h"

class SinWave : public Oscillator
{
public:
    void prepare(double rate, int numChannels) override;
    void process(juce::AudioBuffer<float>& buffer) override;

    float getAmplitude() const { return amplitude; }
    float getFrequency() { return smoothedFreq.getNextValue(); }
    void setAmplitude(const float newAmplitude) override { amplitude = newAmplitude; }
    void setFrequency(const float newFrequency) override { smoothedFreq.setTargetValue(newFrequency); }

private:
    std::vector<float> phases;
    float amplitude = 0.02f;
    float sampleRate = 0.0f;
    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> smoothedFreq;
};