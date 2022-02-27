//
//  ParameterManager.h
//  week5
//
//  Created by michaella on 2/27/22.
//

#ifndef ParameterManager_h
#define ParameterManager_h

#include "JuceHeader.h"
#include "ParameterDefines.h"

class ParameterManager {
public:
    
    /* */
    ParameterManager(juce::AudioProcessor* inAudioProcessor);
    
    /* */
    ~ParameterManager();
    
    /* */
    float getCurrentValue(int inParameterID);
    
    /* */
    juce::AudioProcessorValueTreeState* getValueTree();
    
private:
    
    /* this will be our "parameter tree" */
    std::unique_ptr<juce::AudioProcessorValueTreeState> mParameterState;
};

#endif /* ParameterManager_h */
