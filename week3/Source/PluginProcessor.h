/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "SineWave.h"

//==============================================================================
class Week3AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Week3AudioProcessor();
    ~Week3AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void setSineVolume(int inSineID, float inInputVolumeAmp);
    float getSineVolume(int inSineID);

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

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    
    //-------INIT------------------------------
    SineWave mSineWave;
    float mSineGain = 0.2;
    
    SineWave m2SineWave;
    float m2SineGain = 0.2;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Week3AudioProcessor)
};
