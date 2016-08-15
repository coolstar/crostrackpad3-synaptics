#ifndef _INTERNAL_H_
#define _INTERNAL_H_

#pragma warning(push)
#pragma warning(disable:4512)
#pragma warning(disable:4480)

#define SPBT_POOL_TAG ((ULONG) 'TBPS')

/////////////////////////////////////////////////
//
// Common includes.
//
/////////////////////////////////////////////////

#include <ntddk.h>
#include <wdm.h>
#include <wdf.h>
#include <ntstrsafe.h>

#include "spb.h"

#define RESHUB_USE_HELPER_ROUTINES
#include "reshub.h"

#include "trace.h"

#include "rmi.h"
#include "gesturerec.h"

//
// Forward Declarations
//

typedef struct _DEVICE_CONTEXT  DEVICE_CONTEXT,  *PDEVICE_CONTEXT;
typedef struct _REQUEST_CONTEXT  REQUEST_CONTEXT,  *PREQUEST_CONTEXT;

struct _DEVICE_CONTEXT 
{
    //
    // Handle back to the WDFDEVICE
    //

    WDFDEVICE FxDevice;

    //
    // Handle to the sequential SPB queue
    //

    WDFQUEUE SpbQueue;

    //
    // Connection ID for SPB peripheral
    //

	SPB_CONTEXT I2CContext;
    
    //
    // Interrupt object and wait event
    //

    WDFINTERRUPT Interrupt;

    KEVENT IsrWaitEvent;

    //
    // Setting indicating whether the interrupt should be connected
    //

    BOOLEAN ConnectInterrupt;

	BOOLEAN IsHandlingInterrupts;

	BOOLEAN ProcessedRegs;

	BOOLEAN RegsSet;

    //
    // Client request object
    //

    WDFREQUEST ClientRequest;

    //
    // WaitOnInterrupt request object
    //

    WDFREQUEST WaitOnInterruptRequest;

	WDFTIMER Timer;

	WDFQUEUE ReportQueue;

	BYTE DeviceMode;

	ULONGLONG LastInterruptTime;

	csgesture_softc sc;

	int page;

	unsigned long flags;

	struct rmi_function f01;
	struct rmi_function f11;
	struct rmi_function f30;

	unsigned int max_fingers;
	unsigned int max_x;
	unsigned int max_y;
	unsigned int x_size_mm;
	unsigned int y_size_mm;
	bool read_f11_ctrl_regs;
	uint8_t f11_ctrl_regs[RMI_F11_CTRL_REG_COUNT];

	unsigned int gpio_led_count;
	unsigned int button_count;
	unsigned long button_mask;
	unsigned long button_state_mask;

	unsigned long device_flags;
	unsigned long firmware_id;

	uint8_t f01_ctrl0;
	uint8_t interrupt_enable_mask;
	bool restore_interrupt_mask;

	uint8_t lastreport[40];
};

struct _REQUEST_CONTEXT
{    
    //
    // Associated framework device object
    //

    WDFDEVICE FxDevice;

    //
    // Variables to track write length for a sequence request.
    // There are needed to complete the client request with
    // correct bytesReturned value.
    //

    BOOLEAN IsSpbSequenceRequest;
    ULONG_PTR SequenceWriteLength;
};

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, GetDeviceContext);
WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(REQUEST_CONTEXT, GetRequestContext);

#pragma warning(pop)

#endif // _INTERNAL_H_
