/*
  ==============================================================================

    FilterComponent.h
    Created: 20 Jun 2024 8:48:46am
    Author:  Tyler

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterFreqId, juce::String filterResId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterTypeSelector{ "Filter Type" };
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;


    juce::Slider filterFreqSlider;
    juce::Slider filterResSlider;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr <Attachment> filterFreqAttachment;
    juce::Label filterFreqLabel{ "Filter Frequency", "Filter Frequency" };

    std::unique_ptr <Attachment> filterResAttachment;
    juce::Label filterResLabel{ "Filter Resonance", "Filter Resonance" };

    juce::Label filterTypeSelectorLabel{ "Filter Type", "Filter Type" };

    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr <Attachment>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
