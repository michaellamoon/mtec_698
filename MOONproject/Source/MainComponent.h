#pragma once

#include <JuceHeader.h>
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
    void releaseResources() override;

    void oscMessageReceived (const juce::OSCMessage& message) override;
    //==============================================================================
    void resized() override;
    void paint (juce::Graphics& g) override;
    void updateAngleDelta();
    //==============================================================================
    void buttonClicked (juce::Button* button) override  
       {
           //---------------BUTTONS CHANGES PARAMETERS------------------------
           if (button == &M2Button)
           {
               frequencySlider.setValue(mStartingTunning + 32.03);
           }
           if (button == &m3Button)
           {
               frequencySlider.setValue(mStartingTunning + 49.5);
           }
           if (button == &M3Button)
           {
               frequencySlider.setValue(mStartingTunning + 68);
           }
           if (button == &p4Button)
           {
               frequencySlider.setValue(mStartingTunning + 87.6);
           }
           if (button == &p5Button)
           {
               frequencySlider.setValue(mStartingTunning + 130.37);
           }
           if (button == &M6Button)
           {
               frequencySlider.setValue(mStartingTunning + 178.37);
           }
           if (button == &M7Button)
           {
               frequencySlider.setValue(mStartingTunning + 232.25);
           }
           if (button == &p8Button)
           {
               frequencySlider.setValue(mStartingTunning + 261.62);
           }
       }

private:
    int mStartingTunning = 440;
    //==============================================================================
    //-------OSC DATA INPUT SLIDER-----------------------------
        juce::Slider OSCdataSlider;
    //-------FREQ GENERATOR SLIDER------------------------------
        juce::Slider frequencySlider;
        double currentSampleRate = 0.0, currentAngle = 0.0, angleDelta = 0.0;
    //------BUTTONS----------------------------------------------
        juce::TextButton M2Button, m3Button, M3Button, p4Button, p5Button, M6Button,
        M7Button, p8Button;
    //------images----------------------------------------------
        juce::Image background;
    //------vu meter----------------------------------------------
        Visualiser visualiser;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

