/*******************************************************************************
* File Name: main.c
*
* Version: 1.00
*
* Description:
*  This example project shows how to get data from DHT11 sensor and decoding the data
*  The output is displayed using UART.
*
********************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#include <project.h>

#define DELAY_ACQUISITION  0x14
#define DELAY_PROCESSING   0x32

/* Function Prototypes */

void delay_function(void);
void Decode_DHT_Data(void);

CY_ISR_PROTO(Delay_Timer_ISR_Handler);
CY_ISR_PROTO(DHT_Pin_ISR_Handler);

uint8 flag=0;

int CountValues_DataTimer[44]={0};

int Temperature_Values[8], Humidity_Values[8];

uint8 Decoded_Temperature_Data, Decoded_Humidity_Data;

int DiffCountValues[44]={0};

int RisingEdge_Counts=0;

int i,j,k;

int cnt,executed;

uint8 decodeFlag=0;

/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Performs the following tasks:
*  - Start the components.
*  - Develop custom protocol to get output from DHT11. 
*  - Sends the result to HyperTerminal (PC) using UART.
*  
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/

int main()
{
    /* Initialize Data_Timer and Delay_Timer component */
    
    Data_Timer_Start();
    
    Delay_Timer_Start();  
    
    /* Start UART component */
    
    UART_Start();
    
    /* Write Control_Reg_Data_Timer and Control_Reg_Delay_Timer value as 1 to keep Data_Timer and Delay_Timer component in reset */
    
    Control_Reg_Data_Timer_Write(1);
    
    Control_Reg_Delay_Timer_Write(1);
    
    /*The DHT_Pin value has been written as 1 as initial condition*/
    
    DHT_Pin_Write(1);
    
    /* Initialize DHT_Pin_ISR and Delay_Timer_ISR */
    
    DHT_Pin_ISR_StartEx(DHT_Pin_ISR_Handler);
    
    Delay_Timer_ISR_StartEx(Delay_Timer_ISR_Handler);
    
    /* Disable ISR components */
    
    DHT_Pin_ISR_Disable();
    
    Delay_Timer_ISR_Disable();
    
    /* Initialize executed and cnt states as 1 and 0 */
    
    executed=1;
    
    cnt=0;
    
    /* Enable Global Interrupts */
    
    CyGlobalIntEnable; 
    
    for(;;)
    {
        /* The conditional statement executed = 1 and cnt = 0 to start the  */
        
        if(executed==1 && cnt==0)
        {
            executed=0;
            
            RisingEdge_Counts=0;
            
            CyDelayUs(50);

            DHT_Pin_Write(0);
            
            Delay_Timer_WritePeriod(DELAY_ACQUISITION);
            
            /*   Call the delay function to stay the DHT_Pin as low for 20ms   */
            
            delay_function();
        }
        
        /* This conditional statement should be called after Delay_Timer_ISR_Handler is executed */
        
        if(cnt>=2 && executed==0)
        {
            /* Enable the Data_Timer by writing 0 to Control_Reg_Data_Timer */
            
            Control_Reg_Data_Timer_Write(0);
            
            /* Write 1 to DHT_Pin */
            
            DHT_Pin_Write(1);
            
            /* Enable DHT_Pin_ISR to get data from the DHT11 sensor */
            
            DHT_Pin_ISR_Enable();
            
            /* To keep the DHT_Pin as High for 30us, the below function is called */
            
            CyDelayUs(30);
            
            Delay_Timer_WritePeriod(DELAY_PROCESSING);
            
            Control_Reg_Delay_Timer_Write(0);
            
            /* Change the Executed and Count status to decode the DHT11 values */
            
            executed=2;
            cnt=0;
        }
        
        if(decodeFlag==1)
        {
            Control_Reg_Data_Timer_Write(1);
            DHT_Pin_ISR_Disable(); 
            DHT_Pin_Write(1);   
            decodeFlag=0;
            Decode_DHT_Data();
            executed=1;
            cnt=0;
        }
    }
}

