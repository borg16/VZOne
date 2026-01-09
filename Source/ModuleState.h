/*
  ==============================================================================

    Module.h
    Created: 7 Jan 2026 11:56:12pm
    Author:  chris

  ==============================================================================
*/

#pragma once

#include <array>

namespace VZOne
{
    class ModuleConfiguration;

    class ModuleState {
    public:
        ModuleState():configuration(nullptr),
            currentAngle(0.0),
            angleDelta(0.0),
            level(0.0) {}

        ModuleState(const ModuleConfiguration* config, double cyclesPerSample)
            : configuration(config),
            currentAngle(0.0),
            angleDelta(cyclesPerSample * 2.0 * juce::MathConstants<double>::pi),
            level(0.0) {
        }

        float processSample() {
            if (angleDelta == 0.0)
                return 0.0;
            auto sample = lookupWave(currentAngle, 2) * level;
            currentAngle += angleDelta;
            if (currentAngle >= juce::MathConstants<double>::twoPi)
                currentAngle -= juce::MathConstants<double>::twoPi;
            return static_cast<float>(sample);
        }

    private:
        static float lookupWave(double angle, int waveIndex);

        const ModuleConfiguration* configuration;
        double currentAngle;
        double angleDelta;
        double level;
    };
}

