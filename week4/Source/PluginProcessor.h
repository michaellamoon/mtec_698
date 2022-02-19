/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "SineWave.h"
#include "ParameterDefines.h"

//==============================================================================
class Week4AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Week4AudioProcessor();
    ~Week4AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getStateInformation (juce::MemoryBlock& destData) override;       //DAW CALL PLUGIN STATE
    void setStateInformation (const void* data, int sizeInBytes) override; //DAW SETS CURRENT STATE
    juce::AudioProcessorValueTreeState& getValueTreeState();               //RETURN VALUE TREE STATE TO DAW

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
    SineWave mSineWavePlug;
    SineWave fSineWavePlug;
    
    SineWave m2SineWavePlug;
    SineWave f2SineWavePlug;
    
    /* this will be our "parameter tree" */
    std::unique_ptr<juce::AudioProcessorValueTreeState> mParameterState;
    /*guarantees thread safe read and write access*/
    std::array<std::atomic<float>*, TotalNumberParameters> mParameterValues;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week4AudioProcessor)
};
