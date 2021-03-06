
/**
 * libemulation
 * RAM
 * (C) 2010-2011 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Controls random access memory.
 */

#ifndef _RAM_H
#define _RAM_H

#include "OEComponent.h"

#include "ControlBusInterface.h"

// Notes:
// * size is the RAM size. It must be a power of two.
// * To determine the power state, set the controlBus.
// * powerOnPattern is the byte pattern used when power is first applied.
// * image is the RAM image.

class RAM : public OEComponent
{
public:
    RAM();
    
    bool setValue(string name, string value);
    bool getValue(string name, string &value);
    bool setRef(string name, OEComponent *ref);
    bool setData(string name, OEData *data);
    bool getData(string name, OEData **data);
    bool init();
    void update();
    
    bool postMessage(OEComponent *sender, int message, void *data);
    
    void notify(OEComponent *sender, int notification, void *data);
    
    OEChar read(OEAddress address);
    void write(OEAddress address, OEChar value);
    
protected:
    OEAddress size;
    
    OEChar *datap;
    OEAddress mask;
    
private:
    OEData powerOnPattern;
    
    OEComponent *controlBus;
    
    OEData data;
    
    ControlBusPowerState powerState;
    
    void initMemory();
};

#endif
