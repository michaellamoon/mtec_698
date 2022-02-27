/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "SineWave.h"
#include "Delay.h"
#include "ParameterManager.h"

//==============================================================================
class Week5AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Week5AudioProcessor();
    ~Week5AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getStateInformation (juce::MemoryBlock& destData) override;       //DAW CALL PLUGIN STATE
    void setStateInformation (const void* data, int sizeInBytes) override; //DAW SETS CURRENT STATE
    ParameterManager* getParameterManager();               //RETURN VALUE TREE STATE TO DAW

    /* called before destruction to free data (rarely used with modern cpp) */
    void releaseResources() override;
    
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;


private:
    
    //-------INIT------------------------------
    SineWave mSineWave1;
    SineWave mSineWave1FMOperator;
    
    Delay mDelayLeft;
    Delay mDelayRight;
    
    /* this will be our "parameter tree" */
    std::unique_ptr<ParameterManager> mParameterManager;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week5AudioProcessor)
};
