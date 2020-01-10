/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Delay1AudioProcessor::Delay1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

Delay1AudioProcessor::~Delay1AudioProcessor()
{
}

//==============================================================================
const String Delay1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Delay1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Delay1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Delay1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Delay1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Delay1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Delay1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Delay1AudioProcessor::setCurrentProgram (int index)
{
}

const String Delay1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Delay1AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Delay1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    this->sampleRate = sampleRate;
    for (int i = 0; i < 2; i++) 
    {
        delayLine[i].updateSize((int) ((mDelay / 1000.0f) * (sampleRate)));
        delayLine[i].clear();
    }

}

void Delay1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Delay1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Delay1AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {        
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); sample++) 
        {
            channelData[sample] += delayLine[channel].get() * mFeedback;
            delayLine[channel].push(channelData[sample]);
        }        
    }
}

//==============================================================================
bool Delay1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Delay1AudioProcessor::createEditor()
{
    return new Delay1AudioProcessorEditor (*this);
}

//==============================================================================
void Delay1AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Delay1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Delay1AudioProcessor();
}

void mDelayLine::push(float value) 
{
    delayLine[readOffset] = value;
    readOffset = (readOffset + 1) % delayLine.size();
}

float mDelayLine::get()
{
    return delayLine[readOffset];
}

void mDelayLine::clear()
{
    for (int i = 0; i < delayLine.size(); i++)
    {
        delayLine[i] = 0.0f;
    }
}

void mDelayLine::updateSize(long int size) 
{
    delayLine.resize(size);
    readOffset = readOffset % delayLine.size();
}


