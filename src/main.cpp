#include <Arduino.h>

enum class LedPin : uint8_t {
  Warning = 0,
  Error = 1, 
  Ok = 2
};

struct Blinker {
  uint32_t last_toggle_time = 0;
  bool led_state = false;
  int blink_counter = 0;
  int target_blinks = 0;
  uint32_t interval_ms = 0;
  LedPin pin;

  void start(LedPin led_pin, int n_blinks, uint32_t duration_ms);
  void update();
};



//Declarations
void setPinMode(LedPin pin, u_int8_t mode);
void writePin(LedPin pin, u_int8_t value);
Blinker errorBlinker;

void setup()
{
  setPinMode(LedPin::Error, OUTPUT);
  setPinMode(LedPin::Warning, OUTPUT);
  setPinMode(LedPin::Ok, OUTPUT);
  
  writePin(LedPin::Error, LOW);
  writePin(LedPin::Warning, LOW);
  writePin(LedPin::Ok, LOW);

  errorBlinker.start(LedPin::Error, 10, 200);
}

void loop()
{
  errorBlinker.update();
}


//functions

void Blinker::start(LedPin led_pin, int n_blinks, uint32_t duration_ms) {
  if (blink_counter == 0) {
    pin = led_pin;
    target_blinks = n_blinks * 2;
    blink_counter = 0;
    interval_ms = duration_ms;
    last_toggle_time = millis();
  }
}

void Blinker::update() {
  if (target_blinks == 0) return;

  uint32_t current_time = millis();

  if (current_time - last_toggle_time >= interval_ms) {
    led_state = !led_state;
    writePin(pin, led_state ? HIGH : LOW);

    last_toggle_time = current_time;
    blink_counter++;

    if (blink_counter >= target_blinks) {
      target_blinks = 0;
      blink_counter = 0;
      writePin(pin, LOW);
    }
  }
}

//Helpers and wrappers
void setPinMode(LedPin pin, u_int8_t mode){
  pinMode(static_cast<uint8_t>(pin), mode);
}

void writePin(LedPin pin, u_int8_t value){
    digitalWrite(static_cast<uint8_t>(pin), value);
}
