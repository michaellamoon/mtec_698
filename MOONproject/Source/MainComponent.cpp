#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setAudioChannels (2, 2);
    
     //OSC PORT-----
    if (! connect (9001))
    {
        std::cout << "Error: could not connect to UDP port 9001.";
    }
    addListener(this, "/juceOSC"); //OSC ADDRESS
    
    //SLIDER-------
    OSCdataSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    OSCdataSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    OSCdataSlider.setRange(0.f, 4.f);
    addAndMakeVisible(OSCdataSlider);
    
    
    setSize (800, 600);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // Initialize our sine wave--------------------------------------
        mSineWave1.initialize(442, sampleRate);
        mSineWave1FMOperator.initialize(442, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}
/* PARSE OSC MESSAGE*/
void MainComponent::oscMessageReceived(const juce::OSCMessage& message)
{
    if(message.size() == 1 && message[0].isInt32())
    {
        int receivingData = message[0].getInt32();
        
        //PRINT TO CONSOLE
            //DBG(receivingData);
            //std::cout << receivingData <<std::endl;
            //update value of slider
        
        OSCdataSlider.setValue(receivingData);
    }
}
//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::lightgoldenrodyellow);
    
    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawSingleLineText ("OSC position data", OSCdataSlider.getX()+15, OSCdataSlider.getBottom()+12);

}

void MainComponent::resized()
{
    // silder1 position---------------
    getLookAndFeel().setColour (juce::Slider::thumbColourId, juce::Colours::lightsalmon);
    getLookAndFeel().setColour (juce::Slider::backgroundColourId, juce::Colours::lightsalmon);
    getLookAndFeel().setColour (juce::Slider::textBoxBackgroundColourId, juce::Colours::lightsalmon);
    OSCdataSlider.setBounds(60, 60, 150, 150);
}
