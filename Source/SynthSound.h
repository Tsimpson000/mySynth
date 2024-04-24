/*
  ==============================================================================

    SynthSound.h
    Created: 22 Apr 2024 7:14:05pm
    Author:  SHEEVZ

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {
    //create public functions
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};