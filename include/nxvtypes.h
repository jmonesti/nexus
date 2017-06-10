/******************************************************************************* 
 
  IEEE-ISTO 5001(tm) - 1999, The Nexus 5001 Forum(tm) Standard for a Global  
    Embedded Processor Debug Interface 
  ---------------------------------------------------------------------------- 
 
  This file is a part of the IEEE-ISTO 5001(tm) - 1999 API V1.0. 
   
  File: 
    nxvtypes.h 
     
  Synopsis: 
    Contains sample definitions of vendor defined NEXUS API data types.  This  
    example is for a 64-bit target, compiled on a system which supports 64 bit  
    integers as long long int. 
     
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
 
#ifndef _nxvtypes_h_ 
#define _nxvtypes_h_ 
 
 
/* nxvt_Address: holds a target address 
*/ 
typedef long long int nxvt_Address; 
 
 
/* nxvt_Word: holds a target word (max size of atomic  
    memory access) 
*/ 
typedef long long int nxvt_Word; 
 
 
/* integer register type & number 
*/ 
#define NUM_INT_REGS (32) 
typedef long long int t_IntegerRegister; 
 
/* float registers - type & number 
*/ 
#define NUM_FLOAT_REGS (32) 
typedef float t_FloatRegister; 
 
 
/* nxvt_Registers: an opaque type to contain the target's 
    general purpose register set 
*/ 
typedef struct { 
  t_IntegerRegister intRegs[NUM_INT_REGS]; 
  t_FloatRegister floatRegs[NUM_FLOAT_REGS];  
} nxvt_Registers; 
 
/*################################################################ 
  ### definitions for some extra vendor defined control operations  
  ###   (see nxt_CtrlTag, nxt_CtrlData, and nx_Ioctl) 
  ### this example adds a LED flashing, and trace config features 
  ################################################################*/ 
 
/* NX_CTRL_FLASH_LED: tag value for the LED control operations  
*/ 
#define NX_CTRL_FLASH_LED (0x100) 
 
/* NX_CTRL_CONFIG_TRACEBUF:  
    tag value for the trace buffer control operations  
*/ 
#define NX_CTRL_CONFIG_TRACEBUF (0x101) 
 
 
/* nxvt_VendorDefinedCtrlData:  information for 
     vendor defined control operations (see nx_Ioctl) 
*/ 
typedef struct { 
  union { 
    struct { 
      int howFast; 
    } flashTheLED;          /* if cTag == NX_CTRL_FLASH_LED */ 
    struct { 
      int traceBufferSize; 
    } configureTraceBuffer; /* if cTag == NX_CTRL_CONFIG_TRACEBUF */ 
  } u; 
} nxvt_VendorDefinedCtrlData; 
 
 
/*################################################################ 
  ### definitions for extra features for events 
  ###   (see nxt_SetEvent) 
  ###   - this example adds a "count" facility to events 
  ################################################################*/ 
 
/* nxvt_VendorDefinedExtensionSetEvent:  
    information for adding vendor defined extras to events 
*/ 
typedef struct { 
  int countsBeforeTrigger; 
} nxvt_VendorDefinedExtensionSetEvent; 
 
 
/*################################################################ 
  ### definitions for some extra vendor defined events  
  ###   (see nxt_EventType, nxt_SetEvent and nx_SetEvent) 
  ### this example adds performance counter and watchpoint events 
  ################################################################*/ 
 
/* NX_ETYPE_PERF_COUNT:  
    tag value for the performance counter event 
*/ 
#define NX_ETYPE_PERF_COUNT (0x100) 
 
/* NX_ETYPE_WATCHDOG: tag value for the watchdog event 
*/ 
#define NX_ETYPE_WATCHDOG_COUNT (0x101) 
 
 
/* nxvt_VendorDefinedSetEvent: information for 
    setting vendor defined events 
*/ 
typedef struct { 
  union { 
    struct { 
      int whatToMonitor; 
      int whatToDo; 
    } perfCount;           /* NX_ETYPE_PERF_COUNT */ 
    struct { 
      int stuff; 
    } watchdog;            /* NX_ETYPE_WATCHDOG_COUNT */ 
  } u; 
} nxvt_VendorDefinedBasicSetEvent; 
 
#endif