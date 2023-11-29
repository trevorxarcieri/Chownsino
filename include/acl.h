/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Digilent

  @File Name
    acl.h

  @Description
        This file groups the declarations of the functions that implement
        the ACL library (defined in acl.c).
        Include the file in the project when this library is needed.
        Use #include "acl.h" in the source files where the functions are needed.

  @Author
  Diligent (Edited by Trevor Arcieri)

 */
/* ************************************************************************** */

#ifndef _ACL_H    /* Guard against multiple inclusion */
#define _ACL_H

// ACL interrupt pin
#define tris_ACL_INT2   TRISGbits.TRISG0
#define lat_ACL_INT2    LATGbits.LATG0


#define ACL_I2C_ADDR        0x1D
#define ACL_OUT_X_MSB       0x01 
#define ACL_CTRL_REG1       0x2A
#define ACL_DEVICE_ID       0x0D 
#define ACL_XYZDATACFG      0x0E 

// function prototypes
void ACL_Init(unsigned long int pb_freq);
void ACL_ReadRawValues(unsigned char *rgRawVals);
void ACL_ReadGValues(float *rgGVals);
unsigned char ACL_SetRange(unsigned char bRange);
float ACL_ConvertRawToValueG(unsigned char *rgRawVals);
unsigned char ACL_SetRegister(unsigned char bAddress, unsigned char bValue);
unsigned char ACL_GetRegister(unsigned char bAddress);
 
//private functions:
void ACL_ConfigurePins();
void I2C_Init(unsigned long pb_freq, unsigned int clockFreq);
unsigned char I2C_Write(unsigned char slaveAddress,
                        unsigned char* dataBuffer,
                        unsigned char bytesNumber,
                        unsigned char stopBit);
unsigned char I2C_Read(unsigned char slaveAddress,
                    unsigned char* dataBuffer,
                    unsigned char bytesNumber);

/* *****************************************************************************
 End of File
 */
