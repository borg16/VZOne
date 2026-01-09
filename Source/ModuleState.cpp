/*
  ==============================================================================

    Module.cpp
    Created: 7 Jan 2026 11:56:12pm
    Author:  chris

  ==============================================================================
*/

#include <array>

#include <JuceHeader.h>

#include "ModuleState.h"
#include "VZOneSound.h"

using namespace VZOne;

static constexpr int tableSize = 2048;

using WaveTable = std::array<float, tableSize>;

static float saw(float phase, float p, float u, float v)
{
    return phase <= p
        ? u / p * phase
        : phase <= v
        ? (1 - u / p * (1 - v) - u) / (v - p) * (phase - p) + u
        : u / p * (phase - 1.0f) + 1.0f;
}

static std::unique_ptr<std::array<WaveTable, VZOne::Sound::waveformCount>> buildWaveTables()
{
    // Allocate on the heap to avoid large stack usage
    auto tablesPtr = std::make_unique<std::array<WaveTable, VZOne::Sound::waveformCount>>();
    auto& tables = *tablesPtr;

    for (int i = 0; i < tableSize; ++i)
    {
        float phase = static_cast<float>(i) / static_cast<float>(tableSize);
        double angle = juce::MathConstants<double>::twoPi * static_cast<double>(phase);

        tables[0][static_cast<size_t>(i)] = static_cast<float>(std::sin(angle));
        tables[1][static_cast<size_t>(i)] = static_cast<float>(std::sin(juce::MathConstants<double>::twoPi * saw(phase, 0.201063f, 0.298472f, 0.861249f)));
        tables[2][static_cast<size_t>(i)] = static_cast<float>(std::sin(juce::MathConstants<double>::twoPi * saw(phase, 0.122448f, 0.299202f, 0.915584f)));
        tables[3][static_cast<size_t>(i)] = static_cast<float>(std::sin(juce::MathConstants<double>::twoPi * saw(phase, 0.0692947f, 0.300676f, 0.952308f)));
        tables[4][static_cast<size_t>(i)] = static_cast<float>(std::sin(juce::MathConstants<double>::twoPi * saw(phase, 0.0371464f, 0.300532f, 0.974066f)));
        tables[5][static_cast<size_t>(i)] = static_cast<float>(std::sin(juce::MathConstants<double>::twoPi * saw(phase, 0.0199944f, 0.303999f, 0.986284f)));
    }

    return tablesPtr;
}

const std::unique_ptr<std::array<WaveTable, VZOne::Sound::waveformCount>> waveTables = buildWaveTables();

float ModuleState::lookupWave(double angle, int waveIndex)
{
    auto tablePos = angle * (static_cast<double>(tableSize) / juce::MathConstants<double>::twoPi);

    if (tablePos >= static_cast<double>(tableSize))
        tablePos -= static_cast<double>(tableSize);

    auto index0 = static_cast<int>(tablePos);
    auto frac = tablePos - static_cast<double>(index0);
    auto index1 = (index0 + 1) % tableSize;

    int clampedIndex = juce::jlimit(0, VZOne::Sound::waveformCount - 1, waveIndex);
    const auto& table = (*waveTables)[static_cast<size_t>(clampedIndex)];

    auto value0 = table[static_cast<size_t>(index0)];
    auto value1 = table[static_cast<size_t>(index1)];

    return static_cast<float>(value0 + (value1 - value0) * frac);
}

