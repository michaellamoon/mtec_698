/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterDefines.h"

//==============================================================================
Week4AudioProcessorEditor::Week4AudioProcessorEditor (Week4AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //-----SLIDER1-------------------
    //vol
    mSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    mSlider.setRange(0.f, 1.f);
    addAndMakeVisible(mSlider);
    
    mSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment
                            (audioProcessor.getValueTreeState(),PARAMETER_NAMES[GAIN_AMOUNT], mSlider));
    
    //freq
    fSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    fSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    fSlider.setRange(0.f, 1.f);
    addAndMakeVisible(fSlider);
    
    fSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment
                            (audioProcessor.getValueTreeState(),PARAMETER_NAMES[FM_AMOUNT], fSlider));
    
    
    //-----SLIDER2-------------------
    m2Slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    m2Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    m2Slider.setRange(0.f, 1.f);
    addAndMakeVisible(m2Slider);
    
    m2SliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment
                            (audioProcessor.getValueTreeState(),PARAMETER_NAMES[GAIN_AMOUNT2], m2Slider));
    
    //freq
    f2Slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    f2Slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    f2Slider.setRange(0.f, 1.f);
    addAndMakeVisible(f2Slider);
    
    f2SliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment
                            (audioProcessor.getValueTreeState(),PARAMETER_NAMES[FM_AMOUNT2], f2Slider));
    
    
    setSize(400, 300);
}

Week4AudioProcessorEditor::~Week4AudioProcessorEditor()
{
}

//==============================================================================
void Week4AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::lightgreen);

    g.setColour (juce::Colours::lightsalmon);
    g.setFont (15.0f);
    g.drawFittedText ("sine1 vol", getLocalBounds(), juce::Justification::centredLeft, 1);
    g.drawFittedText ("sine1 FM", getLocalBounds(), juce::Justification::bottomLeft, 1);
    g.drawFittedText("sine2 vol", getLocalBounds(), juce::Justification::centredRight, 1);
    g.drawFittedText ("sine2 FM", getLocalBounds(), juce::Justification::bottomRight, 1);
 
}

void Week4AudioProcessorEditor::resized()
{
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::lightsalmon);
    // silder1 position---------------
    mSlider.setBounds(0, 0, 150, 150);
    fSlider.setBounds(0, 170, 150, 100);
    // silder2 position---------------
    m2Slider.setBounds(250, 0, 150, 150);
    f2Slider.setBounds(250, 170, 150, 100);
}
