/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterDefines.h"

//==============================================================================
Week5AudioProcessorEditor::Week5AudioProcessorEditor (Week5AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    mGainAmountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mGainAmountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mGainAmountSlider);
    
    mFMAmountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFMAmountSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mFMAmountSlider);
    
    mFMFreqSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mFMFreqSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mFMFreqSlider);
    
    mDelayTimeSecondsSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayTimeSecondsSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mDelayTimeSecondsSlider);
    
    mDelayFeedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayFeedbackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mDelayFeedbackSlider);
    
    mDelayMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mDelayMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    addAndMakeVisible(mDelayMixSlider);
    
    //------------
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    auto* value_tree = audioProcessor.getParameterManager()->getValueTree();
    
    mGainAmountSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[SINE_GAIN], mGainAmountSlider));
    mFMAmountSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[SINE_FM_AMOUNT], mFMAmountSlider));
    mFMFreqSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[SINE_FM_FREQUENCY], mFMFreqSlider));
    mDelayTimeSecondsSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[DELAY_TIME_SECONDS], mDelayTimeSecondsSlider));
    mDelayFeedbackSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[DELAY_FEEDBACK], mDelayFeedbackSlider));
    mDelayMixSliderAttachment.reset(new SliderAttachment(*value_tree, PARAMETER_NAMES[DELAY_MIX], mDelayMixSlider));
    
    setSize(400, 300);
}

Week5AudioProcessorEditor::~Week5AudioProcessorEditor()
{
}

//==============================================================================
void Week5AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::lightgreen);

    g.setColour (juce::Colours::lightsalmon);
    g.setFont (juce::Font(12));
    g.drawSingleLineText("Gain", mGainAmountSlider.getX(), mGainAmountSlider.getBottom()+12);
    g.drawSingleLineText("FM Amount", mFMAmountSlider.getX(), mFMAmountSlider.getBottom()+12);
    g.drawSingleLineText("FM Freq", mFMFreqSlider.getX(), mFMFreqSlider.getBottom()+12);
    g.drawSingleLineText("Delay Time", mDelayTimeSecondsSlider.getX(), mDelayTimeSecondsSlider.getBottom()+12);
    g.drawSingleLineText("Delay Feedback", mDelayFeedbackSlider.getX(), mDelayFeedbackSlider.getBottom()+12);
    g.drawSingleLineText("Delay Mix", mDelayMixSlider.getX(), mDelayMixSlider.getBottom()+12);
 
}

void Week5AudioProcessorEditor::resized()
{
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::lightsalmon);
    mGainAmountSlider.setBounds(0, 0, 75, 75);
    mFMAmountSlider.setBounds(100, 0, 75, 75);
    mFMFreqSlider.setBounds(200, 0, 75, 75);
    mDelayTimeSecondsSlider.setBounds(0, 87, 75, 75);
    mDelayFeedbackSlider.setBounds(100, 87, 75, 75);
    mDelayMixSlider.setBounds(200, 87, 75, 75);
}
