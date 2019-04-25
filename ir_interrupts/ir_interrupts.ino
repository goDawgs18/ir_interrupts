//This will be the interval for how much we increment delay
#define INTERVAL 10

//This is going to specify how our LEDS should behave
uint8_t LED_PATTERN;

// This will let us know which LEDs are lit
uint8_t LED_STATE;

volatile uint8_t delayTime;

boolean incomingSignal;

unsigned long prevMillis = 0;

void myTimer() {
  unsigned long currMillis = millis();
  while ((currMillis - prevMillis) < delayTime) {
    currMillis = millis();
  }
  prevMillis = currMillis;
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
      LED_STATE = 0b000000;
      break;
    default:
      LED_STATE = 0b100000;
  }
}

ISR (PCINT0_vect) {
  incomingSignal = true;
}

void setPattern() {
  //LED_PATTERN = (LED_PATTERN == 3) ? 0 : 3;
  switch (LED_PATTERN) {
    case 0:
      LED_PATTERN = 1;
      break;
    case 1:
      LED_PATTERN = 2;
      break;
    case 2:
      LED_PATTERN = 0;
      break;
  }
  incomingSignal = false;
}

void setup() {
  // put your setup code here, to run once:
  LED_PATTERN = 0;
  LED_STATE = 0;
  //set the digital pins 2-7 to outputs
  DDRD = DDRD  | 0b11111100;

  //making sure that digital pin 8 is an input
  DDRB = DDRB & 0b111110;
  
  delayTime = 100;

  //setting the first bit PCIE0 on to enable PCINT0
  PCICR = PCICR | 0b1;

  //making sure that the Digital pin 8 throws interrupt
  PCMSK0 = PCMSK0 | 0b1;

  incomingSignal = false;
}

void loop() {
  /*
   * put if statment like if need to increment interval
   * or something like that put that here
   * 
   * we will set the stuff for this if statment with the led
   * patten case statement
   */
  if (incomingSignal) {
    setPattern();
  }
  
  switch (LED_PATTERN)
  {
    case 0:
      LED_STATE = 0b000000;
      break;
    case 1:
      LED_STATE = 0b111111;
      break;
    case 2:
      loopMode();
      break;
    default:
      LED_STATE = 0b111111;
      LED_PATTERN = 0;
      break;
  }
  //because 0 and 1 are not being used
  PORTD = LED_STATE << 2;

  myTimer();
}


