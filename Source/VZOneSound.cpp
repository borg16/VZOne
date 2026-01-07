/*
  ==============================================================================

    VZOneSound.cpp
    Created: 5 Jan 2026 8:45:14pm
    Author:  chris

  ==============================================================================
*/

#include "VZOneSound.h"

VZOne::Sound::Sound()
{
}

VZOne::Sound::~Sound()
{
}

bool VZOne::Sound::appliesToNote(int /*midiNoteNumber*/)
{
    return true;
}

bool VZOne::Sound::appliesToChannel(int /*midiChannel*/)
{
    return true;
}

void VZOne::Sound::setWaveformType(int newType)
{
  waveformType = newType;
}

int VZOne::Sound::getWaveformType() const
{
  return waveformType;
}
