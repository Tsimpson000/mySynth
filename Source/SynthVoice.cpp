/*
  ==============================================================================

    SynthVoice.cpp
    Created: 22 Apr 2024 7:13:34pm
    Author:  Tyler

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
    osc.setWaveFreq(midiNoteNumber);
    adsr.noteOn();
    filterAdsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    filterAdsr.noteOff();

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
    

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    synthBuffer.setSize(outputChannels, samplesPerBlock, false, true, true);

    osc.prepareToPlay(spec);
    adsr.setSampleRate(sampleRate);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    filterAdsr.setSampleRate(sampleRate);
    gain.prepare(spec);


    gain.setGainLinear(0.2f);

    isPrepared = true;

}

//void SynthVoice::updateAdsr(const float attack, const float decay, const float sustain, const float release)
//{
//    adsr.update(attack, decay, sustain, release);
//}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
   
}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive())
        return;
    
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };

    //proccess osciallator through buffer
    osc.getNextAudioBlock(audioBlock);
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    filter.process(synthBuffer);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) 
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
    }

}

void SynthVoice::updateFilter(const int filterType, const float cutoff, const float resonance)
{
    float modulator = filterAdsr.getNextSample();
    filter.updateParameters(filterType, cutoff, resonance, modulator);
}

//void SynthVoice::updateModAdsr(const float attack, const float decay, const float sustain, const float release)
//{
//    filterAdsr.update(attack, decay, sustain, release);
//}