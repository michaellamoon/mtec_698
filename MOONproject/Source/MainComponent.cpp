#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
     //OSC PORT-----
    if (! connect (9001))
    {
        std::cout << "Error: could not connect to UDP port 9001.";
    }
    addListener(this, "/juceOSC"); //OSC ADDRESS
    
    //OSC SLIDER-------
    OSCdataSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    OSCdataSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    OSCdataSlider.setRange(0.f, 4.f);
    addAndMakeVisible(OSCdataSlider);
    
    setAudioChannels (2, 2);
    setSize (800, 600);
    
    //FREQ GEN-----
    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 20);
    frequencySlider.setRange (50.0, 5000.0);
    frequencySlider.onValueChange = [this]
    {
        if (currentSampleRate > 0.0)
            updateAngleDelta();
    };
    addAndMakeVisible (frequencySlider);
    
    //----
    
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    currentSampleRate = sampleRate;
    updateAngleDelta();
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto level = 0.125f;
    auto* leftBuffer  = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    auto* rightBuffer = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);

    for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        auto currentSample = (float) std::sin (currentAngle);
        currentAngle += angleDelta;
        leftBuffer[sample]  = currentSample * level;
        rightBuffer[sample] = currentSample * level;
    }
}

void MainComponent::releaseResources(){}


/* PARSE OSC MESSAGE*/
void MainComponent::oscMessageReceived(const juce::OSCMessage& message)
{
    if(message.size() == 2 && message[0].isInt32())
    {
        int receivingData = message[0].getInt32();
        int startingTunning = message[1].getInt32();
        
        //PRINT TO CONSOLE
            //DBG(receivingData);
            //std::cout << receivingData <<std::endl;
            //update value of slider
        
        //---------------OSC INPUT CHANGES PARAMETERS------------------------
        OSCdataSlider.setValue(receivingData);
        
        if(receivingData == 1){frequencySlider.setValue(startingTunning + 83);} //m3 = 83 freq interval
        if(receivingData == 2){frequencySlider.setValue(startingTunning + 114);} //M3 = 114
        if(receivingData == 3){frequencySlider.setValue(startingTunning + 147);} //p4 = 147
        if(receivingData == 4){frequencySlider.setValue(startingTunning + 219);} //p5 = 219
    }
}
/*FREQ GENERATOR*/
void MainComponent::updateAngleDelta()
{
    auto cyclesPerSample = frequencySlider.getValue() / currentSampleRate;         //calculate number of cycles for each output sample
    angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;          //multipled by length of whole sine wave cycle (2pi radians)
}
//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::wheat);
    
    g.setColour (juce::Colours::lightgoldenrodyellow);
    g.setFont (13.0f);
    g.drawSingleLineText ("OSC position data", OSCdataSlider.getX()+15, OSCdataSlider.getBottom()+12);
    g.drawSingleLineText ("freq/pitch", frequencySlider.getX()+15, frequencySlider.getBottom()+12);

}

void MainComponent::resized()
{
    getLookAndFeel().setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    
    //osc slider position---------------
    OSCdataSlider.setColour (juce::Slider::thumbColourId, juce::Colours::lightsalmon);
    OSCdataSlider.setColour (juce::Slider::backgroundColourId, juce::Colours::lightsalmon);
    OSCdataSlider.setColour (juce::Slider::textBoxTextColourId, juce::Colours::lightsalmon);
    OSCdataSlider.setBounds (100, 20, 150, getHeight()-100);
    
    //freq slider position-------------------
    frequencySlider.setColour (juce::Slider::thumbColourId, juce::Colours::black);
    frequencySlider.setColour (juce::Slider::backgroundColourId, juce::Colours::black);
    frequencySlider.setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);
    frequencySlider.setBounds(getWidth()-150, 20, 150, getHeight()-100);
    
}
