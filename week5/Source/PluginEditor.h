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
class Week5AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Week5AudioProcessorEditor (Week5AudioProcessor&);
    ~Week5AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //CALL SLIDER INSTANCE--------------------
    juce::Slider mGainAmountSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mGainAmountSliderAttachment;
    
    juce::Slider mFMAmountSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mFMAmountSliderAttachment;
    
    juce::Slider mFMFreqSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mFMFreqSliderAttachment;
    
    juce::Slider mDelayTimeSecondsSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDelayTimeSecondsSliderAttachment;
    
    juce::Slider mDelayFeedbackSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDelayFeedbackSliderAttachment;
    
    juce::Slider mDelayMixSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mDelayMixSliderAttachment;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Week5AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week5AudioProcessorEditor)
};
