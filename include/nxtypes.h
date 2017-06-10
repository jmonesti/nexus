/******************************************************************************* 
 
  IEEE-ISTO 5001(tm) - 1999, The Nexus 5001 Forum(tm) Standard for a Global  
    Embedded Processor Debug Interface 
  ---------------------------------------------------------------------------- 
 
  This file is a part of the IEEE-ISTO 5001(tm) - 1999 API V1.0. 
   
  File: 
    nxtypes.h 
     
  Synopsis: 
    Definitions of standard NEXUS API data types 
     
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
 
#ifndef _nxtypes_h_ 
#define _nxtypes_h_ 
 
/* Include the vendor's own definition of some NEXUS data types 
*/ 
#include "nxvtypes.h" 
 
 
/* +-------------+ 
   | error types | 
   +-------------+ */ 
 
/* nxt_Status: standard status codes used by all NEXUS API fns 
*/ 
typedef enum { 
  NX_ERROR_NONE          = 0, /* success */ 
  NX_ERROR_FAILED        = 1, /* generic failure */ 
  NX_ERROR_NO_CAPABILITY = 2, /* operation not within capabilities */ 
  NX_ERROR_NO_SPACE      = 3  /* insufficient buffer space */                   
} nxt_Status; 
 
 
/* +----------------------------------+ 
   | low level message handling types | 
   +----------------------------------+ */ 
 
/* nxt_Packet: NEXUS packet = a sequence of bits 
*/ 
typedef struct { 
  int numBitsInPacket; 
  void *data;   /* stream of (numBitsInPacket+7)/8 bytes */ 
} nxt_Packet; 
 
 
/* nxt_Message: NEXUS message = a sequence of packets 
*/ 
typedef struct { 
  int numPackets; 
  nxt_Packet *packets; 
} nxt_Message; 
 
 
/* +--------------------------+ 
   | session management types | 
   +--------------------------+ */ 
 
/* nxt_Endian: defines host, emulator, and target endian  
*/ 
typedef enum { 
  NX_ENDIAN_UNKNOWN,  /* used for initial assignment */ 
  NX_ENDIAN_BIG, 
  NX_ENDIAN_LITTLE, 
  NX_ENDIAN_OTHER 
} nxt_Endian; 
 
 
/* nxt_PortType: specifies either JTAG or AUX 
*/ 
typedef enum { 
  NX_PORT_TYPE_UNAVAILABLE,    /* a non-existant port */ 
  NX_PORT_TYPE_JTAG,            
  NX_PORT_TYPE_AUX, 
  NX_PORT_TYPE_OTHER           /* reserved for future use */ 
} nxt_PortType; 
 
 
/* nxt_TargetSpec: when connecting, defines the target's specification 
*/ 
typedef struct { 
  nxt_PortType accessPort;      /* port for access/ctrl */ 
  nxt_PortType unsolicatedPort; /* port for unsolicated messages */ 
  nxt_Endian targetEndian; 
  nxvt_VendorDefinedTargetSpec vendorTargetSpec; 
                                /* see header files for vendor extensions */ 
} nxt_TargetSpec; 
 
 
/* version string for v1.0 of API  
*/ 
#define NX_VERSION_STRING_10 "nxAPIv1.0" 
 
 
/* NX_EVENTID_INVALID: Event ID that is not available */  
#define NX_EVENTID_INVALID (0) 
 
