/*
  ==============================================================================

    VCOneVoice.cpp
    Created: 4 Jan 2026 9:09:48pm
    Author:  chris

  ==============================================================================
*/

#include "VZOneVoice.h"
#include "VZOneSound.h"

const std::array<VZOneVoice::WaveTable, VZOneVoice::waveformCount> VZOneVoice::waveTables = VZOneVoice::buildWaveTables();

float VZOneVoice::saw(float phase, float p, float u, float v)
{
    return phase <= p
               ? u / p * phase
           : phase <= v
               ? (1 - u / p * (1 - v) - u) / (v - p) * (phase - p) + u
               : u / p * (phase - 1.0f) + 1.0f;
}

std::array<VZOneVoice::WaveTable, VZOneVoice::waveformCount> VZOneVoice::buildWaveTables()
{
    std::array<WaveTable, waveformCount> tables{};

    for (int i = 0; i < tableSize; ++i)
    {
        float phase = static_cast<float>(i) / static_cast<float>(tableSize);
        double angle = juce::MathConstants<double>::twoPi * static_cast<double>(phase);

        tables[0][static_cast<size_t>(i)] = static_cast<float>(std::sin(angle));
        tables[1][static_cast<size_t>(i)] = std::sin(juce::MathConstants<double>::twoPi * saw(phase, 0.201063f, 0.298472f, 0.861249f));
        tables[2][static_cast<size_t>(i)] = std::sin(juce::MathConstants<double>::twoPi * saw(phase, 0.122448f, 0.299202f, 0.915584f));
        tables[3][static_cast<size_t>(i)] = std::sin(juce::MathConstants<double>::twoPi * saw(phase, 0.0692947f, 0.300676f, 0.952308f));
        tables[4][static_cast<size_t>(i)] = std::sin(juce::MathConstants<double>::twoPi * saw(phase, 0.0371464f, 0.300532f, 0.974066f));
        tables[5][static_cast<size_t>(i)] = std::sin(juce::MathConstants<double>::twoPi * saw(phase, 0.0199944f, 0.303999f, 0.986284f));
    }

    return tables;
}

float VZOneVoice::lookupWave(double angle, int waveIndex) const
{
    auto tablePos = angle * (static_cast<double>(tableSize) / juce::MathConstants<double>::twoPi);

    if (tablePos >= static_cast<double>(tableSize))
        tablePos -= static_cast<double>(tableSize);

    auto index0 = static_cast<int>(tablePos);
    auto frac = tablePos - static_cast<double>(index0);
    auto index1 = (index0 + 1) % tableSize;

    int clampedIndex = juce::jlimit(0, waveformCount - 1, waveIndex);
    const auto& table = waveTables[static_cast<size_t>(clampedIndex)];

    auto value0 = table[static_cast<size_t>(index0)];
    auto value1 = table[static_cast<size_t>(index1)];

    return static_cast<float>(value0 + (value1 - value0) * frac);
}

bool VZOneVoice::canPlaySound(juce::SynthesiserSound*)
{
    return true;
}

void VZOneVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    VZOne::Sound* vzSound = dynamic_cast<VZOne::Sound*>(sound);
    if (vzSound != nullptr)
        waveformIndex = juce::jlimit(0, waveformCount - 1, vzSound->getWaveformType());
    else
        waveformIndex = 0;
    currentAngle = 0.0;
    level = velocity * 0.15;
    tailOff = 0.0;

    auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();

    angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
}

void VZOneVoice::stopNote(float velocity, bool allowTailOff)
{
    clearCurrentNote();
    angleDelta = 0.0;
}

void VZOneVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void VZOneVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void VZOneVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (angleDelta != 0.0)
    {
        if (tailOff > 0.0) // [7]
        {
            while (--numSamples >= 0)
            {
                auto currentSample = static_cast<float>(lookupWave(currentAngle, waveformIndex) * level * tailOff);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);

                currentAngle += angleDelta;
                if (currentAngle >= juce::MathConstants<double>::twoPi)
                    currentAngle -= juce::MathConstants<double>::twoPi;
                ++startSample;

                tailOff *= 0.99; // [8]

                if (tailOff <= 0.005)
                {
                    clearCurrentNote(); // [9]

                    angleDelta = 0.0;
                    break;
                }
            }
        }
        else
        {
            while (--numSamples >= 0) // [6]
            {
                auto currentSample = static_cast<float>(lookupWave(currentAngle, waveformIndex) * level);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);

                currentAngle += angleDelta;
                if (currentAngle >= juce::MathConstants<double>::twoPi)
                    currentAngle -= juce::MathConstants<double>::twoPi;
                ++startSample;
            }
        }
    }
}
