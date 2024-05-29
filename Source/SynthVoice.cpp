/*
  ==============================================================================

    SynthVoice.cpp
    Created: 22 Apr 2024 7:13:34pm
    Author:  SHEEVZ

  ==============================================================================
*/

#include "SynthVoice.h"


bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    //retrieve MIDI data to play pitch in hertz
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();

    if (!allowTailOff || !adsr.isActive()) 
    {
        clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) 
{

}


void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) 
{
// Use this method as the place to do any pre-playback
// initialisation that you need..


    adsr.setSampleRate(sampleRate);
    

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepare(spec);

    gain.prepare(spec);
    gain.setGainLinear(0.2f);

    isPrepared = true;

}

void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParameters.attack = attack;
    adsrParameters.decay = decay;
    adsrParameters.sustain = sustain;
    adsrParameters.release = release;

    adsr.setParameters(adsrParameters);
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
   
}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive())
        return;
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };

    //proccess osciallator through buffer
    osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) 
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (! adsr.isActive())
        {
            clearCurrentNote();
        }
    }
}