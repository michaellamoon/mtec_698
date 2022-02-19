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
    GAIN_AMOUNT,
    //GAIN_AMOUNT2,
    FM_AMOUNT,
    //FM_AMOUNT2,
    TotalNumberParameters,
    inSineID
};

static const juce::StringArray PARAMETER_NAMES {
    "Gain Amount",
    "FM Amount",
};

static const juce::Array<juce::NormalisableRange<float>> PARAMETER_RANGES {
    //                            (start value, end value, interval, skew/curve)
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 1.f),
    juce::NormalisableRange<float>(0.f, 1.f, 0.f, 1.f),
};

#endif /* ParameterDefines_h */
