/*
  ==============================================================================

    OscData.h
    Created: 4 Jun 2024 3:39:00pm
    Author:  Tyler

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void setWaveFreq(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);

private:

};