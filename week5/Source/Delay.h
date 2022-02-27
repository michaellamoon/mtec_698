//
//  Delay.h
//  week5
//
//  Created by michaella on 2/27/22.
//

#ifndef Delay_h
#define Delay_h

#include "JuceHeader.h"

class Delay {
    
public:
    
    /* CONSTRUCTOR */
    Delay();
    
    /* DECONSTRUCTOR */
    ~Delay();
    
    /* INITALIZE */
    void initialize(float inSampleRate);
    
    /* */
    void setParameters(float inTimeSeconds, float inFeedbackAmount, float inMix);
    
    /* */
    void processBlock(float* inBuffer, int inNumSamples);
    
    /* */
    void processSample(float& inSample);
    
    void setGain(float inGain);
    float getGain();

    
private:
    
    float mTimeInSeconds = 0;
    float mFeedbackAmount = 0;
    float mMix = 0;
    
    float mWriteHead = 0;
    float mFeedbackSample = 0;
    
    juce::AudioBuffer<float> mCircularBuffer;
    
    float mSampleRate;
    
    juce::LinearSmoothedValue<float> mSmoothedGain;
    
};

#endif /* Delay_h */