/* nxt_Capability: defines what the target is capable of 
*/ 
typedef struct { 
  char *apiVersionString;    /* NUL character terminated version string */ 
  char *halInfo;             /* NUL character terminated, emulator HAL specific info string */ 
  nxt_Endian targetEndian;   /* target byte order */ 
  nxt_Endian emuEndian;      /* emulator byte order */ 
  int deviceId;              /* as per DID message (see Appendix B) */ 
  int maxMemMap;             /* max number of memory map structs for read/write operations */ 
  int maxMemAccessPriority;  /* max number of access priority structs for read/write operations */ 
  int maxAccessSize;         /* maximum allowable memory access size in bits */ 
 
  /* event ids for event capabilities, either NX_EVENTID_INVALID or n..m */ 
  int btmEventId; 
  int dtmMinEventId; 
  int dtmMaxEventId; 
  int otmEventId; 
  int substitutionEventId; 
  int watchMinEventId; 
  int watchMaxEventId; 
  int breakMinEventId; 
  int breakMaxEventId; 
} nxt_Capability; 
  
 
/* nxt_Handle: used to reference a connected target 
*/ 
typedef struct { 
  nxt_Capability cap;      /* capabilities */ 
  nxt_TargetSpec targetSpec;  
  void *nxTALPrivatePtr;   /* private data as needed for the TAL */ 
  void *nxHALPrivatePtr;   /* private data as needed for the HAL */ 
} nxt_Handle; 
 
 
/* nxt_CtrlTag: defines the type of a control event 
*/ 
typedef enum { 
  NX_CTRL_SET_CLIENT             = 0x01, 
  NX_CTRL_OVERRUN_MODE           = 0x02, 
  NX_CTRL_SUBSTITUTION_MODE      = 0x03, 
  NX_CTRL_RESETORHALT            = 0x04, 
  NX_CTRL_EVENTIN                = 0x05, 
  NX_CTRL_CLIENTBREAK            = 0x06, 
  NX_CTRL_RESTART_FROM_BREAKSTEP = 0x50 
 
  /* values from 0x100 upwards are for vendor extensions */ 
 
} nxt_CtrlTag; 
 
 
/* nxt_CtrlData: used to apply control operations 
*/ 
typedef struct { 
  nxt_CtrlTag cTag; 
  union { 
    struct { 
      int clientId; 
    } setClient;             /* if cTag == NX_CTRL_SET_CLIENT */ 
    struct { 
      int delay;             /* == 0 to disable */ 
    } overrunMode;           /* if cTag == NX_CTRL_OVERRUN_MODE */ 
    struct { 
      int enable;            /* if == 0 disable substituion else enable it */ 
      int forInstructions;   /* valid if enable != 0 */ 
      int forData;           /* valid if enable != 0 */ 
    } substitutionMode;      /* if cTag == NX_CTRL_SUBSTITUTION_MODE */ 
    struct { 
      int performResetSequence; 
      int haltState; 
    } resetOrHalt;           /* if cTag == NX_CTRL_RESETORHALT */ 
    struct { 
      nxvt_Registers regs; 
    } restartFromBreakpoint; /* if cTag == NX_CTRL_RESTART_FROM_BREAKSTEP */ 
    struct { 
      int eventIn;           /* if cTag == NX_CTRL_EVENTIN */ 
    } eventInMode; 
    struct { 
      int clientBreakpoint;  /* if cTag == NX_CTRL_CLIENTBREAK */ 
    } clientBreakpointMode; 
  } u; 
  nxvt_VendorDefinedCtrlData vendorDefinedCtrlData; 
} nxt_CtrlData; 
 
 
/* +------------------------+ 
   | event management types | 
   +------------------------+ */ 
 
