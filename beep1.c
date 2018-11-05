//Beep module
// Made by: James Shields (jds96 - 94504086) and Yihong Liu (yli227 - 49118489)
//Date: 12/10/16

//This function allows a beep to be created on a piezo speaker element using a quick switch in voltage.
#include "system.h"
#include "pio.h"
#include "beep1.h"
#include "delay.h"

//Connect speaker to pins 6 and 8 of the header port.
#define PIEZO1_PIO PIO_DEFINE (PORT_D, 4)
#define PIEZO2_PIO PIO_DEFINE (PORT_D, 6)

//Main sound producing function. When this is run once, the voltage polarity on the pins is switched. Designed to be called quickly, i.e. a While loop.
void noise_maker(void)
{
    pio_config_set(PIEZO1_PIO, PIO_OUTPUT_LOW);
    pio_config_set(PIEZO2_PIO, PIO_OUTPUT_HIGH);
    DELAY_US(300);              // A larger delay provides time for speaker diaphram to reach a larger displacement, giving volume control.
    pio_config_set(PIEZO1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(PIEZO2_PIO, PIO_OUTPUT_LOW);
}
