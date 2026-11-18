#include <stdio.h>
#include "xil_printf.h"
#include "xparameters.h"
#include "sleep.h" 

// AXI GPIO Base Address
#define GPIO_BASE_ADDR 0x41200000 
#define GPIO_PTR ((volatile unsigned int *)GPIO_BASE_ADDR)

int main()
{
    xil_printf("\r\n--- ARM Core Booting Up ---\r\n");
    xil_printf("Starting Fibonacci Sequence on LEDs...\r\n\r\n");

    // Safety measure to ensure pins are configured as Outputs
    GPIO_PTR[1] = 0x0; 

    unsigned int a = 0;
    unsigned int b = 1;
    unsigned int next;
    int i;

    while (1) { // Infinite loop to keep the sequence running
        // Reset Fibonacci sequence
        a = 0;
        b = 1;

        // Display first 15 numbers of the sequence
        for (i = 0; i < 7; i++) {
            xil_printf("Fibonacci [%2d] = %d\r\n", i, a);
            
            // Write the lowest 4 bits of the Fibonacci number to the LEDs
            GPIO_PTR[0] = a & 0xF; 

            // Wait 1 second so you can see the LEDs change
            sleep(1);

            // Calculate next Fibonacci number
            next = a + b;
            a = b;
            b = next;
        }

        // Turn all LEDs off for 2 seconds before restarting the sequence
        GPIO_PTR[0] = 0x0;
        sleep(2);
    }

    return 0;
}