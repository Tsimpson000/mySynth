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
#include "Data/AdsrData.h"
#include "Data/OscData.h"
#include "Data/FilterData.h"

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


    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);

    //Called to let the voice know that a midi controller has been moved.
    void controllerMoved(int controllerNumber, int newControllerValue) override;

    //Renders the next block of data for this voice.
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;

    //void updateAdsr(const float attack, const float decay, const float sustain, const float release);

    void updateFilter(const int filterType, const float cutoff, const float resonance);
    //void updateModAdsr(const float attack, const float decay, const float sustain, const float release);

    OscData& getOscillator() { return osc; }
    AdsrData& getAdsr() { return adsr; }
    AdsrData& getFilterAdsr() { return filterAdsr; }
    FilterData& getFilter() { return filter; }
private:
    juce::AudioBuffer<float> synthBuffer;

    OscData osc;
    AdsrData adsr;
    FilterData filter;
    AdsrData filterAdsr;
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };
};