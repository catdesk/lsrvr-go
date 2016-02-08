#ifndef AikoDevices_h
#define AikoDevices_h

#include "Arduino.h"

using namespace std;

#define EnableAikoDeviceBlink

#ifdef EnableAikoDeviceTemperatureDS1820
#include "../OneWire/OneWire.h"
#endif

namespace Aiko {
  namespace Device {
#include "aiko_devices/AikoDeviceBlink.h"
  }
}

#endif
