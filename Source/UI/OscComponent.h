/*
  ==============================================================================

    OscComponent.h
    Created: 4 Jun 2024 7:23:33pm
    Author:  Tyler

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String fmFreqID, juce::String fmDepthID);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscWaveSelector;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr <Attachment> fmFreqAttachment;
    juce::Label fmFreqLabel{ "FM Frequency", "FM Frequency" };
    
    std::unique_ptr <Attachment> fmDepthAttachment;
    juce::Label fmDepthLabel{ "FM Depth", "FM Depth" };
    
    juce::Label waveSelectorLabel{ "Wave Type", "Wave Type" };

    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr <Attachment>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
