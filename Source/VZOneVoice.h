/*
  ==============================================================================

    VCOneVoice.h
    Created: 4 Jan 2026 9:09:22pm
    Author:  chris

  ==============================================================================
*/

#pragma once

#include <array>

#include <JuceHeader.h>

#include "ModuleState.h"


class VZOneVoice : public juce::SynthesiserVoice
{
public:
    // Inherited via SynthesiserVoice
    bool canPlaySound(juce::SynthesiserSound*) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
    VZOne::ModuleState moduleState[1];
};
