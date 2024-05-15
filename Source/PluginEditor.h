/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MySynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MySynthAudioProcessorEditor (MySynthAudioProcessor&);
    ~MySynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSliderParams(juce::Slider& slider);

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    juce::ComboBox oscSelect;

    using SliderAttahment = juce::AudioProcessorValueTreeState::SliderAttachment;

    //Setting up a mechanism to manage the lifecycle of a SliderAttachment object. 
    //This is often done when you want to create dynamic objects with a limited scope or when you want to properly cleanup resources.
    std::unique_ptr<SliderAttahment> attackSliderAttachment;
    std::unique_ptr<SliderAttahment> decaySliderAttachment;
    std::unique_ptr<SliderAttahment>  sustainSliderAttachment;
    std::unique_ptr<SliderAttahment> releaseSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelectAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MySynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MySynthAudioProcessorEditor)
};
