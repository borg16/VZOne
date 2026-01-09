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

bool VZOne::Voice::canPlaySound(juce::SynthesiserSound*)
{
    return true;
}

void VZOne::Voice::startNote(int midiNoteNumber, float /*velocity*/, juce::SynthesiserSound* sound, int /*currentPitchWheelPosition*/)
{
    Sound* vzSound = dynamic_cast<Sound*>(sound);
    if (vzSound != nullptr) {

        auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        auto cyclesPerSample = cyclesPerSecond / getSampleRate();

        // Placement new to re-construct moduleState[0] in-place
        new (&moduleState[0]) ModuleState(vzSound->getConfiguration(0), cyclesPerSample);
    }
}

void VZOne::Voice::stopNote(float /*velocity*/, bool /*allowTailOff*/)
{
    moduleState[0].endNote();
    clearCurrentNote();
}

void VZOne::Voice::pitchWheelMoved(int /*newPitchWheelValue*/)
{
}

void VZOne::Voice::controllerMoved(int /*controllerNumber*/, int /*newControllerValue*/)
{
}

void VZOne::Voice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    // Only render if this voice is currently playing a note
    if (!isVoiceActive())
        return;

    while (--numSamples >= 0)
    {
        auto currentSample = moduleState[0].processSample();

        for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
            outputBuffer.addSample(i, startSample, currentSample);
        ++startSample;
    }
}
