/*
  ==============================================================================

    AdsrData.cpp
    Created: 4 Jun 2024 2:56:42pm
    Author:  Tyler

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::update(const float attack, const float decay, const float sustain, const float release)
{
    adsrParameters.attack = attack;
    adsrParameters.decay = decay;
    adsrParameters.sustain = sustain;
    adsrParameters.release = release;

    setParameters(adsrParameters);
}