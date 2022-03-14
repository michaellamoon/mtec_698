//
//  Parameter Manger.hpp
//  week7 - Shared Code
//
//  Created by michaella on 3/13/22.
//

#ifndef Parameter_Manger_hpp
#define Parameter_Manger_hpp

#include "JuceHeader.h"
#include "ParameterDefines.h"

class ProcessorInterface;

class ParameterManager {
public:
    
    /* */
    ParameterManager(ProcessorInterface* inInterface);
    
    /* */
    ~ParameterManager();
    
    /* */
    float getCurrentValue(int inParameterID);
    
    /* */
    juce::AudioProcessorValueTreeState* getValueTree();
    
private:
    
    /* this will be our "parameter tree" */
    std::unique_ptr<juce::AudioProcessorValueTreeState> mParameterState;
    
    ProcessorInterface* mProcessorInterface;
};

#endif /* ParameterManager_h */
