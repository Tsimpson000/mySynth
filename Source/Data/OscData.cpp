/*
  ==============================================================================

    OscData.cpp
    Created: 4 Jun 2024 3:39:00pm
    Author:  Tyler

  ==============================================================================
*/

#include "OscData.h"
void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    prepare(spec);
    fmOsc.prepare(spec);
    
}
void OscData::setWaveType(const int choice) 
{

        switch (choice)
        {
        //sine wave
        case 0:
            initialise([](float x) {return std::sin(x);});
            break;

        //saw wave
        case 1:
            initialise([](float x) {return x / juce::MathConstants<float>::pi;});
            break;
        //square wave
        case 2:
            initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f;});
            break;
        default:
            //something went wrong
            jassertfalse;
            break;
        }
}

void OscData::setWaveFreq(const int midiNoteNumber) 
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
    lastMidi = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    processFmOsc(block);
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::processFmOsc(juce::dsp::AudioBlock<float>& block)
{
    for (int ch = 0; ch < block.getNumChannels(); ++ch) 
    {
        for (int s = 0; s < block.getNumSamples(); ++s) 
        {
            fmMod = fmOsc.processSample(block.getSample(ch, s)) * fmDepth;
        }
    }
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::updateFm(const float freq, const float depth)
{
    fmOsc.setFrequency(freq);
    fmDepth = depth;
    auto currentFreq = juce::MidiMessage::getMidiNoteInHertz(lastMidi) + fmMod;
    setFrequency(currentFreq >= 0 ? currentFreq : currentFreq * -1.0f);
}