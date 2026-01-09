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
            level(1.0) {
        }

        float processSample();

        void endNote();
        bool isActive() const { return angleDelta > 0; }

    private:
        static float lookupWave(double angle, int waveIndex);

        const ModuleConfiguration* configuration;
        double currentAngle;
        double angleDelta;
        double level;
    };
}

