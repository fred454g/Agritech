#include <Arduino.h>

enum class LedPin : uint8_t {
  Warning = 0,
  Error = 1, 
  Ok = 2
};


//Declarations
void setPinMode(LedPin pin, u_int8_t mode);
void writePin(LedPin pin, u_int8_t value);
void blink(LedPin pin, int count, uint32_t duration_ms);


void setup()
{
  setPinMode(LedPin::Error, OUTPUT);
  setPinMode(LedPin::Warning, OUTPUT);
  setPinMode(LedPin::Ok, OUTPUT);

  //Start med alt slukket
  writePin(LedPin::Error, LOW);
  writePin(LedPin::Warning, LOW);
  writePin(LedPin::Ok, LOW);

}

void loop()
{
  blink(LedPin::Error, 10, 200);
}


//functions

void blink(LedPin pin, int count, uint32_t duration_ms){
  for (int i = 0; i < count; i++){
    writePin(pin, HIGH);
    delay(duration_ms); //ms
    writePin(pin, LOW);
    delay(duration_ms); //ms
  }
}

//Helpers and wrappers
void setPinMode(LedPin pin, u_int8_t mode){
  pinMode(static_cast<uint8_t>(pin), mode);
}

void writePin(LedPin pin, u_int8_t value){
    digitalWrite(static_cast<uint8_t>(pin), value);
}