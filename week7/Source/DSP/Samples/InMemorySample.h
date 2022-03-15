//
//  InMemorySample.h
//  GrainSynth - Shared Code
//
//  Created by Jacob Penn on 7/6/21.
//  Copyright © 2021 Minimal Audio. All rights reserved.
//
#pragma once
#ifndef InMemorySample_h
#define InMemorySample_h

#include "SampleBase.h"

class InMemorySample : public SampleBase
{
public:
    
    /* */
    InMemorySample();
    
    /* */
    ~InMemorySample();
    
    /* */
    void readerInitialized() override;
    
    /* */
    void getSample(juce::int64 inPosition, std::vector<float>& inResults) override;
    
    /* */
    void getSample(juce::int64 inPositionLeft, juce::int64 inPositionRight, std::vector<float>& inResults) override;
    
    /* */
    juce::AudioBuffer<float>* getBuffer();
    
private:
    
    std::unique_ptr<juce::AudioBuffer<float>> mInMemoryBuffer;

};

#endif /* InMemorySample_h */
