/*
  ==============================================================================

    SynthVoice.h
    Created: 22 Apr 2024 7:13:34pm
    Author:  SHEEVZ

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice {
public:
    //Must return true if this voice object is capable of playing the given sound.
    bool canPlaySound(juce::SynthesiserSound* sound) override;

    //Called to start a new note.
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;

    //Called to stop a note.
    void stopNote(float velocity, bool allowTailOff) override;

    //Called to let the voice know that the pitch wheel has been moved
    void pitchWheelMoved(int newPitchWheelValue) override;

    //Called to let the voice know that a midi controller has been moved.
    void controllerMoved(int controllerNumber, int newControllerValue) override;

    //Renders the next block of data for this voice.
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;
};