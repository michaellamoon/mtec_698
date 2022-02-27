//
//  ParameterDefines.h
//  week4
//
//  Created by michaella on 2/19/22.
//

#ifndef ParameterDefines_h
#define ParameterDefines_h

#include "JuceHeader.h"

//Param defines
enum {
    SINE_GAIN = 0,
    SINE_FM_AMOUNT,
    SINE_FM_FREQUENCY,
    DELAY_TIME_SECONDS,
    DELAY_FEEDBACK,
    DELAY_MIX,
    TotalNumberParameters
};

static const juce::StringArray PARAMETER_NAMES {
    "Gain Amount",
    "FM Amount",
    "FM Frequency",
    "Delay Time Seconds",
    "Delay Feedback",
    "Delay Mix",
};

static const juce::Array<juce::NormalisableRange<float>> PARAMETER_RANGES {
    // start value, end value, interval, skew/curve
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 1.f),
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 1.f),
    juce::NormalisableRange<float>(1.f, 20000.f, 0.f, .25f),
    // 20 ms to 1 second
    juce::NormalisableRange<float>(.02f, 1.f, 0.f, 1.f),
    juce::NormalisableRange<float>(0.f, .9f, 0.f, 1.f),
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 0.5f),
};

#endif /* ParameterDefines_h */
