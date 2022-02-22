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
class Week4AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Week4AudioProcessorEditor (Week4AudioProcessor&);
    ~Week4AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //CALL SLIDER INSTANCE--------------------
        juce::Slider mSlider;
        juce::Slider m2Slider;
    
        juce::Slider fSlider;
        juce::Slider f2Slider;
    
        juce::ToggleButton switchButton;
        
        /* This is a helpful juce class to attach our slider to our value tree */
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mSliderAttachment;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m2SliderAttachment;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fSliderAttachment;
        std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> f2SliderAttachment;
    
        std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> switchButtonAttachment;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Week4AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week4AudioProcessorEditor)
};
