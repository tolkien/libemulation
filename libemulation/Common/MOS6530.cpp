
/**
 * libemulation
 * MOS6530
 * (C) 2009-2010 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Implements a MOS 6530 (ROM, RAM, I/O, Timer)
 */

#include "MOS6530.h"

#include "Bus.h"
#include "AddressDecoder.h"

MOS6530::MOS6530()
{
	bus = NULL;
	
	portA = NULL;
	
	portB = NULL;
	busB = NULL;
}

bool MOS6530::setProperty(const string &name, const string &value)
{
	if (name == "directionA")
		directionA = getInt(value);
	else if (name == "dataA")
		dataA = getInt(value);
	else if (name == "directionB")
		directionB = getInt(value);
	else if (name == "dataB")
		dataB = getInt(value);
	else
		return false;
	
	return true;
}

bool MOS6530::getProperty(const string &name, string &value)
{
	if (name == "directionA")
		value = getHex(directionA);
	else if (name == "dataA")
		value = getHex(dataA);
	else if (name == "directionB")
		value = getHex(directionB);
	else if (name == "dataB")
		value = getHex(dataB);
	else
		return false;
	
	return true;
}

bool MOS6530::connect(const string &name, OEComponent *component)
{
	if (name == "bus")
	{
		if (bus)
			bus->removeObserver(this, BUS_RESET_ASSERTED);
		bus = component;
		if (bus)
			bus->addObserver(this, BUS_RESET_ASSERTED);
	}
	else if (name == "portA")
		portA = component;
	else if (name == "portB")
		portB = component;
	else if (name == "busB")
		busB = component;
	else
		return false;
	
	return true;
}

int MOS6530::read(int address)
{
	switch (address & 0xf)
	{
		case 0x0:
		case 0x4:
			dataA &= directionA;
			if (portA)
				dataA |= portA->read(0) & ~directionA;
			return dataA;
		case 0x1:
		case 0x5:
			return directionA;
		case 0x2:
		case 0x6:
			dataB &= directionB;
			if (portB)
				dataB |= portB->read(1) & ~directionB;
			return dataB;
		case 0x3:
		case 0x7:
			return directionB;
		case 0x8:
		case 0x9:
		case 0xa:
		case 0xb:
		case 0xc:
		case 0xd:
		case 0xe:
		case 0xf:
			return 0;
	}
	
	return 0;
}

void MOS6530::write(int address, int value)
{
	switch (address & 0xf)
	{
		case 0x0:
		case 0x4:
			dataA = value;
			if (portA)
				portA->write(0, value);
			break;
		case 0x1:
		case 0x5:
			directionA = value;
			break;
		case 0x2:
		case 0x6:
			dataB = value;
			if (portB)
				portB->write(1, value);
			break;
		case 0x3:
		case 0x7:
			directionB = value;
			break;
		case 0x8:
		case 0x9:
		case 0xa:
		case 0xb:
		case 0xc:
		case 0xd:
		case 0xe:
		case 0xf:
			break;
	}
}