#pragma once

#include <JuceHeader.h>
#include "SineWave.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
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

private:
    //==============================================================================
    //CALL SLIDER INSTANCE--------------------
        juce::Slider OSCdataSlider;
    //-------INIT------------------------------
    SineWave mSineWave1;
    SineWave mSineWave1FMOperator;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
