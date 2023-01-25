#include "contiki.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "cc2420.h"
#include "clock.h"


PROCESS(sens_process, "sens process");
AUTOSTART_PROCESSES(&sens_process);

int channel = 11;
int chan_rssi = 0;
int best_chan = 0;
int best_chan_rssi = 0;
int flag = 0;

int counter = 0;

void begin_radio(void) {
	cc2420_init();
	cc2420_on();
	cc2420_set_channel(channel);
}

PROCESS_THREAD(sens_process, ev, data){

	//static struct etimer timer;
	clock_init();

	PROCESS_BEGIN();
	//etimer_set(&timer, CLOCK_SECOND * 5);

	begin_radio();

	printf("Hello World!\n");

	while (counter < 2) {
		cc2420_set_channel(channel);
		clock_wait(15); //Wait ticks
		chan_rssi = cc2420_rssi(); // Get RSSI
		printf("RSSI at channel %d: %d\n", channel, chan_rssi); // Print RSSI

		if (flag == 0) { //If first time running set best chan to the first RSSI/channel
			best_chan_rssi = chan_rssi;
			best_chan = channel;
			flag = 1;
		}
		if (chan_rssi > best_chan_rssi) { //Set best channel/RSSI
			best_chan_rssi = chan_rssi;
			best_chan = channel;
		}
		//PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
		//etimer_reset(&timer);
		
		channel = channel + 1; //Change channel
		if (channel == 27) {
			channel = 11;
			counter = counter + 1;
		}
		
	}
	printf("Best channel %d with RSSI of %d\n", best_chan, best_chan_rssi);
	PROCESS_END();
}
