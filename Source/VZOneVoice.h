/*
  ==============================================================================

    VCOneVoice.h
    Created: 4 Jan 2026 9:09:22pm
    Author:  chris

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <array>

class VZOneVoice : public juce::SynthesiserVoice
{
    // Inherited via SynthesiserVoice
    bool canPlaySound(juce::SynthesiserSound*) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
    static constexpr int tableSize = 2048;
    static constexpr int waveformCount = 6;
    using WaveTable = std::array<float, tableSize>;

    static const std::array<WaveTable, waveformCount> waveTables;

    static std::array<WaveTable, waveformCount> buildWaveTables();
    static float saw(float phase, float p, float u, float v);
    float lookupWave(double angle, int waveIndex) const;

    int waveformIndex = 0;
    double currentAngle = 0.0, angleDelta = 0.0, level = 0.0, tailOff = 0.0;
};