/*
  ==============================================================================

    ModuleConfiguration.h
    Created: 8 Jan 2026 10:35:34pm
    Author:  chris

  ==============================================================================
*/

#pragma once

namespace VZOne
{
    class ModuleConfiguration {
    public:
        ModuleConfiguration() = default;
        // Add configuration parameters as needed

        int getWaveformType() const { return waveformType; }
        void setWaveformType(int type) { waveformType = type; }
    private:
        int waveformType = 2; // 0: sine, 1-5: additional waves
    };
}
