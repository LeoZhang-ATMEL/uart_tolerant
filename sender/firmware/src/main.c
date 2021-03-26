/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
#define ERR_LEN 13 /* 26 us, 1/4 for 9600 baud */
#define BIT_LEN 104

static void run_test(void)
{
    uint8_t i;
    for (i = 0; i < BIT_LEN; i++) {
        // Start Bit
        UART_TX_REF_Clear();
        UART_TX_SIM_Clear();
        SYSTICK_DelayUs(104);

        
        // bit 0
        UART_TX_REF_Set();
        UART_TX_SIM_Set();
        SYSTICK_DelayUs(104);
        
        // bit 1
        UART_TX_REF_Clear();
        UART_TX_SIM_Clear();
        SYSTICK_DelayUs(104);

        // bit 2
        UART_TX_REF_Set();
        UART_TX_SIM_Set();
        SYSTICK_DelayUs(104);

        // bit 3
        UART_TX_REF_Clear();
        UART_TX_SIM_Clear();
        SYSTICK_DelayUs(104);
        
        // bit 4
        UART_TX_REF_Set();
        UART_TX_SIM_Set();
        SYSTICK_DelayUs(104);
        
        // bit 5
        UART_TX_REF_Clear();
        UART_TX_SIM_Clear();
        SYSTICK_DelayUs(104);
        
        // bit 6
        UART_TX_REF_Set();
        UART_TX_SIM_Set();
        SYSTICK_DelayUs(104);

#if 1
        // bit 7 = 0
        UART_TX_REF_Clear();
        if (i <= ERR_LEN) {
            SYSTICK_DelayUs(i);
            UART_TX_SIM_Clear();
            SYSTICK_DelayUs(BIT_LEN - i);
        } else if (i < (BIT_LEN - ERR_LEN)) {
            UART_TX_SIM_Clear();
            SYSTICK_DelayUs(i - ERR_LEN);
            UART_TX_SIM_Set();
            SYSTICK_DelayUs(ERR_LEN);
            UART_TX_SIM_Clear();
            SYSTICK_DelayUs(BIT_LEN - i);
        } else {
            UART_TX_SIM_Clear();
            SYSTICK_DelayUs(i);
            UART_TX_SIM_Set();
            if (BIT_LEN - i > 0) {
                SYSTICK_DelayUs(BIT_LEN - i);
            }
        }
#else
        UART_TX_REF_Clear();
        UART_TX_SIM_Clear();
        SYSTICK_DelayUs(104);
#endif
        
        UART_TX_REF_Set();
        UART_TX_SIM_Set();
        
        SYSTICK_DelayUs(10000);
    }
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    //SYSTICK_TimerPeriodSet(300 - 1);
    SYSTICK_TimerStart();
    printf("UART Tolerant Test (Sender)\r\n");

    while (1) {
        if (SWITCH0_Get()) {
            continue;
        }
        while(SWITCH0_Get() == 0);
        printf("Start Testing, send 0x55\r\n");
        run_test();
    }

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

