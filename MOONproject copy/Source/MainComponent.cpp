#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    /* declare a vector of parameters */
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    /* loop through our parameter defines and add the parameters to the vector */
    for (int i = 0; i < TotalNumberParameters; i++) {
        parameters.push_back(std::make_unique<juce::AudioParameterFloat>(PARAMETER_NAMES[i], PARAMETER_NAMES[i], PARAMETER_RANGES[i], 1.f));
    }

    /* construct the parameter tree object -- this will actually add all the parameters to our plugin */
    mParameterState.reset(new juce::AudioProcessorValueTreeState(*this, nullptr, "PARAMETER_STATE", { parameters.begin(), parameters.end() }));

    /* now lets get pointers which point to the current values of the parameters, we can use these in our processing loops */
    for (int i = 0; i < TotalNumberParameters; i++) {
        mParameterValues[i] = mParameterState->getRawParameterValue(PARAMETER_NAMES[i]);
        
        
        
        
    
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
void MainComponent::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSineWavePlug.initialize(442, sampleRate);
    fSineWavePlug.initialize(442, sampleRate);
    
    visualiser.clear();
}

void MainComponent::getNextAudioBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
    {
        juce::ScopedNoDenormals noDenormals;
        auto totalNumInputChannels  = getTotalNumInputChannels();
        auto totalNumOutputChannels = getTotalNumOutputChannels();

        
        for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
             buffer.clear (i, 0, buffer.getNumSamples());
        
        //---------
        mSineWavePlug.setGain(mParameterValues[GAIN_AMOUNT]->load());
        fSineWavePlug.setGain(mParameterValues[FM_AMOUNT]->load());
        
         
         // FOR EACH SAMPLE IN THE INCOMING AUDIO BUFFER
         for (int sample_index = 0; sample_index < buffer.getNumSamples(); sample_index++) {
             
             float fm_operator = fSineWavePlug.getNextSample();
             
             float output = mSineWavePlug.getNextSampleWithFM(fm_operator);
                 
                 // STORE THE OUTPUT TO THE LEFT AND RIGHT CHANNELS OF THE AUDIO BUFFER
                 buffer.setSample(0, sample_index, output);
                 buffer.setSample(1, sample_index, output);
             }
         }
        
    visualiser.pushBuffer(buffer);
}

void MainComponent::releaseResources(){}

    //==============================================================================
    juce::AudioProcessorValueTreeState& Week4AudioProcessor::getValueTreeState()
    {
        return *mParameterState.get();
    }
    
    void Week4AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
    {
        // Get the underlying ValueTree from out "Parameter Value Tree"
        auto tree_state = mParameterState->copyState();
        
        // Convert the value tree into an XML object which can be saved on disk to as binary
        std::unique_ptr<juce::XmlElement> xml(tree_state.createXml());
        
        /* */
        DBG(xml->toString());

        /* store as binary */
        copyXmlToBinary(*xml, destData);
    }

    void Week4AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
    {
        std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

        if (xmlState.get()) {
            
            DBG(xmlState->toString());
            
            juce::ValueTree parameter_tree = juce::ValueTree::fromXml(*xmlState);
            mParameterState->replaceState(parameter_tree);
        }
    }
    
    
    

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

void MainComponent::updateAngleDelta2()
{
    auto cyclesPerSample2 = fmSlider.getValue() / currentSampleRate2;         //calculate number of cycles for each output sample
    angleDelta2 = cyclesPerSample2 * 2.0 * juce::MathConstants<double>::pi;          //multipled by length of whole sine wave cycle (2pi radians)
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
    mSlider.setBounds(0, 3, 130, 130);
    fSlider.setBounds(0, 170, 150, 100);

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
    //visualiser.setTransform(const juce::AffineTransform::rotation (1.5708).translated);
    visualiser.setBounds(557, 150, 31, 370);
    
}
