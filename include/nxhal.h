/******************************************************************************* 
 
  IEEE-ISTO 5001(tm) - 1999, The Nexus 5001 Forum(tm) Standard for a Global  
    Embedded Processor Debug Interface 
  ---------------------------------------------------------------------------- 
 
  This file is a part of the IEEE-ISTO 5001(tm) - 1999 API V1.0. 
   
  File: 
    nxhal.h 
     
  Synopsis: 
    Defines the entry points for the Hardware Abstraction Layer (HAL) 
     
  History: 
    28-Jan-1999 - davee; originated 
    12-May-1999 - tzagotta; edits for release 1.0 of specification 
	02-Dec-1999 - tzagota; edits for initial IEEE-ISTO release 
 
  ---------------------------------------------------------------------------- 
 
  Nexus API Team: 
    Dave Edwards, STMicroelectronics 
    Ray Almond, Noral Micrologics 
    Norm Bartek, Diab-SDS 
    Stewart Christie, CAD-UL Inc. 
    Gerhard Martin, Infineon Technologies 
    Phil Meek, Noral Micrologics 
    Jim Pangburn, Diab-SDS 
    Chad Peckham, Motorola 
    Roger Theyyunni, Applied Dynamics International 
    Kerry Woodbury, Diab-SDS 
    Patty Walton, Applied Microsystems 
    Tom Zagotta (Chairperson), Accurate Technologies Inc. 
 
  ---------------------------------------------------------------------------- 
 
  Copyright (c) 1999, IEEE Industry Standards and Technology Organization. 
  All rights reserved.   
 
  IEEE-ISTO 5001 and Nexus 5001 Forum are trademarks of the IEEE-ISTO. 
 
*******************************************************************************/ 
 
#ifndef _nxhal_h_ 
#define _nxhal_h_ 
 
/* Include the vendor's own definition of the NEXUS data types 
*/ 
#include "nxvtypes.h" 
 
/* Include the standard NEXUS API data types  
*/ 
#include "nxtypes.h" 
 
/* +-----------------------------------------+ 
   | nxhal_Open() - Open a Target Connection | 
   +-----------------------------------------+ 
 
   Preconditions: 
     - tSpec specifies the target setup (byte ordering and ports) 
     - errorCallback is a callback function which can be invoked when errors occur 
 
   Postconditions: 
     if succeeds: 
       - returns an initialized handle 
       - sets the status to NX_ERROR_NONE 
     otherwise 
       - status is set to NX_ERROR_NO_CAPABILITY 
*/ 
 
nxt_Handle *nxhal_Open (const nxt_TargetSpec *tSpec,  
                        void (*errorCallback)(const char *), 
                        nxt_Status *status); 
 
 
/* +-------------------------------------------+ 
   | nxhal_Close() - Close a Target Connection | 
   +-------------------------------------------+ 
 
   Preconditions: 
     - handle from a successful invocation of nxhal_Open() 
 
   Postconditions: 
     - the connection is closes and the handle is deallocated 
*/ 
 
void nxhal_Close (nxt_Handle *handle); 
 
 
/* +-----------------------------------------------------------------------+ 
   | nxhal_WriteNRR() - Write to a Target's NEXUS IEEE1149.1 JTAG Register | 
   +-----------------------------------------------------------------------+ 
 
   Preconditions: 
     - handle from a successful invocation of nxhal_Open() 
     - index ranges from 0 through 127 and identifies which NRR to write 
     - numBitsInNRR specifies the number of bits in the NRR specified by index 
     - data contains a pointer to (numBitsInNRR+7)/8 bytes of data to write to the NRR 
 
   Postconditions: 
     if the write succeeds, the function will return NX_ERROR_NONE; otherwise, 
       it will return NX_ERROR_FAILED 
*/ 
 
nxt_Status nxhal_WriteNRR (nxt_Handle *handle, 
                           const int index, const int numBitsInNJR, 
                           const void *data); 
 
 
/* +------------------------------------------------------------------+ 
   | nxhal_ReadNRR() - Read a Target's NEXUS IEEE1149.1 JTAG Register | 
   +------------------------------------------------------------------+ 
 
   Preconditions: 
     - handle from a successful invocation of nxhal_Open() 
     - index ranges from 0 through 127 and is used to identify which NRR to read 
     - numBitsInNRR specifies the number of bits in the NRR specified by index 
     - data contains a pointer to where (numBitsInNRR+7)/8 bytes of data from the NRR 
         will be written 
 
   Postconditions: 
     if the read succeeds, the specified number of bits of data will be written to where 
       data points to, and the function will return NX_ERROR_NONE 
     otherwise, the function will retun NX_ERROR_FAILED 
*/ 
 
nxt_Status nxhal_ReadNRR (nxt_Handle *handle, 
                          const int index, const int numBitsInNJR, 
                          void *data); 
 
 
/* +--------------------------------------------------+ 
   | nxhal_GetEvent() - read an event from the target | 
   +--------------------------------------------------+ 
 
   Preconditions: 
     - handle from a successful invocation of nxhal_Open() 
     - event points to where the event will be stored 
     - maxbytes is the size of the buffer for the event 
     - if block != 0, will block until something is read, else will poll 
 
   Postconditions: 
     if an event is read 
       stores the event to where the event pointer references 
       returns NX_ERROR_NONE 
     otherwise 
       invoke the errorCallback installed with nxhal_Open (if there is one) 
       returns NX_ERROR_FAILED 
*/ 
 
nxt_Status nxhal_GetEvent (nxt_Handle *handle,  
                           nxt_ReceivedEvent* event, 
                           int maxBytes, 
                           const int block);                   
 
#endif