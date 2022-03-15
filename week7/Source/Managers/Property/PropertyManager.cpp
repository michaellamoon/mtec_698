//
//  PropertyManager.cpp
//  Course Plugin - Shared Code
//
//  Created by michaella on 3/13/22.
//

#include "PropertyManager.h"

#include "PresetManager.h"
#include "ParameterManager.h"
#include "ProcessorInterface.h"

/* */
PropertyManager::PropertyManager(ProcessorInterface* inInterface)
: mProcessorInterface(inInterface)
{
    juce::StringArray CurrentPresetName = mProcessorInterface->getPresetManager()->getCurrentPresetNames();
    for (int i = 0; i < CurrentPresetName.size(); ++i)
    {
       const juce::String item (CurrentPresetName[i]);
       DBG(item);
        //juce::Logger::outputDebugString (item);
    }

//define DBG(textToWrite)
    //JUCE_BLOCK_WITH_FORCED_SEMICOLON (juce::String tempDbgBuf;tempDbgBuf << textToWrite; juce::Logger::outputDebugString (tempDbgBuf);)
}


