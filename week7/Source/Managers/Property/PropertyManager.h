//
//  PropertyManager.hpp
//  Course Plugin - Shared Code
//
//  Created by michaella on 3/13/22.
//

#ifndef PropertyManager_h
#define PropertyManager_h

#include "JuceHeader.h"

class ProcessorInterface;

class PropertyManager {
public:

    /* */
    PropertyManager(ProcessorInterface* inInterface);

    /* */
    ~PropertyManager();
};

#endif /* PresetManager_h */

