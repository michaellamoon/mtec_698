//
//  SineWave.cpp
//  week3
//
//  Created by michaella on 2/13/22.
//

#include "SineWave.h"

//CONSTRUCTOR
SineWave::SineWave() {}
//DECONSTRUCTOR
SineWave::~SineWave() {}

//INITALIZE
void SineWave::initialize(float inFrequencyHz, float inSampleRate) {
    
    // Set frequency (HZ)
    mFreqHz = inFrequencyHz;
    
    // Set samplerate
    mSampleRate = inSampleRate;
    mSmoothedGain.reset(inSampleRate, 0.01);
}

//GETNEXTSAMPLE
float SineWave::getNextSample() {
    
    // calculate our sine function output
    //-- using a sin call scaled to repeat between 0 - 1 on the input
    float output = std::sin(juce::MathConstants<float>::twoPi * mPhase);
    
    // move our phase forward in the sign table by a single step
    //-- determined by our desired samplerate & playback hz
    mPhase += mFreqHz / mSampleRate;
    
    // if we go passed 1 -- lets loop back around the sine wave
    if (mPhase > 1.f) {
        mPhase -= 1.f;
    }
    
    // return the output to the caller
    return output * mSmoothedGain.getNextValue();
}

float SineWave::getNextSampleWithFM(float inFMOperator)
{
    float output = std::sin(juce::MathConstants<float>::twoPi * (mPhase + inFMOperator));
    
    // move our phase forward in the sign table by a single step determined by our desired samplerate & playback hz
    mPhase += mFreqHz / mSampleRate;
    
    // if we go passed 1 -- lets loop back around the sine wave
    if (mPhase > 1.f) {
        mPhase -= 1.f;
    }
    
    // return the output to the caller
    return output * mSmoothedGain.getNextValue();
}

/* */
void SineWave::setGain(float inGain)
{
    mSmoothedGain.setTargetValue(inGain);
}

float SineWave::getGain()
{
    return mSmoothedGain.getTargetValue();
}
