/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MySynthAudioProcessorEditor::MySynthAudioProcessorEditor (MySynthAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , audioProcessor (p)
    , osc (audioProcessor.apvts, "OSC1WAVETYPE", "FMFREQ", "FMDEPTH")
    , adsr("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE")
    , filterAdsr("Mod Envelope", audioProcessor.apvts, "FILTERATTACK", "FILTERDECAY", "FILTERSUSTAIN", "FILTERRELEASE")
    , filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
{

    //plugin window size
    setSize (620, 500);

    //make oscillator visible
    addAndMakeVisible(osc);
    //make adsr visible
    addAndMakeVisible(adsr);
    //make filter visible
    addAndMakeVisible(filter);

    addAndMakeVisible(filterAdsr);
    
}

MySynthAudioProcessorEditor::~MySynthAudioProcessorEditor()
{
}

//==============================================================================
void MySynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    //Our component is opaque, so we must completely fill the background with a solid colour
    g.fillAll (juce::Colours::black);

}

void MySynthAudioProcessorEditor::resized()
{
    const auto paddingX = 5;
    const auto paddingY = 35;
    const auto paddingY2 = 235;

    osc.setBounds(paddingX, paddingY, 300, 200);
    adsr.setBounds(osc.getRight(), paddingY, 300, 200);
    filterAdsr.setBounds(paddingX, paddingY2, 300, 200);
    filter.setBounds(filterAdsr.getRight(), paddingY2, 300, 200);
}


