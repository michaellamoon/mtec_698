/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Week3AudioProcessorEditor::Week3AudioProcessorEditor (Week3AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //-----SLIDER1-------------------
    mSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    mSlider.setRange(0.f, 1.f);
    addAndMakeVisible(mSlider);
    
    mSlider.onValueChange = [this]() {
        audioProcessor.setSineVolume(mSlider.getValue());
    };
    //update value of slider
    mSlider.setValue(audioProcessor.getSineVolume());
    
    //-----SLIDER2-------------------
    m2Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    m2Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    m2Slider.setRange(0.f, 1.f);
    addAndMakeVisible(m2Slider);
    
    m2Slider.onValueChange = [this]() {
        audioProcessor.setSineVolume(m2Slider.getValue());
    };
    //update value of slider
    m2Slider.setValue(audioProcessor.getSineVolume());
    
    
    setSize(400, 300);
}

Week3AudioProcessorEditor::~Week3AudioProcessorEditor()
{
}

//==============================================================================
void Week3AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::lightgreen);

    g.setColour (juce::Colours::lightsalmon);
    g.setFont (15.0f);
    g.drawFittedText ("sine1 vol", getLocalBounds(), juce::Justification::centredLeft, 1);
    g.drawFittedText("sine2 vol", getLocalBounds(), juce::Justification::centredRight, 1);
 
}

void Week3AudioProcessorEditor::resized()
{
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::lightsalmon);
    // silder1 position---------------
    mSlider.setBounds(0, 0, 150, 150);
    // silder2 position---------------
    m2Slider.setBounds(250, 0, 150, 150);
}
