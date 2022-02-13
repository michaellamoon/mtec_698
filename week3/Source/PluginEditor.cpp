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
    
    
    setSize(400, 300);
}

Week3AudioProcessorEditor::~Week3AudioProcessorEditor()
{
}

//==============================================================================
void Week3AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
/*
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
 */
}

void Week3AudioProcessorEditor::resized()
{
    // silder1 position---------------
    mSlider.setBounds(0, 0, 150, 150);
}
