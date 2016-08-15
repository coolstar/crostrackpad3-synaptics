#ifndef _DRIVER_H_
#define _DRIVER_H_

extern "C"

NTSTATUS
DriverEntry(
    _In_  PDRIVER_OBJECT   pDriverObject,
    _In_  PUNICODE_STRING  pRegistryPath
    );    

EVT_WDF_DRIVER_DEVICE_ADD       OnDeviceAdd;
EVT_WDF_OBJECT_CONTEXT_CLEANUP  OnDriverCleanup;

#define DRIVER_NAME       "SynaTP"

#define SIOCTL_TYPE 40000

#define IOCTL_SIOCTL_METHOD_OUT_DIRECT \
    CTL_CODE( SIOCTL_TYPE, 0x901, METHOD_OUT_DIRECT , FILE_ANY_ACCESS  )

#endif
