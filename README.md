# ir_interrupts

## Notes

### 4/24
* ATmeg328 datasheet url: https://www.sparkfun.com/datasheets/Components/SMD/ATMega328.pdf
* Helpful youtube video: https://www.youtube.com/watch?v=-rvaUgYVNuI
* How I think it will work
	* Set up an ISR that will set a flag for an incoming signal
	* That signal will then flag in the loop to figure out what the incoming signal means
	* That will then set up the LED_PATTERN variable so that it will act accordingly
	* IR signal responses:
		* Turn off all of the lights
		* Turn on all of the lights
		* Blink the lights
		* Cycle through all the lights one at a time
		* increment the pattern faster
		* increment the pattern slower
* ISR notes
	* Look at page 73 of the datasheet for the ATmeg