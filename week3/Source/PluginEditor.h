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
class Week3AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Week3AudioProcessorEditor (Week3AudioProcessor&);
    ~Week3AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //CALL SLIDER INSTANCE--------------------
        juce::Slider mSlider;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Week3AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week3AudioProcessorEditor)
};