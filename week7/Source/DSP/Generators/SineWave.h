//
//  SineWave.h
//  week3
//
//  Created by michaella on 2/13/22.
//
#pragma once
#ifndef SineWave_h
#define SineWave_h

#include "JuceHeader.h"

/* BASIC SINEWAVE CLASS */

class SineWave {

// Public= available to the outside program
public:
    
    /* CONSTRUCTOR- (create class)allocate memory/setup various internal data */
    SineWave();
    
    /* DECONSTRUCTOR- (delete class)free memory/delete not using in the application */
    ~SineWave();
    
    /* INITALIZE (in prepare to play) get SineWave ready for playback */
    void initialize(float inFrequencyHz, float inSampleRate);
    
    /* getNextSample- call every sample to get next audio sample in buffer output */
    float getNextSample();
    
    /* getNextSample w/ FM */
    float getNextSampleWithFM(float inFMOperator);
    
    /* */
    void setParameters(float inFreq, float inGain);
    
    
// Private= not accessible to the outside world
private:
    
    // These are member variables of the class (internal data)
    float mFreqHz = 442;
    float mSampleRate = 44100;
    float mPhase = 0;
    
    juce::LinearSmoothedValue<float> mSmoothedGain;
    
};

#endif /* SineWave_h */
