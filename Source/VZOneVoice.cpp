/*
  ==============================================================================

    VCOneVoice.cpp
    Created: 4 Jan 2026 9:09:48pm
    Author:  chris

  ==============================================================================
*/

#include "VZOneVoice.h"
#include "VZOneSound.h"
#include "ModuleState.h"

bool VZOneVoice::canPlaySound(juce::SynthesiserSound*)
{
    return true;
}

void VZOneVoice::startNote(int midiNoteNumber, float /*velocity*/, juce::SynthesiserSound* sound, int /*currentPitchWheelPosition*/)
{
    VZOne::Sound* vzSound = dynamic_cast<VZOne::Sound*>(sound);
    if (vzSound != nullptr) {

        auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        auto cyclesPerSample = cyclesPerSecond / getSampleRate();

        // Placement new to re-construct moduleState[0] in-place
        moduleState[0].~ModuleState();
        new (&moduleState[0]) VZOne::ModuleState(vzSound->getConfiguration(0), cyclesPerSample);
    }
}

void VZOneVoice::stopNote(float /*velocity*/, bool /*allowTailOff*/)
{
    clearCurrentNote();
}

void VZOneVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void VZOneVoice::controllerMoved(int /*controllerNumber*/, int newControllerValue)
{
}

void VZOneVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    while (--numSamples >= 0)
    {
        auto currentSample = moduleState[0].processSample();

        for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
            outputBuffer.addSample(i, startSample, currentSample);
        ++startSample;
    }
}
