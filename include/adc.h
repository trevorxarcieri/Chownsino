/* ************************************************************************** */
/** 

  @Company
    Digilent

  @File Name
    adc.h

  @Description
        This file groups the declarations of the functions that implement
        the ADC module (defined in adc.c). This module is used by AIC and MIC libraries.
        Include the file in the project when the AIC and MIC libraries are needed.
  
  @Author
    Digilent (Edited by Girma Tewolde and Trevor Arcieri)
 
 */
/* ************************************************************************** */

#ifndef _ADC_H    /* Guard against multiple inclusion */
#define _ADC_H

// Analog input AN2
#define tris_ADC_AN2    TRISBbits.TRISB2
#define ansel_ADC_AN2   ANSELBbits.ANSB2

//Potentiometer functions
void potInit();
unsigned int potReadVal();
void potConfigPins();

//ADC functions
void ADC_Init();
unsigned int ADC_AnalogRead(unsigned char analogPIN);

#endif /* _ADC_H */

/* *****************************************************************************
 End of File
 */
