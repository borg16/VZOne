/*
  ==============================================================================

    VZOneSound.h
    Created: 5 Jan 2026 8:45:14pm
    Author:  chris

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

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

        void setWaveformType(int newType);
        int getWaveformType() const;

    private:
      int waveformType = 2; // 0: sine, 1-5: additional waves

        JUCE_LEAK_DETECTOR(Sound)
    };
} // namespace VZOne