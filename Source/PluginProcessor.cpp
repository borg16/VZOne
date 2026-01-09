/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "VZOneVoice.h" // <-- Change to the correct file name if needed


//==============================================================================
VZOne::Processor::Processor()
    : AudioProcessor(BusesProperties()
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    ),
    sound(new Sound())
{
    synth = new juce::Synthesiser();
    synth->addVoice(new Voice());
    synth->addVoice(new Voice());
    synth->addVoice(new Voice());
    synth->addVoice(new Voice());
    synth->addSound(sound);
}

VZOne::Processor::~Processor()
{
}

//==============================================================================
const juce::String VZOne::Processor::getName() const
{
    return JucePlugin_Name;
}

bool VZOne::Processor::acceptsMidi() const
{
    return true;
}

bool VZOne::Processor::producesMidi() const
{
    return false;
}

bool VZOne::Processor::isMidiEffect() const
{
    return false;
}

double VZOne::Processor::getTailLengthSeconds() const
{
    return 0.0;
}

int VZOne::Processor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int VZOne::Processor::getCurrentProgram()
{
    return 0;
}

void VZOne::Processor::setCurrentProgram(int /*index*/)
{
}

const juce::String VZOne::Processor::getProgramName(int /*index*/)
{
    return {};
}

void VZOne::Processor::changeProgramName(int /*index*/, const juce::String& /*newName*/)
{
}

//==============================================================================
void VZOne::Processor::prepareToPlay(double sampleRate, int /*samplesPerBlock*/)
{
    synth->setCurrentPlaybackSampleRate(sampleRate);
}

void VZOne::Processor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool VZOne::Processor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
    return true;
}

void VZOne::Processor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // CRITICAL: Clear the buffer first to avoid passing through input audio
    buffer.clear();
    
    // Now render the synth output
    synth->renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    // Apply gain compensation based on number of active voices
    int numActiveVoices = 0;
    for (int i = 0; i < synth->getNumVoices(); ++i)
    {
        if (synth->getVoice(i)->isVoiceActive())
            ++numActiveVoices;
    }
    
    if (numActiveVoices > 1)
    {
        // Reduce gain to prevent clipping when multiple voices play
        float gainReduction = 1.0f / std::sqrt(static_cast<float>(numActiveVoices));
        buffer.applyGain(gainReduction);
    }
}

//==============================================================================
bool VZOne::Processor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* VZOne::Processor::createEditor()
{
    return new VZOneAudioProcessorEditor(*this);
}

//==============================================================================
void VZOne::Processor::getStateInformation(juce::MemoryBlock& /*destData*/)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void VZOne::Processor::setStateInformation(const void* /*data*/, int /*sizeInBytes*/)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VZOne::Processor();
}