/*******************************************************************************
* Function Name: Decode_DHT_Data
********************************************************************************
*
* Summary:
*  Performs the following tasks:
*  - The value stored in CountValues_DataTimer[] array, is used to decode the data of DHT output
*  - The time difference between CountValues_DataTimer[i] and CountValues_DataTimer[i-1] is calculated
*  - If the CountValues_DataTimer[i] is approximately 70 counts, it is data 0, and if CountValues_DataTimer[i] is approximately 120, it is data 1. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/

void Decode_DHT_Data(void)
{
    for(i=1; i< 44; i++)
    {
        DiffCountValues[i]=CountValues_DataTimer[i-1]-CountValues_DataTimer[i];
    } 
    for(j=0; j<8; j++)
    {
        if(DiffCountValues[j+3]>100)
        {
            Humidity_Values[7-j]=1;
        }
        else
        {
            Humidity_Values[7-j]=0;
        }
        if(DiffCountValues[j+19]>100)
        {
            Temperature_Values[7-j]=1;
        }
        else
        {
            Temperature_Values[7-j]=0;
        }
    }
    Decoded_Temperature_Data= (uint8)((Temperature_Values[7]<<7) + (Temperature_Values[6]<<6) + (Temperature_Values[5]<<5) + (Temperature_Values[4]<<4) + (Temperature_Values[3] <<3) + (Temperature_Values[2] <<2) + (Temperature_Values[1]<<1) + Temperature_Values[0]);
    Decoded_Humidity_Data=(uint8)((Humidity_Values[7]<<7) + (Humidity_Values[6]<<6) + (Humidity_Values[5]<<5) + (Humidity_Values[4]<<4) + (Humidity_Values[3] <<3) + (Humidity_Values[2] <<2) + (Humidity_Values[1]<<1) + Humidity_Values[0]);

    UART_UartPutString("\nTemperature Data:  ");
    UART_UartPutChar(Decoded_Temperature_Data);
    
    UART_UartPutString("\nHumidity Data:  ");
    UART_UartPutChar(Decoded_Humidity_Data);
}




/*******************************************************************************
* Function Name: delayfucntion
********************************************************************************
*
* Summary:
*  Performs the following tasks:
*  - Enable Delay_Timer_ISR to detect Delay_Tiemr Terminal Count interrupt
*  - Start the Delay_Timer component.
*  - This function does not use the CPU delay API, CyDelay(), but uses Delay_Timer to generate delay. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/


void delay_function(void)
{
    /*  Change the global variables state    */
    cnt=1;
    executed=0;
   
    /*  Enable Delay_timer_ISR    */
    
    Delay_Timer_ISR_Enable();
    
    /*  Write 0 to Control_Reg_Delay_Timer to starting Delay_Timer component */
    
    Control_Reg_Delay_Timer_Write(0);   
    
}


/******************************************************************************
* Function Name: Delay_Timer_ISR_Handler
*******************************************************************************
*
* Summary:
*  Interrupt Service Routine. Check the Delay_Timer status and clear the interrupt
*  change the Count and Executed status
*
******************************************************************************/

CY_ISR(Delay_Timer_ISR_Handler)
{
    /* Change the Count and Executed values */
    
    if(Delay_Timer_ReadPeriod() == DELAY_ACQUISITION)
    {
        cnt=2;                  // need to change the values
        executed=0;             // need to change the values
    }
    else if(Delay_Timer_ReadPeriod() == DELAY_PROCESSING)
    { 
        decodeFlag=1;
    }
    else
    {    }
    
    /* Write 1 to the Contro_Reg_Delay_Timer to disable the Timer function */
    
    Control_Reg_Delay_Timer_Write(1);
    
    /* Read the status register of Delay_Timer to clear interrupt */
    
    Delay_Timer_ReadStatusRegister();
    
    /* Clear the Delay_Timer_ISR interrupt */
    
    Delay_Timer_ISR_ClearPending();    
    
}

/******************************************************************************
* Function Name: DHT_Pin_ISR_Handler
*******************************************************************************
*
* Summary:
*  Interrupt Service Routine. Check the Delay_Timer status and clear the interrupt
*  change the Count and Executed status
*
******************************************************************************/

CY_ISR(DHT_Pin_ISR_Handler)
{   
    /* Clear the interrupt request of the ISR DHT_Pin_ISR */
    
    DHT_Pin_ISR_ClearPending();   
    
    /* Clear the interrupt request of the pin DHT_Pin */
    
    DHT_Pin_ClearInterrupt();
    
    /* Read the counter values of Data_Timer for processing */
    
    CountValues_DataTimer[RisingEdge_Counts]=Data_Timer_ReadCounter();
    
    RisingEdge_Counts++;  
}