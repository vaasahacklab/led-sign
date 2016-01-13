// Setup stuff
int pinArray[] = {14, 15, 16, 17, 18, 19, 13};
int levelArray[] = {0, 0, 0, 0, 0, 0, 0};

const int MAXPOWER = 999;
const int CHAR_DELAY = 500;

int current_index = 0;
int last_char_index = 0;
unsigned long next_char_timer = millis() + CHAR_DELAY;

void setup(){
  for (current_index = 0; current_index < 7; current_index++) {
    pinMode(pinArray[current_index], OUTPUT);
  }
}

void loop() {
  // Update next character if needed
  if(millis() > next_char_timer) {
    last_char_index++;
    if(last_char_index == 7) {
      last_char_index = 0;
    }

    levelArray[last_char_index] = MAXPOWER;
    next_char_timer = millis() + CHAR_DELAY;
  }

  // Decay character power level
  for (current_index = 0; current_index < 7; current_index++) {
    if(levelArray[current_index] > 5) {
      levelArray[current_index] = levelArray[current_index] - 5;
    }
  }

  // Display current power level with fake PWM
  // https://www.arduino.cc/en/Tutorial/SecretsOfArduinoPWM
  for (current_index = 0; current_index < 7; current_index++) {
    digitalWrite(pinArray[current_index], HIGH);
    delayMicroseconds(levelArray[current_index]);
    digitalWrite(pinArray[current_index], LOW);
    delayMicroseconds(1000 - (levelArray[current_index]));
  }
}
