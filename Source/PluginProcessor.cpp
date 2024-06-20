/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MySynthAudioProcessor::MySynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

MySynthAudioProcessor::~MySynthAudioProcessor()
{
}

//==============================================================================
const juce::String MySynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MySynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MySynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MySynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MySynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MySynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MySynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MySynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MySynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void MySynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MySynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);

    //if succesffuly cast as synth , call prepareToPlay method
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void MySynthAudioProcessor::releaseResources()
{
     // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MySynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void MySynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

 
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //if our synth voice is correctly casting as a JUCE synth voice
    for (int i = 0; i < synth.getNumVoices(); ++i) 
    {
        //if our voice is calling from SynthVoice
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) 
        {
            //adsr
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            //osc wave
            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");

            //LFO
            auto& fmDepth = *apvts.getRawParameterValue("FMDEPTH");
            auto& fmFrequency = *apvts.getRawParameterValue("FMFREQ");

            //Filter
            auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
            auto& filterCutoff = *apvts.getRawParameterValue("FILTERFREQ");
            auto& filterRes = *apvts.getRawParameterValue("FILTERRES");

            //Filter Adsr
            auto& fAttack = *apvts.getRawParameterValue("FILTERATTACK");
            auto& fDecay = *apvts.getRawParameterValue("FILTERDECAY");
            auto& fSustain = *apvts.getRawParameterValue("FILTERSUSTAIN");
            auto& fRelease = *apvts.getRawParameterValue("FILTERRELEASE");

                voice->getOscillator().setWaveType (oscWaveChoice);
                voice->getOscillator().updateFm (fmFrequency, fmDepth);
                voice->getAdsr().update (attack.load(), decay.load(), sustain.load(), release.load());
                voice->getFilterAdsr().update (fAttack.load(), fDecay.load(), fSustain.load(), fRelease.load());
                voice->updateFilter (filterType, filterCutoff, filterRes);
            
        }
    }

    //output sound
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool MySynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MySynthAudioProcessor::createEditor()
{
    return new MySynthAudioProcessorEditor (*this);
}

//==============================================================================
void MySynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MySynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MySynthAudioProcessor();
}

//Value Tree
juce::AudioProcessorValueTreeState::ParameterLayout MySynthAudioProcessor::createParameters() 
{
    
    //create vector to return parameter layout
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //FM mod
    ///parameter used to select FM Frequency
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "FMFREQ", 1 }, "FM Frequency", juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.3f}, 0.0f));
    ///parameter used to select Frequency Depth
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "FMDEPTH", 1 }, "FM Depth", juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.3f}, 0.0f));


    //ADSR Envelope
    ///parameter used to select Attack 
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "ATTACK", 1 }, "Attack", juce::NormalisableRange<float>{0.1f, 1.0f, 0.01f}, 0.1f));
    ///parameter used to select Decay
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "DECAY", 1 }, "Decay", juce::NormalisableRange<float>{0.1f, 1.0f, 0.01f}, 0.1f));
    ///parameter used to select Sustain
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "SUSTAIN", 1 }, "Sustain", juce::NormalisableRange<float>{0.1f, 1.0f, 0.01f}, 1.0f));
    ///parameter used to select Release
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{ "RELEASE", 1 }, "Release", juce::NormalisableRange<float>{0.1f, 3.0f, 0.01f}, 0.1f));

    //Wave form selector
    //parameter used to select wave type
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    //Filter
    ///parameter used to select filter type
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray{ "Low-Pass", "Band-Pass", "High-Pass" }, 0));
    ///parameter used to select filter frequency
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERFREQ", "Filter Freq", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 200.0f));
    ///parameter used to select filter resonance
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES", "Filter Resonance", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f));


    //Filter ADSR Envelope
    ///parameter used to select Attack 
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERATTACK", "Filter Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    ///parameter used to select Release 
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERDECAY", "Filter Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    ///parameter used to select Sustain 
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERSUSTAIN", "Filter Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    ///parameter used to select Release 
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRELEASE", "Filter Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));

    //return vector
    return { params.begin(), params.end() };

}
