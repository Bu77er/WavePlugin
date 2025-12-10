/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
    , freqSliderAttachment(audioProcessor.getState(), "freqHz", frequencySlider)
    , playButtonAttachment(audioProcessor.getState(), "play", playButton)
    , waveFormAttachment(audioProcessor.getState(), "waveform", waveFormBox)
{

    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    
    addAndMakeVisible(&frequencySlider);

    frequencyLabel.setJustificationType(juce::Justification::verticallyCentred);

    addAndMakeVisible(&frequencyLabel);
   
    playButton.setButtonText("Playing");
    playButton.setClickingTogglesState(true);
    playButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    playButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
    playButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::red);

    playButton.onClick = [this]()
        {
            const bool isPlaying = playButton.getToggleState();
            playButton.setButtonText(isPlaying ? "Playing" : "Bypassed");
        };

    addAndMakeVisible(playButton);

    waveFormBox.addItem("Sine", 1);
    waveFormBox.addItem("Square", 2);
    waveFormBox.setSelectedId(1);

    addAndMakeVisible(waveFormBox);

    setSize (400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::darkolivegreen);
    g.setFont (juce::FontOptions (30.0f));
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    frequencySlider.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 100, 100, 200);
    playButton.setBounds(getWidth() / 2 - 30, getHeight() / 2 + 110, 60, 20);
    frequencyLabel.setBounds(getWidth() / 2 - 30, getHeight() / 2 - 120, 60, 20);
    waveFormBox.setBounds(getWidth() / 2 + 50, getHeight() / 2 - 120, 100, 20);
}
