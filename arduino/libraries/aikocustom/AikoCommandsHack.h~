/*
 * To Do
 * ~~~~~
 * - Convert existing temporary hack to something more like AikoEvents !
 */

void (*commandHandlers[])() = {
  baudRateCommand,
  nodeCommand,
  relayCommand,
#ifdef PIN_RELAY_2
  relay2Command,
#endif
  resetClockCommand,
  resetLcdCommand,
  transmitRateCommand
};

char* commands[] = {
  "baud=",
  "node=",
  "relay",
#ifdef PIN_RELAY_2
  "relay2",
#endif
  "transmit="
};

char* eepromKeyword[] = {
  0,  // "bd",
  "nd",
  0,
  0,
  0,
  0   // "tr"
};

byte parameterCount[] = {  // ToDo: Change to incorporate parameter type ?
  1,  // baud rate       (integer)
  1,  // node name       (string)
  1,  // relay state     (boolean)
#ifdef PIN_RELAY_2
  1,  // relay2 state    (boolean)
#endif
  1   // transmit rate   (integer seconds)
};

byte commandCount = sizeof(commands) / sizeof(*commands);
