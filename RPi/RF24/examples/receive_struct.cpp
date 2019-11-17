/* Send Struct over the radio nRF24L01 to be used in the STAGIOP-TR project 
 *
 * author: carlos lopes
 *
 * */

#include <cstdlib>
#include <RF24/RF24.h>

using namespace std;

// CE Pin, CSN Pin, SPI Speed

// Setup for GPIO 22 CE and CE1 CSN with SPI Speed @ 1Mhz
RF24 radio(RPI_V2_GPIO_P1_22, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_1MHZ);

// Radio pipe addresses for the 2 nodes to communicate.
const uint8_t pipes[][6] = {"1Node","2Node"};


int main(int argc, char** argv){

	unsigned long got_time = 0;

	// Print preamble:
	printf("RF24/examples/send_struct/\n");

	// Setup and configure rf radio
	radio.begin();
	// optionally, increase the delay between retries & # of retries
	radio.setRetries(15,15);
	// Dump the configuration of the rf unit for debugging
	radio.printDetails();
	// Open radio pipe for writing
	radio.openWritingPipe(pipes[1]);
	// Open radio pipe for reading
	radio.openReadingPipe(1,pipes[0]);
	// First, start listening so we can receive data.
	radio.startListening();
	 
	while (1) 
	{
		// Take the time, and receive it.
		//printf("Now receiving...\n");
	
		// if there is data ready
		//printf("Check available...\n");

		if ( radio.available() )
		{
			// Dump the payloads until we've gotten everything

			// Fetch the payload, and see if this was the last one.
			radio.read( &got_time, sizeof(unsigned long) );

			printf("got_time: %ul", got_time);
		}
	}

}

