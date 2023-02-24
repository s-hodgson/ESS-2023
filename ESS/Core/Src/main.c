/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ess_helper.h"

int main(void)
{
	/* Initialize system */
	HAL_Init();
	/* Initialize peripherals on board */
	ess_helper_init();
	// Set all the LEDs to on.
	*(uint32_t*)0x40020C14 = 0xF000;
    while(1){
    }
}
