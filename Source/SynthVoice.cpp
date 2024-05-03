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
    gain.setGainLinear(0.01f);

    isPrepared = true;

}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
   
}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    juce::dsp::AudioBlock<float> audioBlock{outputBuffer};

    //proccess osciallator through buffer
    osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}