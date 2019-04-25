
//This is going to specify how our LEDS should behave
uint8_t LED_PATTERN;

// This will let us know which LEDs are lit
uint8_t LED_STATE;

unsigned long prevMillis = 0;

void setup() {
  // put your setup code here, to run once:
  progState = 0;
  returning = false;
}

void loop() {
  
  
}

void loopMode() {
  switch(LED_STATE) {
    case 0b000000:
      LED_STATE = 0b100000;
      break;
    case 0b100000:
      LED_STATE = 0b010000;
      break;
    case 0b010000:
      LED_STATE = 0b001000;
      break;
    case 0b001000:
      LED_STATE = 0b000100;
      break;
    case 0b000100:
      LED_STATE = 0b000010;
      break;
    case 0b000010:
      LED_STATE = 0b000001;
      break;
    case 0b000001:
      LED_STATE = 0b000000
    default:
      LED_STATE = 0b100000;
  }
}