/* nxt_EventType: defines the type of an event 
*/ 
typedef enum { 
  NX_ETYPE_STEP          = 0x01,  /* single step */ 
  NX_ETYPE_BREAKPOINT    = 0x10,  /* breakpoint */ 
  NX_ETYPE_WATCHPOINT    = 0x20,  /* watchpoint */ 
  NX_ETYPE_BTM           = 0x50,  /* branch trace messaging */ 
  NX_ETYPE_DTM           = 0x51,  /* data trace messaging */ 
  NX_ETYPE_OTM           = 0x52,  /* ownership trace messaging */ 
  NX_ETYPE_SUBSTITUTION  = 0x70   /* memory substitution */ 
  /* values from 0x100 upwards are for vendor extension */ 
} nxt_EventType; 
 
 
/* nxt_RWMode: whether accesses trigger for read, write or both 
*/ 
typedef enum { 
  NX_RWMODE_READ, 
  NX_RWMODE_WRITE, 
  NX_RWMODE_READ_OR_WRITE 
} nxt_RWMode; 
 
 
/* nxt_BreakpointOperand:  
    what a breakpoint should match against 
*/ 
typedef enum { 
  NX_BREAKPOINT_DATAADDR, 
  NX_BREAKPOINT_DATAVALUE, 
  NX_BREAKPOINT_DATAADDR_AND_DATAVALUE, 
  NX_BREAKPOINT_INSTRADDR 
} nxt_BreakpointOperand; 
 
 
/* nxt_WatchpointOperand:  
    what a watchpoint should match against 
*/ 
typedef enum { 
  NX_WATCHPOINT_DATAADDR 
  NX_WATCHPOINT_DATAVALUE, 
  NX_WATCHPOINT_DATAADDR_AND_DATAVALUE, 
  NX_WATCHPOINT_INSTRADDR 
} nxt_WatchpointOperand; 
 
 
/* nxt_EventOutputMode:                            ____ 
     used when setting the mode for the Event Out (EVTO) pin 
*/ 
typedef enum { 
  NX_EVTO_NOCHANGE,  /* occurance doesn't change Event Output pin */ 
  NX_EVTO_TRIGGERED  /* occurance asserts Event Output */ 
} nxt_EventOutputMode; 
 
/* nxt_SetEvent:  
     used when setting an event 
*/ 
typedef struct { 
  nxt_EventType eType; 
  int eid; 
  union { 
    struct { 
      nxt_RWMode rwMode;        /* trigger on read, write, or both */ 
      nxvt_Address addr; 
      nxt_BreakpointOperand op; /* match I/D address, data, or both */ 
      nxvt_Word data; 
      nxvt_Word mask; 
      nxt_EventOutputMode eoMode; 
    } breakpoint; 
    struct { 
      nxt_RWMode rwMode;        /* trigger on read, write, or both */ 
      nxvt_Address addr; 
      nxt_WatchpointOperand op; /* match I/D address, data, or both */ 
      nxvt_Word data; 
      nxvt_Word mask; 
      nxt_EventOutputMode eoMode; 
    } watchpoint; 
    struct { 
      int startTriggerId;       /* disabled == 0, else = event id */ 
      int endTriggerId;         /* disabled == 0, else = event id */ 
    } btm; 
    struct { 
      nxt_RWMode rwMode; 
      int startTriggerId;       /* disabled == 0, else = event id */ 
      int endTriggerId;         /* disabled == 0, else = event id */ 
      nxvt_Address startAddr;   /* (addr >= startAddr) && (addr &lt; endAddr) */ 
      nxvt_Address endAddr; 
    } dtm; 
    struct { 
      int startTriggerId;      /* trigger disabled == 0, else = event id */ 
    } substitution; 
    nxvt_VendorDefinedBasicSetEvent vendorDefinedBasic; 
  } u; 
  nxvt_VendorDefinedExtensionSetEvent vendorDefinedExtension; 
} nxt_SetEvent; 
 
 
/* nxt_ReadEvent: defines what can be read from the target 
*/  
typedef enum { 
  NX_READ_EVENT_MESSAGE    = 0x1, 
  NX_READ_EVENT_BREAKSTEP  = 0x2, 
  NX_READ_EVENT_INPUTPIN   = 0x3 
} nxt_ReadEvent; 
 
 
/* nxt_ReceivedEvent: an event read from the target  
    - its either empty, a breakpoint, a message or a pin level 
*/ 
typedef struct { 
  nxt_ReadEvent rTag; 
  union { 
    nxt_Message message;      /* valid if rTag == NX_READ_EVENT_MESSAGE */ 
    nxvt_Registers regs;      /* valid if rTag == NX_READ_EVENT_BREAKSTEP */ 
    struct { 
      int level; 
    } inputPin;               /* valid if rTag == NX_READ_EVENT_INPUTPIN */ 
  } u; 
} nxt_ReceivedEvent; 
 
 
#endif