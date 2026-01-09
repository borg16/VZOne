/*
  ==============================================================================

    VZOneSound.h
    Created: 5 Jan 2026 8:45:14pm
    Author:  chris

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "ModuleConfiguration.h"

namespace VZOne
{
    class Sound : public juce::SynthesiserSound
    {
    public:
        static constexpr int waveformCount = 6;

        Sound();
        ~Sound() override;
        bool appliesToNote(int midiNoteNumber) override;
        bool appliesToChannel(int midiChannel) override;

        const ModuleConfiguration* getConfiguration(int idx) const { return configuration + idx; }
        ModuleConfiguration* getConfiguration(int idx) { return configuration + idx; }

    private:

        ModuleConfiguration configuration[1];

        JUCE_LEAK_DETECTOR(Sound)
    };
} // namespace VZOne
