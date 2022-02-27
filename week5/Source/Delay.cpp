//
//  Delay.cpp
//  week5 - Standalone Plugin
//
//  Created by michaella on 2/27/22.
//

#include "Delay.h"


/* CONSTRUCTOR- (create class)allocate memory/setup various internal data */
Delay::Delay(){}

/* DECONSTRUCTOR- (delete class)free memory/delete not using in the application */
Delay::~Delay(){}

/* INITALIZE (in prepare to play) get SineWave ready for playback */
void Delay::initialize(float inSampleRate)
{
    mSampleRate = inSampleRate;
    mCircularBuffer.setSize(1, 5 * inSampleRate);
    mSmoothedGain.reset(inSampleRate, 0.01);
}

/* */
void Delay::setParameters(float inTimeSeconds, float inFeedbackAmount, float inMix)
{
    mFeedbackAmount = inFeedbackAmount;
    mTimeInSeconds = inTimeSeconds;
    mMix = inMix;
}

/* */
void Delay::processBlock(float* inBuffer, int inNumSamples)
{
    for (int i = 0; i < inNumSamples; i++) {
        processSample(inBuffer[i]);
    }
}

/* */
void Delay::processSample(float& inSample)
{
    mCircularBuffer.setSample(0, mWriteHead, std::tanh(inSample + (mFeedbackSample * mFeedbackAmount)));
    
    mWriteHead++;
    
    if (mWriteHead >= mCircularBuffer.getNumSamples()) {
        mWriteHead = 0;
    }
    
    float time_in_sample = mTimeInSeconds * mSampleRate;
    float read_head = mWriteHead - time_in_sample;
    
    if (read_head < 0) {
        read_head += mCircularBuffer.getNumSamples();
    }
    
    float output_sample = mCircularBuffer.getSample(0, read_head) * mSmoothedGain.getNextValue();
    
    mFeedbackSample = output_sample;
    
    inSample = (output_sample * mMix) + (inSample * (1.f-mMix));
}

void Delay::setGain(float inGain)
{
    mSmoothedGain.setTargetValue(inGain);
}

float Delay::getGain()
{
    return mSmoothedGain.getTargetValue();
}
