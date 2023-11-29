/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Digilent

  @File Name
    adc.h

  @Description
        This file groups the declarations of the functions that implement
        the ADC module (defined in adc.c). This module is used by AIC and MIC libraries.
        Include the file in the project when the AIC and MIC libraries are needed.
  
  @Author
    Digilent (edited by Girma Tewolde)
 
  @Last modification
    10/03/2020 @ 11:44 AM 
 */
/* ************************************************************************** */

#ifndef _ADC_H    /* Guard against multiple inclusion */
#define _ADC_H

// Analog input AN2
#define tris_ADC_AN2    TRISBbits.TRISB2
#define ansel_ADC_AN2   ANSELBbits.ANSB2

//potentiometer functions
void potInit();
unsigned int potReadVal();
void potConfigPins();

//ACD functions
void ADC_Init();
unsigned int ADC_AnalogRead(unsigned char analogPIN);
//#ifdef __cplusplus
//extern "C" {
//#endif



    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************



    /* Provide C++ Compatibility */
//#ifdef __cplusplus
//}
//#endif
#endif /* _ADC_H */

/* *****************************************************************************
 End of File
 */
