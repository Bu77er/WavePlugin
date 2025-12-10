#pragma once
#include "Oscillator.h"
#include <numbers>

class SquareWave : public Oscillator
{
public:
    void prepare(double rate, int numChannels) override;
    void process(juce::AudioBuffer<float>& buffer) override;

    void setFrequency(float newFrequency) override { frequency = newFrequency; }
    void setAmplitude(float newAmplitude) override { amplitude = newAmplitude; }

private:
    float sampleRate = 44100.0f;
    float frequency = 440.0f;
    float amplitude = 0.0f;

    std::vector<float> phases;
};