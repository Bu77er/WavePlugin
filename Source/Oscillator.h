#pragma once
#include <JuceHeader.h>

class Oscillator
{
public:
    virtual ~Oscillator() = default;

    virtual void prepare(double sampleRate, int numChannels) = 0;
    virtual void process(juce::AudioBuffer<float>& buffer) = 0;

    virtual void setFrequency(float f) = 0;
    virtual void setAmplitude(float a) = 0;
};