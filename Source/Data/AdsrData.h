/*
  ==============================================================================

    AdsrData.h
    Created: 4 Jun 2024 2:56:42pm
    Author:  Tyler

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
    //declare ADSR parameter objects
    juce::ADSR::Parameters adsrParameters;
};