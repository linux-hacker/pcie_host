#ifndef _PCI_DRIVER_LIB_H_
#define _PCI_DRIVER_LIB_H_

/************************************************************************
*  File: PCI_DRIVER_lib.h
*
*  Library for accessing PCI_DRIVER devices using a Kernel PlugIn driver.
*  The code accesses hardware using WinDriver's WDC library.
*  Code was generated by DriverWizard v10.21.
*
*  Jungo Confidential. Copyright (c) 2017 Jungo Ltd.  http://www.jungo.com
*************************************************************************/

#include "wdc_lib.h"
#include "samples/shared/pci_regs.h"
#include "samples/shared/bits.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************
  General definitions
 *************************************************************/
/* Kernel PlugIn driver name (should be no more than 8 characters) */
#define KP_PCI_DRIVER_DRIVER_NAME "KP_STRAT"

/* Kernel PlugIn messages - used in WDC_CallKerPlug() calls (user mode) / KP_PCI_DRIVER_Call() (kernel mode) */
enum {
    KP_PCI_DRIVER_MSG_VERSION = 1, /* Query the version of the Kernel PlugIn */
};

/* Kernel Plugin messages status */
enum {
    KP_PCI_DRIVER_STATUS_OK = 0x1,
    KP_PCI_DRIVER_STATUS_MSG_NO_IMPL = 0x1000,
};

/* Default vendor and device IDs */
#define PCI_DRIVER_DEFAULT_VENDOR_ID 0x1172 /* Vendor ID */
#define PCI_DRIVER_DEFAULT_DEVICE_ID 0xE003 /* Device ID */


/* Kernel PlugIn version information struct */
typedef struct {
    DWORD dwVer;
    CHAR cVer[100];
} KP_PCI_DRIVER_VERSION;

/* Address space information struct */
#define MAX_TYPE 8
typedef struct {
    DWORD dwAddrSpace;
    CHAR sType[MAX_TYPE];
    CHAR sName[MAX_NAME];
    CHAR sDesc[MAX_DESC];
} PCI_DRIVER_ADDR_SPACE_INFO;

/* Interrupt result information struct */
typedef struct
{
    DWORD dwCounter; /* Number of interrupts received */
    DWORD dwLost;    /* Number of interrupts not yet handled */
    WD_INTERRUPT_WAIT_RESULT waitResult; /* See WD_INTERRUPT_WAIT_RESULT values in windrvr.h */
    DWORD dwEnabledIntType; /* Interrupt type that was actually enabled
                               (MSI/MSI-X/Level Sensitive/Edge-Triggered) */
    DWORD dwLastMessage; /* Message data of the last received MSI/MSI-X
                        (Windows Vista/7); N/A to line-based interrupts) */
} PCI_DRIVER_INT_RESULT;
/* TODO: You can add fields to PCI_DRIVER_INT_RESULT to store any additional
         information that you wish to pass to your diagnostics interrupt
         handler routine (DiagIntHandler() in PCI_DRIVER_diag.c) */

/* PCI_DRIVER diagnostics interrupt handler function type */
typedef void (*PCI_DRIVER_INT_HANDLER)(WDC_DEVICE_HANDLE hDev,
    PCI_DRIVER_INT_RESULT *pIntResult);

/* PCI_DRIVER diagnostics plug-and-play and power management events handler function type */
typedef void (*PCI_DRIVER_EVENT_HANDLER)(WDC_DEVICE_HANDLE hDev,
    DWORD dwAction);

/*************************************************************
  Function prototypes
 *************************************************************/
DWORD PCI_DRIVER_LibInit(void);
DWORD PCI_DRIVER_LibUninit(void);

#if !defined(__KERNEL__)
WDC_DEVICE_HANDLE PCI_DRIVER_DeviceOpen(const WD_PCI_CARD_INFO *pDeviceInfo);
BOOL PCI_DRIVER_DeviceClose(WDC_DEVICE_HANDLE hDev);

static BOOL IsItemExists(PWDC_DEVICE pDev, ITEM_TYPE item);
DWORD PCI_DRIVER_IntEnable(WDC_DEVICE_HANDLE hDev, PCI_DRIVER_INT_HANDLER funcIntHandler);
DWORD PCI_DRIVER_IntDisable(WDC_DEVICE_HANDLE hDev);
BOOL PCI_DRIVER_IntIsEnabled(WDC_DEVICE_HANDLE hDev);

DWORD PCI_DRIVER_EventRegister(WDC_DEVICE_HANDLE hDev, PCI_DRIVER_EVENT_HANDLER funcEventHandler);
DWORD PCI_DRIVER_EventUnregister(WDC_DEVICE_HANDLE hDev);
BOOL PCI_DRIVER_EventIsRegistered(WDC_DEVICE_HANDLE hDev);
#endif

DWORD PCI_DRIVER_GetNumAddrSpaces(WDC_DEVICE_HANDLE hDev);
BOOL PCI_DRIVER_GetAddrSpaceInfo(WDC_DEVICE_HANDLE hDev, PCI_DRIVER_ADDR_SPACE_INFO *pAddrSpaceInfo);


const char *PCI_DRIVER_GetLastErr(void);

static void ErrLog(const CHAR *sFormat, ...);
 void TraceLog(const CHAR *sFormat, ...);

#ifdef __cplusplus
}
#endif

#endif
