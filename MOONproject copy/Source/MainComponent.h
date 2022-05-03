#pragma once

#include <JuceHeader.h>
#include "SineWave.h"
#include "ParameterDefines.h"

class Visualiser : public juce::AudioVisualiserComponent
{
public:
    Visualiser() : juce::AudioVisualiserComponent (1)
    {
        setBufferSize(128);
        setSamplesPerBlock(16);
    }
};
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
                       public juce::Button::Listener,
                        private juce::OSCReceiver,
                        private juce::OSCReceiver::ListenerWithOSCAddress
                        <juce::OSCReceiver::MessageLoopCallback>
                    //inherit juce module "OSCReceiver"
                    //inherit abstract class, print on message thread (RealtimeCallback: print on own osc thread) -PURE VIRTUAL FUNCTION NEEDS OWN FUNCTION (in cpp)
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    
    void getStateInformation (juce::MemoryBlock& destData);       //DAW CALL PLUGIN STATE
    void setStateInformation (const void* data, int sizeInBytes); //DAW SETS CURRENT STATE
    juce::AudioProcessorValueTreeState& getValueTreeState();               //RETURN VALUE TREE STATE TO DAW
    
    void releaseResources() override;

    void oscMessageReceived (const juce::OSCMessage& message) override;
    //==============================================================================
    void resized() override;
    void paint (juce::Graphics& g) override;
    void updateAngleDelta();
    void updateAngleDelta2();
    //==============================================================================
    void buttonClicked (juce::Button* button) override  
       {
           //---------------BUTTONS CHANGES PARAMETERS------------------------
           if (button == &M2Button)
           {
               fSlider.setValue(mStartingTunning + 32.03);
           }
           if (button == &m3Button)
           {
               fSlider.setValue(mStartingTunning + 49.5);
           }
           if (button == &M3Button)
           {
               fSlider.setValue(mStartingTunning + 68);
           }
           if (button == &p4Button)
           {
               fSlider.setValue(mStartingTunning + 87.6);
           }
           if (button == &p5Button)
           {
               fSlider.setValue(mStartingTunning + 130.37);
           }
           if (button == &M6Button)
           {
               fSlider.setValue(mStartingTunning + 178.37);
           }
           if (button == &M7Button)
           {
               fSlider.setValue(mStartingTunning + 232.25);
           }
           if (button == &p8Button)
           {
               fSlider.setValue(mStartingTunning + 261.62);
           }
       }

private:
    int mStartingTunning = 440;
    //==============================================================================
    //-------OSC DATA INPUT SLIDER-----------------------------
        juce::Slider OSCdataSlider;
    //-------FREQ GENERATOR SLIDER------------------------------
    SineWave mSineWavePlug;
    SineWave fSineWavePlug;
    
    juce::Slider mSlider;
    juce::Slider fSlider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fSliderAttachment;
    /* this will be our "parameter tree" */
    std::unique_ptr<juce::AudioProcessorValueTreeState> mParameterState;
    /*guarantees thread safe read and write access*/
    std::array<std::atomic<float>*, TotalNumberParameters> mParameterValues;
    //------BUTTONS----------------------------------------------
        juce::TextButton M2Button, m3Button, M3Button, p4Button, p5Button, M6Button,
        M7Button, p8Button;
    //------images----------------------------------------------
        juce::Image background;
    //------vu meter----------------------------------------------
        Visualiser visualiser;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

