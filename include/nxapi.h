/******************************************************************************* 
 
  IEEE-ISTO 5001(tm) - 1999, The Nexus 5001 Forum(tm) Standard for a Global  
    Embedded Processor Debug Interface 
  ---------------------------------------------------------------------------- 
 
  This file is a part of the IEEE-ISTO 5001(tm) - 1999 API V1.0. 
   
  File: 
    nxapi.h 
     
  Synopsis: 
    Definitions of the NEXUS API entry points 
     
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
 
#ifndef _nxapi_h_ 
#define _nxapi_h_ 
 
/* Include the standard NEXUS API data types  
*/ 
#include "nxtypes.h" 
 
/* +--------------------------------------+ 
   | nx_Open() - Open a Target Connection | 
   +--------------------------------------+ 
 
   Preconditions:  
     - tSpec specifies the target setup (byte ordering and port type) 
     - errorCallback is a callback function which may be invoked 
         when errors occur 
 
   Postconditions: 
     if succeeds, a handle is returned and status is set to NX_ERROR_NONE 
     if fails, NULL is returned, and status is set to NX_ERROR_NO_CAPABILITY 
*/ 
 
nxt_Handle *nx_Open (const nxt_TargetSpec *tSpec,  
                     void (*errorCallback)(const char *), 
                     nxt_Status *status); 
 
 
/* +----------------------------------------+ 
   | nx_Close() - Close a Target Connection | 
   +----------------------------------------+ 
 
   Preconditions: 
     - handle is from successful invocation of nx_Open 
 
   Postconditions: 
     - closes the connection and deallocates the handle 
     - returned status indicates whether the close was successful 
*/ 
 
nxt_Status nx_Close (nxt_Handle *handle); 
 
 
/* +-------------------------------------+ 
   | nx_Control() - Control a Connection | 
   --------------------------------------+ 
 
   Preconditions: 
     - handle is from a successful invocation of nx_Open 
     - ctrl specifies the control operation to apply 
 
   Postconditions: 
     if succeeds, returns NX_ERROR_NONE  
     otherwise may invoke the error callback installed with nx_Open, 
       then returns NX_ERROR_FAILED or NX_ERROR_NO_CAPABILITY 
*/ 
 
nxt_Status nx_Control (nxt_Handle *handle, nxt_CtrlData ctrl); 
 
 
/* +----------------------------------------+ 
   | nx_WriteMem() - Write to Target Memory | 
   -----------------------------------------+ 
 
   Preconditions: 
     - handle from a successful invocation of nx_Open 
     - map specifies a memory map (not all targets support this facility) 
     - accessPriority specifies bus priority 
     - addr is the address to write to 
     - numBytes is used to specify how many bytes to write 
     - accessSize is used to specify the byte access size to be used during 
         the data transfer 
     - bytesToWrite is a pointer to the data to write 
 
   Postconditions: 
     if succeeds, returns NX_ERROR_NONE and 
       writes specifies data to the target's memory. 
     else may invoke the error callback installed with nx_Open, 
       then returns NX_ERROR_FAILED  
*/ 
 
nxt_Status nx_WriteMem (nxt_Handle *handle, 
                        const int map, const int accessPriority, 
                        const nxvt_Address addr, const size_t numBytes, 
                        const int accessSize, 
                        const void *bytesToWrite); 
 
 
/* +--------------------------------+ 
   | nx_ReadMem: Read Target Memory | 
   ---------------------------------+ 
 
   Preconditions: 
     - handle from a successful invocation of nx_Open 
     - map specifies a memory map (not all targets support this facility) 
     - accessPriority specifies bus priority 
     - addr is the address to write to 
     - numBytes is used to specify how many bytes to read 
     - bytesRead points to where the data should be stored 
 
   Postconditions: 
     if succeeds, returns NX_ERROR_NONE and bytesRead points to the data  
       read from the target's memory. 
     else may invoke the error callback installed with nx_Open, then  
       returns NX_ERROR_FAILED  
*/ 
nxt_Status nx_ReadMem (nxt_Handle *handle, 
                       const int map, const int accessPriority, 
                       const nxvt_Address addr, const size_t numBytes, 
                       const int accessSize, void* *bytesRead); 
 
 
/* +------------------------------+ 
   | nx_SetEvent() - Set an Event | 
   -------------------------------+ 
 
   Preconditions: 
     - handle is from a successful invocation of nx_Open 
     - setEvent defines the event to set 
 
  Postconditions: 
    if succeeds, returns NX_ERROR_NONE  
    else may invoke the error callback  installed with nx_Open, then returns  
      NX_ERROR_FAILED or NX_ERROR_NO_CAPABILITY 
*/ 
 
nxt_Status nx_SetEvent (nxt_Handle *handle, const nxt_SetEvent *setEvent); 
 
 
/* +---------------------------------------+ 
   | nx_ClearEvent() - Clear a Debug Event | 
   ----------------------------------------+ 
 
   Preconditions: 
     - handle is from a successful invocation of nx_Open 
     - eid if the ID of an event previously set up with nx_SetEvent 
 
   Postconditions: 
     Once this function completes, the specified event will be disabled 
*/ 
 
void nx_ClearEvent (nxt_Handle *handle, const int eid); 
 
 
/* +----------------------------------------------------+ 
   | nx_GetEvent() - Read a Debug Event from the Target | 
   -----------------------------------------------------+ 
 
   Preconditions: 
     - handle is a from a successful invocation of nx_Open 
     - event is a pointer to a block of memory to receive the event 
     - maxBytes is set by the caller to indicate the number of bytes that 
         can be received in the event block of memory 
     - block specifies whether this function will block until an event 
         is available from the target 
 
   Postconditions: 
     if no event available, returns NULL else returns an event 
*/ 
 
nxt_Status nx_GetEvent (nxt_Handle *handle, nxt_ReceivedEvent *event, 
                        int maxBytes, const int block); 
 
#endif /* _nxapi_h_ */
