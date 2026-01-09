/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VZOne::VZOneAudioProcessorEditor::VZOneAudioProcessorEditor (Processor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    waveformSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    waveformSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    waveformSlider.setRange(0, Sound::waveformCount - 1, 1.0);
    waveformSlider.setValue(audioProcessor.getSound()->getConfiguration(0)->getWaveformType());
    waveformSlider.onValueChange = [this]()
    {
        audioProcessor.getSound()->getConfiguration(0)->setWaveformType(juce::jlimit(0, Sound::waveformCount - 1, static_cast<int>(waveformSlider.getValue())));
    };

    waveformLabel.setText("Waveform", juce::dontSendNotification);
    waveformLabel.setJustificationType(juce::Justification::centred);
    waveformLabel.attachToComponent(&waveformSlider, false);

    addAndMakeVisible(waveformSlider);
    addAndMakeVisible(waveformLabel);

    setSize (400, 120);
}

VZOne::VZOneAudioProcessorEditor::~VZOneAudioProcessorEditor()
{
}

//==============================================================================
void VZOne::VZOneAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
}

void VZOne::VZOneAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(20);
    waveformSlider.setBounds(area.removeFromTop(60));
}
