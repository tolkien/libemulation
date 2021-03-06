
/**
 * libemulation
 * HID Joystick
 * (C) 2011 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Implements a joystick component
 */

#include "OEComponent.h"

class HIDJoystick : public OEComponent
{
public:
    HIDJoystick();
    
    bool postMessage(OEComponent *sender, int message, void *data);
    
    void addDevice();
    void removeDevice();
    
    void setAxis(OEInt deviceIndex, OEInt index, float value);
    void setHat(OEInt deviceIndex, OEInt index, OEInt value);
    void setButton(OEInt deviceIndex, OEInt index, bool value);
    
private:
    OEInt joystickNum;
};
