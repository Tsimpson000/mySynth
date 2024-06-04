/*
  ==============================================================================

    AdsrComponent.h
    Created: 4 Jun 2024 2:55:40pm
    Author:  Tyler

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSliderParams(juce::Slider& slider);

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    using SliderAttahment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttahment> attackSliderAttachment;
    std::unique_ptr<SliderAttahment> decaySliderAttachment;
    std::unique_ptr<SliderAttahment>  sustainSliderAttachment;
    std::unique_ptr<SliderAttahment> releaseSliderAttachment;
 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
