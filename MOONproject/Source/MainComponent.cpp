#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    background = juce::ImageCache::getFromMemory (BinaryData::bdg_png, BinaryData::bdg_pngSize);
    
     //OSC PORT-----
    if (! connect (9001))
    {
        std::cout << "Error: could not connect to UDP port 9001.";
    }
    addListener(this, "/juceOSC"); //OSC ADDRESS
    
    //OSC SLIDER-------
    OSCdataSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    OSCdataSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 150, 20);
    OSCdataSlider.setRange(0.f, 4.f);
    addAndMakeVisible(OSCdataSlider);
    
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
    
    //INTERVAL BUTTONS-----
    addAndMakeVisible (M2Button);
    M2Button.addListener(this);
    
    addAndMakeVisible (m3Button);
    m3Button.addListener(this);
    addAndMakeVisible (M3Button);
    M3Button.addListener(this);
    
    addAndMakeVisible (p4Button);
    p4Button.addListener(this);
    addAndMakeVisible (p5Button);
    p5Button.addListener(this);
    
    addAndMakeVisible (M6Button);
    M6Button.addListener(this);
    addAndMakeVisible (M7Button);
    M7Button.addListener(this);
    
    addAndMakeVisible (p8Button);
    p8Button.addListener(this);
    
    //WAVEFORM VISUALISER-----
    addAndMakeVisible(visualiser);
    
    //----
    setAudioChannels (2, 2);
    setSize (1000, 600);
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
    
    visualiser.clear();
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto level = 0.125f;  //volume
    auto* leftBuffer  = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    auto* rightBuffer = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);

    for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        auto currentSample = (float) std::sin (currentAngle);
        currentAngle += angleDelta;
        leftBuffer[sample]  = currentSample * level;
        rightBuffer[sample] = currentSample * level;
    }
    visualiser.pushBuffer(bufferToFill);
}

void MainComponent::releaseResources(){}


/* PARSE OSC MESSAGE*/
void MainComponent::oscMessageReceived(const juce::OSCMessage& message)
{
    if(message.size() == 2 && message[0].isInt32())
    {
        int receivingData = message[0].getInt32();
        mStartingTunning = message[1].getInt32(); //call variable in header file
        
        //PRINT TO CONSOLE
            //DBG(receivingData);
            //std::cout << receivingData <<std::endl;
            //update value of slider
        
        //---------------OSC INPUT CHANGES PARAMETERS------------------------
        OSCdataSlider.setValue(receivingData);
        
//        if(receivingData == 0){frequencySlider.setValue(50);}
//        if(receivingData == 1){frequencySlider.setValue(mStartingTunning + 83);} //m3 = 83 freq interval
//        if(receivingData == 2){frequencySlider.setValue(mStartingTunning + 114);} //M3 = 114
//        if(receivingData == 3){frequencySlider.setValue(mStartingTunning + 147);} //p4 = 147
//        if(receivingData == 4){frequencySlider.setValue(mStartingTunning + 219);} //p5 = 219
        
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
    //g.fillAll (juce::Colours::wheat);
        g.drawImageAt (background, 0, 0);
    
    g.setColour (juce::Colours::lightgoldenrodyellow);
    g.setFont (13.0f);
    g.drawSingleLineText ("OSC position data", OSCdataSlider.getX()+15, OSCdataSlider.getBottom()+12);
}

void MainComponent::resized()
{
    getLookAndFeel().setColour (juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    
    //osc slider position---------------
    OSCdataSlider.setColour (juce::Slider::thumbColourId, juce::Colours::darkred);
    OSCdataSlider.setColour (juce::Slider::backgroundColourId, juce::Colours::darkred);
    OSCdataSlider.setColour (juce::Slider::textBoxTextColourId, juce::Colours::lightsalmon);
    OSCdataSlider.setBounds (268, 195, 10, 249);
    
    
    
    //freq slider position-------------------
    frequencySlider.setColour (juce::Slider::thumbColourId, juce::Colours::black);
    frequencySlider.setColour (juce::Slider::backgroundColourId, juce::Colours::black);
    frequencySlider.setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);
    frequencySlider.setBounds(745, 181, 8, 325);
    

    //interval button position-------------------
    M2Button.setColour (juce::TextButton::buttonColourId, juce::Colours::transparentWhite);
    m3Button.setColour (juce::TextButton::buttonColourId, juce::Colours::transparentWhite);
    M3Button.setColour (juce::TextButton::buttonColourId, juce::Colours::transparentWhite);
    p4Button.setColour (juce::TextButton::buttonColourId, juce::Colours::transparentWhite);
    p5Button.setColour (juce::TextButton::buttonColourId, juce::Colours::transparentWhite);
    M6Button.setColour (juce::TextButton::buttonColourId, juce::Colours::transparentWhite);
    M7Button.setColour (juce::TextButton::buttonColourId, juce::Colours::transparentWhite);
    p8Button.setColour (juce::TextButton::buttonColourId, juce::Colours::transparentWhite);
    
    M2Button.setBounds(754+2,184+1,29,32);
    
    m3Button.setBounds(754+2,222+1,29,32);
    M3Button.setBounds(754+2,262+1,29,32);
    
    p4Button.setBounds(754+2,300+1,29,32);
    p5Button.setBounds(754+2,335+1,29,32);
    
    M6Button.setBounds(754+2,375+1,29,32);
    M7Button.setBounds(754+2,414+1,29,32);
    
    p8Button.setBounds(754+2,454+1,29,32);
    
    //visualiser position-------------------
    visualiser.setColours(juce::Colour (255, 246, 223), juce::Colours::red); //background, waveform
    visualiser.setBounds(388, 320, 370, 31);
    visualiser.setTransform(juce::AffineTransform::rotation (1.5708, visualiser.getBounds().getCentreX(), visualiser.getBounds().getCentreY()));
}
