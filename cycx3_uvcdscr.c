/*
 ## Cypress CX3 Firmware Example Source (cycx3_uvcdscr.c)
 ## ===========================
 ##
 ##  Copyright Cypress Semiconductor Corporation, 2013-2014,
 ##  All Rights Reserved
 ##  UNPUBLISHED, LICENSED SOFTWARE.
 ##
 ##  CONFIDENTIAL AND PROPRIETARY INFORMATION
 ##  WHICH IS THE PROPERTY OF CYPRESS.
 ##
 ##  Use of this file is governed
 ##  by the license agreement included in the file
 ##
 ##     <install>/license/license.txt
 ##
 ##  where <install> is the Cypress software
 ##  installation root directory path.
 ##
 ## ===========================
 */


/* This file contains the USB enumeration descriptors for the CX3 UVC YUY2 application example.
 * The descriptor arrays must be 32 byte aligned if the D-cache is turned on. If the linker
 * used is not capable of supporting the aligned feature for this, then dynamically allocated
 * buffer must be used, and the descriptor must be loaded into it. */

#include "cycx3_uvc.h"
#include "cyu3mipicsi.h"

/* Standard Device Descriptor for USB 3 */
const uint8_t CyCx3USB30DeviceDscr[] =
{
    0x12,                               /* Descriptor size */
    CY_U3P_USB_DEVICE_DESCR,            /* Device descriptor type */
    0x10, 0x03,                         /* USB 3.0 */
    0xEF,                               /* Device class */
    0x02,                               /* Device Sub-class */
    0x01,                               /* Device protocol */
    0x09,                               /* Maxpacket size for EP0 : 2^9 */
    0xB4, 0x04,                         /* Vendor ID */
    0xC3, 0x00,                         /* Product ID */
    0x03, 0x01,                         /* Device release number */

    0x01,                               /* Device protocol */
    0x40,                               /* Maxpacket size for EP0 : 64 bytes */
    0xB4, 0x04,                         /* Vendor ID */
    0xC3, 0x00,                         /* Product ID */
    0x03, 0x01,                         /* Device release number */
    0x01,                               /* Manufacture string index */
    0x02,                               /* Product string index */
    0x03,                               /* Serial number string index */
    0x01                                /* Number of configurations */
};

/* Binary Device Object Store (BOS) Descriptor */
const uint8_t CyCx3USBBOSDscr[] =
{
    0x05,                               /* Descriptor size */
    CY_U3P_BOS_DESCR,                   /* Device descriptor type */
    0x16, 0x00,                         /* Length of this descriptor and all sub descriptors */
    0x02,                               /* Number of device capability descriptors */

    /* USB 2.0 Extension */
    0x07,                               /* Descriptor size */
    CY_U3P_DEVICE_CAPB_DESCR,           /* Device capability type descriptor */
    CY_U3P_USB2_EXTN_CAPB_TYPE,         /* USB 2.1 extension capability type */
	0x1E,0x64,0x00,0x00,				/* Supported device level features: LPM support, BESL supported,
											  Baseline BESL=400 us, Deep BESL=1000 us. */

    /* SuperSpeed Device Capability */
    0x0A,                               /* Descriptor size */
    CY_U3P_DEVICE_CAPB_DESCR,           /* Device capability type descriptor */
    CY_U3P_SS_USB_CAPB_TYPE,            /* SuperSpeed device capability type */
    0x00,                               /* Supported device level features  */
    0x0E, 0x00,                         /* Speeds supported by the device : SS, HS and FS */
    0x03,                               /* Functionality support */
    0x00,                               /* U1 device exit latency */
    0x00, 0x00                          /* U2 device exit latency */
};

/* Standard Device Qualifier Descriptor */
const uint8_t CyCx3USBDeviceQualDscr[] =
{
    0x0A,                               /* descriptor size */
    CY_U3P_USB_DEVQUAL_DESCR,           /* Device qualifier descriptor type */
    0x00, 0x02,                         /* USB 2.0 */
    0xEF,                               /* Device class */
    0x02,                               /* Device sub-class */
    0x01,                               /* Device protocol */
    0x40,                               /* Maxpacket size for EP0 : 64 bytes */
    0x01,                               /* Number of configurations */
    0x00                                /* Reserved */
};

/* Standard Super Speed Configuration Descriptor */
const uint8_t CyCx3USBSSConfigDscr[] =
{
    /* Configuration Descriptor*/
    0x09,                               /* Descriptor Size */
    CY_U3P_USB_CONFIG_DESCR,            /* Configuration Descriptor Type */
#ifdef CX3_UVC_1_0_SUPPORT
#ifdef STILL_CAPTURE_ENABLE
    0x54, 0x01,
#else
    0x3d, 0x01,                         /* Length of this descriptor and all sub descriptors */
#endif
#else
#ifdef STILL_CAPTURE_ENABLE
    0x29, 0x01,
#else
#ifdef BULK_TRANS_MODE
	0x12, 0x01, 						/* Length of this descriptor and all sub descriptors */
#else
    0x1b, 0x01,                         /* Length of this descriptor and all sub descriptors */
#endif
#endif
#endif
    0x02,                               /* Number of interfaces */
    0x01,                               /* Configuration number */
    0x03,                               /* Configuration string index */
    0x80,                           	/* Config characteristics - Bus powered */
    0x32,                           	/* Max power consumption of device (in 8mA unit) : 400mA */

    /* Interface Association Descriptor */
    0x08,                               /* Descriptor Size */
    CX3_INTRFC_ASSN_DESCR,              /* Interface Association Descriptor Type */
    0x00,                               /* Interface number of the VideoControl interface
                                           that is associated with this function*/
    0x02,                               /* Number of contiguous Video interfaces that are
                                           associated with this function */
    0x0E,                               /* Video Interface Class Code: CC_VIDEO */
    0x03,                               /* Subclass code: SC_VIDEO_INTERFACE_COLLECTION*/
    0x00,                               /* Protocol: PC_PROTOCOL_UNDEFINED*/
    0x00,                               /* String Descriptor index for interface */

    /* Standard Video Control Interface Descriptor (Interface 0, Alternate Setting 0)*/
    0x09,                               /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,            /* Interface Descriptor type */
    0x00,                               /* Index of this Interface */
    0x00,                               /* Alternate setting number */
    0x01,                               /* Number of end points - 1 Interrupt Endpoint*/
    0x0E,                               /* Video Interface Class Code: CC_VIDEO  */
    0x01,                               /* Interface sub class: SC_VIDEOCONTROL */
    0x00,                               /* Interface protocol code: PC_PROTOCOL_UNDEFINED.*/
    0x00,                               /* Interface descriptor string index */

    /* Class specific VC Interface Header Descriptor */
    0x0D,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class Specific Interface Descriptor type: CS_INTERFACE */
    0x01,                               /* Descriptor Sub type: VC_HEADER */
#ifdef CX3_UVC_1_0_SUPPORT
    0x00, 0x01,                         /* Revision of UVC class spec: 1.0 - Legacy version */
    0x50, 0x00,                         /* Total Size of class specific descriptors
                                           (till Output terminal) */
#else
    0x10, 0x01,                         /* Revision of UVC class spec: 1.1 - Minimum version required
                                           for USB Compliance. Not supported on Windows XP*/
    0x51, 0x00,                         /* Total Size of class specific descriptors
                                           (till Output terminal) */
#endif

    0x00, 0x6C, 0xDC, 0x02,             /* Clock frequency : 48MHz(Deprecated) */
    0x01,                               /* Number of streaming interfaces */
    0x01,                               /* VideoStreaming interface 1 belongs to this
                                           VideoControl interface*/

    /* Input (Camera) Terminal Descriptor */
    0x12,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* CS_INTERFACE */
    0x02,                               /* VC_INPUT_TERMINAL subtype */
    0x01,                               /* ID of this input terminal */
    0x01, 0x02,                         /* ITT_CAMERA type. This terminal is a camera
                                           terminal representing the CCD sensor*/
    0x00,                               /* No association terminal */
    0x00,                               /* Unused */
    0x00, 0x00,                         /* No optical zoom supported */
    0x00, 0x00,                         /* No optical zoom supported */
    0x00, 0x00,                         /* No optical zoom supported */
    0x03,                               /* Size of controls field for this terminal : 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */

    /* Processing Unit Descriptor */
#ifdef CX3_UVC_1_0_SUPPORT
    0x0C,                               /* Descriptor size */
#else
    0x0D,                               /* Descriptor size */
#endif
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x05,                               /* Processing Unit Descriptor type: VC_PROCESSING_UNIT*/
    0x02,                               /* ID of this unit */
    0x01,                               /* Source ID: 1: Conencted to input terminal */
    0x00, 0x40,                         /* Digital multiplier */
    0x03,                               /* Size of controls field for this terminal: 3 bytes */
    0x01, 0x00, 0x00,                   /* No controls supported */
    0x00,                               /* String desc index: Not used */
#ifndef CX3_UVC_1_0_SUPPORT
    0x00,                               /* Analog Video Standards Supported: None */
#endif

    /* Extension Unit Descriptor*/
    0x1C,                          // Descriptor size
    0x24,                          // Class specific interface desc type
    0x06,                          // Extension Unit Descriptor type
    0x03,                          // ID of this terminal
    0x9F, 0x6D, 0x7A, 0x94,        // 16 byte GUID
    0x2F, 0x8A, 0x8D, 0x41,
    0x85, 0x9E, 0x6C, 0x9A,
    0xA0, 0x38, 0x10, 0x14,
    0x03,                          // Number of controls in this terminal
    0x01,                          // Number of input pins in this terminal
    0x02,                          // Source ID : 2 : Connected to Proc Unit
    0x03,                          // Size of controls field for this terminal : 3 bytes
    0x3F, 0x00, 0x00,              // No controls supported
    0x00,                          // String desc index : Not used

    /* Output Terminal Descriptor */
    0x09,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x03,                               /* Output Terminal Descriptor type */
    0x04,                               /* ID of this terminal */
    0x01, 0x01,                         /* USB Streaming terminal type */
    0x00,                               /* No association terminal */
    0x03,                               /* Source ID : 3 : Connected to Extn Unit */
    0x00,                               /* String desc index : Not used */

    /* Video Control Status Interrupt Endpoint Descriptor */
    0x07,                               /* Descriptor size */
    CY_U3P_USB_ENDPNT_DESCR,            /* Endpoint Descriptor Type */
    CX3_EP_CONTROL_STATUS,              /* Endpoint address and description: EP-2 IN */
    CY_U3P_USB_EP_INTR,                 /* Interrupt End point Type */
    0x40, 0x00,                         /* Max packet size: 64 bytes */
    0x01,                               /* Servicing interval */

    /* Super Speed Endpoint Companion Descriptor */
    0x06,                               /* Descriptor size */
    CY_U3P_SS_EP_COMPN_DESCR,           /* SS Endpoint Companion Descriptor Type */
    0x00,                               /* Max no. of packets in a Burst: 1 */
    0x00,                               /* Attribute: N.A. */
#ifdef BULK_TRANS_MODE
    0x40,                               /* Bytes per interval: 1024 */
    0x00,
#else
    0x00,                               /* Bytes per interval: 1024 */
    0x04,
#endif

    /* Class Specific Interrupt Endpoint Descriptor */
    0x05,                               /* Descriptor size */
    0x25,                               /* Class Specific Endpoint Descriptor Type */
    CY_U3P_USB_EP_INTR,                 /* End point Sub Type */
    0x40, 0x00,                         /* Max packet size = 64 bytes */

    /* Standard Video Streaming Interface Descriptor (Interface 1, Alternate Setting 0) */
    0x09,                               /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,            /* Interface Descriptor type */
    0x01,                               /* Interface number: 1 */
    0x00,                               /* Alternate setting number: 0 */
#ifdef BULK_TRANS_MODE
    0x01,                               /* Number of end points: 1 Bulk Endpoint */
#else
    0x00,                               /* Number of end points : zero bandwidth */
#endif
    0x0E,                               /* Interface class : CC_VIDEO */
    0x02,                               /* Interface sub class : SC_VIDEOSTREAMING */
    0x00,                               /* Interface protocol code : PC_PROTOCOL_UNDEFINED */
    0x00,                               /* Interface descriptor string index */

    /* Class-specific Video Streaming Input Header Descriptor */
    0x0E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class-specific VS I/f Type */
    0x01,                               /* Descriptor Subtype: Input Header */
    0x01,                               /* 1 format desciptor follows */
#ifdef STILL_CAPTURE_ENABLE
    0x96, 0x00,
#else
    0x7f, 0x00,                         /* Total size of Class specific VS descr */
#endif
    CX3_EP_BULK_VIDEO,                  /* EP address for BULK video data: EP 3 IN */
    0x00,                               /* No dynamic format change supported */
    0x04,                               /* Output terminal ID : 4 */
#ifdef STILL_CAPTURE_ENABLE
    0x02,                               /* Method 2 Still image capture method supported */
#else
    0x00,                               /* No Still image capture supported */
#endif
    0x00,                               /* Hardware trigger NOT supported */
    0x00,                               /* Hardware to initiate still image capture not supported */
    0x01,                               /* Size of controls field : 1 byte */
    0x00,                               /* D2 : Compression quality supported - No compression*/

    /* Class specific Uncompressed VS format descriptor */
    0x1B,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class-specific VS interface Type */
    0x04,                               /* Subtype : VS_FORMAT_UNCOMPRESSED */
    0x01,                               /* Format desciptor index */
    0x02,                               /* Number of Frame Descriptors that follow this descriptor: 3 */
    
#ifndef YUY2_COLOR_MODE
	/* GUID, globally unique identifier used to identify streaming-encoding format: RGB888  */
    0X7D, 0XEB, 0X36, 0XE4,
    0X4F, 0X52, 0XCE, 0X11,
    0X9F, 0X53, 0X00, 0X20,
    0XAF, 0X0B, 0XA7, 0X70,
    0x18,                               /* Number of bits per pixel: 24*/
#else 
	/* GUID, globally unique identifier used to identify streaming-encoding format: YUY2  */
    0x59, 0x55, 0x59, 0x32,             /*MEDIASUBTYPE_YUY2 GUID: 32595559-0000-0010-8000-00AA00389B71 */
    0x00, 0x00, 0x10, 0x00,
    0x80, 0x00, 0x00, 0xAA,
    0x00, 0x38, 0x9B, 0x71,
    0x10,                               /* Number of bits per pixel: 16*/
#endif 
	0x01,                               /* Optimum Frame Index for this stream: 2 (1080p) */
    0x00,                               /* X dimension of the picture aspect ratio; Non-interlaced */
    0x00,                               /* Y dimension of the pictuer aspect ratio: Non-interlaced */
    0x00,                               /* Interlace Flags: Progressive scanning, no interlace */
    0x00,                               /* duplication of the video stream restriction: 0 - no restriction */


    /* Class specific Uncompressed VS frame descriptor 1 - 1280*400@ 10/20/30/60fps*/
    0x2A,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype: Uncompressed frame interface*/
    0x01,                               /* Frame Descriptor Index: 2 */
    0x00,                               /* No Still image capture method supported */
    0x00, 0x05,                         /* Width in pixel:  1280 */
    0x90, 0x01,                         /* Height in pixel: 400 */
#ifndef YUY2_COLOR_MODE
    0x00, 0x00, 0x53, 0x07,             /* Min bit rate (bits/s): 1280 x 400 x 3 x 8 x 10 = 122880000 */
    0x00, 0x00, 0xf2, 0x2b,             /* Max bit rate (bits/s): 1280 x 400 x 3 x 8 x 60 = 491520000 */
    0x00, 0x70, 0x17, 0x00,             /* Maximum video or still frame size in bytes(Deprecated): 1280 x 400 x 3 */
#else
    0x00, 0x00, 0xE2, 0x04,             /* Min bit rate (bits/s): 1280 x 400 x 2 x 8 x 10 = 81920000 */
    0x00, 0x00, 0x4c, 0x1d,             /* Max bit rate (bits/s): 1280 x 400 x 2 x 8 x 60 = 491520000 */
    0x00, 0xa0, 0x0f, 0x00,             /* Maximum video or still frame size in bytes(Deprecated): 1280 x 400 x 2 */
#endif
    0x0a, 0x8b, 0x02, 0x00,             /* Default frame interval (in 100ns units): (1/60)x10^7 */
    0x04,                               /* Frame interval type : No of discrete intervals */
    0x0a, 0x8b, 0x02, 0x00,             /* Frame interval 3: 60fps frame interval */
    0x15, 0x16, 0x05, 0x00,             /* Frame interval 3: 30fps frame interval */
    0x20, 0xa1, 0x07, 0x00,             /* Frame interval 3: 20fps frame interval */
    0x40, 0x42, 0x0f, 0x00,             /* Frame interval 3: 10fps frame interval */
    /* Class specific Uncompressed VS frame descriptor 1 - 2560*800@ 10/20/30fps*/
    0x26,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype: Uncompressed frame interface*/
    0x02,                               /* Frame Descriptor Index: 2 */
    0x00,                               /* No Still image capture method supported */
    0x00, 0x0a,                         /* Width in pixel:  1280 */
    0x20, 0x03,                         /* Height in pixel: 400 */
#ifndef YUY2_COLOR_MODE
    0x00, 0x00, 0x4c, 0x1d,             /* Min bit rate (bits/s): 2560 x 800 x 3 x 8 x 10 = 491520000 */
    0x00, 0x00, 0xe4, 0x57,             /* Max bit rate (bits/s): 2560 x 800 x 3 x 8 x 30 = 1474560000 */
    0x00, 0xc0, 0x5d, 0x00,             /* Maximum video or still frame size in bytes(Deprecated): 2560 x 800 x 3 */
    0x15, 0x16, 0x05, 0x00,             /* Default frame interval (in 100ns units): (1/30)x10^7 */
#else
    0x00, 0x00, 0x88, 0x13,             /* Min bit rate (bits/s): 2560 x 800 x 2 x 8 x 10 = 327680000 */
    0x00, 0x00, 0x30, 0x75,             /* Max bit rate (bits/s): 2560 x 800 x 2 x 8 x 30 = 983040000 */
    0x00, 0x80, 0x3e, 0x00,             /* Maximum video or still frame size in bytes(Deprecated): 2560 x 800 x 2 */
    0x0a, 0x8b, 0x02, 0x00,             /* Default frame interval (in 100ns units): (1/30)x10^7 */
#endif
    0x03,                               /* Frame interval type : No of discrete intervals */
    0x15, 0x16, 0x05, 0x00,             /* Frame interval 3: 30fps frame interval */
    0x20, 0xa1, 0x07, 0x00,             /* Frame interval 3: 20fps frame interval */
    0x40, 0x42, 0x0f, 0x00,             /* Frame interval 3: 10fps frame interval */


#ifdef STILL_CAPTURE_ENABLE
    /* Still image descriptor -YUV with QVGA resolution */
    0x17,                   /*Size of this descriptor*/
    0x24,                   /*CS_INTERFACE descriptor type*/
    0x03,                   /*VS_STILL_IMAGE_FRAME descriptor subtype*/
    0x00,                   /*If method 3 is used, endpoint address is mentioned here*/
    0x04,                   //No of frame Resolutions Follows
    0x20, 0x0A,                         /* Width in pixel: 2592 */
    0x98, 0x07,                         /* Height in pixel: 1944 */
    0xD0, 0x02,                         /* Width in pixel:  1280 */
    0x32, 0x00,                         /* Height in pixel: 480 */
    0x00, 0x05,                         /* Width in pixel: 1280 */
    0xD0, 0x02,                         /* Height in pixel: 720 */
    0x80, 0x02,                         /* Width in pixel:  640 */
    0xE0, 0x01,                         /* Height in pixel: 480 */
    0x01,                   /*Compression patterns supported*/
    0x00,                   /*No compression*/
#endif
    /* Color matching descriptor */
    0x06,
    0x24,
    0x0D,
    0x00,
    0x00,
    0x00,

#ifdef BULK_TRANS_MODE
#else
    /* Standard video streaming interface descriptor (Alternate setting 1) */
    0x09,                           /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,        /* Interface descriptor type */
    0x01,                           /* Interface number */
    0x01,                           /* Alternate setting number */
    0x01,                           /* Number of end points : 1 ISO EP */
    0x0E,                           /* Interface class : CC_VIDEO */
    0x02,                           /* Interface sub class : CC_VIDEOSTREAMING */
    0x00,                           /* Interface protocol code : Undefined */
    0x00,                           /* Interface descriptor string index */
#endif

    /* Endpoint Descriptor for ISO/BULK Streaming Video Data */
    0x07,                               /* Descriptor size */
    CY_U3P_USB_ENDPNT_DESCR,            /* Endpoint Descriptor Type */
    CX3_EP_BULK_VIDEO,                  /* Endpoint address and description: EP 3 IN */
#ifdef BULK_TRANS_MODE
	CY_U3P_USB_EP_BULK,			/* BULK End point */
#else
    CY_U3P_USB_EP_ISO | 0x04,           /* BULK End point */
#endif
    CX3_EP_VIDEO_PKT_SIZE_L,       /* CX3_EP_BULK_VIDEO_PKT_SIZE_L */
    CX3_EP_VIDEO_PKT_SIZE_H,       /* CX3_EP_BULK_VIDEO_PKT_SIZE_H */
#ifdef BULK_TRANS_MODE
	0x00,								/* Servicing interval for data transfers */
#else
    0x01,                               /* Servicing interval for data transfers */
#endif

    /* Super Speed Endpoint Companion Descriptor */
    0x06,                           	/* Descriptor size */
    CY_U3P_SS_EP_COMPN_DESCR,           /* SS Endpoint Companion Descriptor Type */
#ifdef BULK_TRANS_MODE
    0x0F,                               /* Max number of packets per burst: 16 */
    0x00,                               /* Attribute: Streams not defined */
    0x00,                               /* No meaning for bulk */
    0x00
#else
    CX3_EP_ISO_VIDEO_SS_BURST - 1,		/* Max no. of packets in a burst */
    CX3_EP_ISO_VIDEO_SS_MULT - 1,		/* Mult setting: Number of bursts per service interval. */
    0x00, 0x04 * CX3_EP_ISO_VIDEO_PKTS_COUNT /* Bytes per interval : 1024 */
#endif
};

/* Standard High Speed Configuration Descriptor */
const uint8_t CyCx3USBHSConfigDscr[] =
{
    /* Configuration descriptor */
    0x09,							/* Descriptor size */
    CY_U3P_USB_CONFIG_DESCR,        /* Configuration descriptor type */
#ifdef CX3_UVC_1_0_SUPPORT
#ifdef STILL_CAPTURE_ENABLE
    0xFC, 0x00,
#else
    0xF1, 0x00,                         /* Length of this descriptor and all sub descriptors */
#endif
#else
#ifdef STILL_CAPTURE_ENABLE
    0xFD, 0x00,
#else
    0xF2, 0x00,                         /* Length of this descriptor and all sub descriptors */
#endif
#endif
    0x02,                           /* Number of interfaces */
    0x01,                           /* Configuration number */
    0x04,                               /* Configuration string index */
    0xC0,                               /* Config characteristics - self powered */
    0x32,                               /* Max power consumption of device (in 2mA unit) : 100mA */

    /* Interface Association Descriptor */
    0x08,                               /* Descriptor Size */
    CX3_INTRFC_ASSN_DESCR,              /* Interface Association Descriptor Type */
    0x00,                               /* Interface number of the VideoControl interface
                                           that is associated with this function*/
    0x02,                               /* Number of contiguous Video interfaces that are
                                           associated with this function */
    0x0E,                               /* Video Interface Class Code: CC_VIDEO */
    0x03,                               /* Subclass code: SC_VIDEO_INTERFACE_COLLECTION*/
    0x00,                               /* Protocol: PC_PROTOCOL_UNDEFINED*/
    0x00,                               /* String Descriptor index for interface */

    /* Standard Video Control Interface Descriptor (Interface 0, Alternate Setting 0)*/
    0x09,                           /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,            /* Interface Descriptor type */
    0x00,                               /* Index of this Interface */
    0x00,                           /* Alternate setting number */
    0x01,                               /* Number of end points - 1 Interrupt Endpoint*/
    0x0E,                               /* Video Interface Class Code: CC_VIDEO  */
    0x01,                               /* Interface sub class: SC_VIDEOCONTROL */
    0x00,                               /* Interface protocol code: PC_PROTOCOL_UNDEFINED.*/
    0x00,                           /* Interface descriptor string index */

    /* Class specific VC Interface Header Descriptor */
    0x0D,                           /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class Specific Interface Descriptor type: CS_INTERFACE */
    0x01,                               /* Descriptor Sub type: VC_HEADER */
#ifdef CX3_UVC_1_0_SUPPORT
    0x00, 0x01,                         /* Revision of UVC class spec: 1.0 - Legacy version */
    0x50, 0x00,                         /* Total Size of class specific descriptors
                                           (till Output terminal) */
#else
    0x10, 0x01,                         /* Revision of UVC class spec: 1.1 - Minimum version required
                                           for USB Compliance. Not supported on Windows XP*/
    0x51, 0x00,                         /* Total Size of class specific descriptors
                                           (till Output terminal) */
#endif
    0x00, 0x6C, 0xDC, 0x02,             /* Clock frequency : 48MHz(Deprecated) */
    0x01,                           /* Number of streaming interfaces */
    0x01,                               /* VideoStreaming interface 1 belongs to this
                                           VideoControl interface*/

    /* Input (Camera) Terminal Descriptor */
    0x12,                           /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* CS_INTERFACE */
    0x02,                               /* VC_INPUT_TERMINAL subtype */
    0x01,                               /* ID of this input terminal */
    0x01, 0x02,                         /* ITT_CAMERA type. This terminal is a camera
                                           terminal representing the CCD sensor*/
    0x00,                           /* No association terminal */
    0x00,                               /* Unused */
    0x00, 0x00,                     /* No optical zoom supported */
    0x00, 0x00,                     /* No optical zoom supported */
    0x00, 0x00,                     /* No optical zoom supported */
    0x03,                           /* Size of controls field for this terminal : 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */

    /* Processing Unit Descriptor */
#ifdef CX3_UVC_1_0_SUPPORT
    0x0C,                           /* Descriptor size */
#else
    0x0D,                               /* Descriptor size */
#endif
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x05,                               /* Processing Unit Descriptor type: VC_PROCESSING_UNIT*/
    0x02,                               /* ID of this unit */
    0x01,                               /* Source ID: 1: Conencted to input terminal */
    0x00, 0x40,                         /* Digital multiplier */
    0x03,                           /* Size of controls field for this terminal : 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */
    0x00,                               /* String desc index: Not used */
#ifndef CX3_UVC_1_0_SUPPORT
    0x00,                               /* Analog Video Standards Supported: None */
#endif
    /* Extension Unit Descriptor */
    0x1C,                           /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x06,                               /* Extension Unit Descriptor type */
    0x03,                           /* ID of this terminal */
    0xFF, 0xFF, 0xFF, 0xFF,         /* 16 byte GUID */
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0x00,                           /* Number of controls in this terminal */
    0x01,                           /* Number of input pins in this terminal */
    0x02,                               /* Source ID : 2 : Connected to Proc Unit */
    0x03,                           /* Size of controls field for this terminal : 3 bytes */
    0x3F, 0x00, 0x00,                   /* No controls supported */
    0x00,                               /* String descriptor index : Not used */

    /* Output Terminal Descriptor */
    0x09,                           /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x03,                               /* Output Terminal Descriptor type */
    0x04,                           /* ID of this terminal */
    0x01, 0x01,                     /* USB Streaming terminal type */
    0x00,                           /* No association terminal */
    0x03,                               /* Source ID : 3 : Connected to Extn Unit */
    0x00,                               /* String desc index : Not used */

    /* Video Control Status Interrupt Endpoint Descriptor */
    0x07,                           /* Descriptor size */
    CY_U3P_USB_ENDPNT_DESCR,            /* Endpoint Descriptor Type */
    CX3_EP_CONTROL_STATUS,              /* Endpoint address and description: EP-2 IN */
    CY_U3P_USB_EP_INTR,                 /* Interrupt End point Type */
    0x40, 0x00,                         /* Max packet size: 64 bytes */
    0x01,                               /* Servicing interval */

    /* Class Specific Interrupt Endpoint Descriptor */
    0x05,                           /* Descriptor size */
    0x25,                           /* Class specific endpoint descriptor type */
    CY_U3P_USB_EP_INTR,             /* End point sub type */
    0x40, 0x00,                     /* Max packet size = 64 bytes */

    /* Standard Video Streaming Interface Descriptor (Interface 1, Alternate Setting 0) */
    0x09,                           /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,        /* Interface descriptor type */
    0x01,                               /* Interface number: 1 */
    0x00,                               /* Alternate setting number: 0 */
    0x01,                               /* Number of end points: 1 Bulk endopoint*/
    0x0E,                           /* Interface class : CC_VIDEO */
    0x02,                               /* Interface sub class : SC_VIDEOSTREAMING */
    0x00,                               /* Interface protocol code : PC_PROTOCOL_UNDEFINED */
    0x00,                           /* Interface descriptor string index */

    /* Class-specific Video Streaming Input Header Descriptor */
    0x0E,                           /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class-specific VS interface type */
    0x01,                               /* Descriptotor subtype : Input Header */
    0x01,                           /* 1 format desciptor follows */
#ifdef STILL_CAPTURE_ENABLE
    0x76, 0x00,
#else
    0x6B, 0x00,                         /* Total size of class specific VS descr */
#endif
    CX3_EP_BULK_VIDEO,                  /* EP address for BULK video data: EP 3 IN  */
    0x00,                               /* No dynamic format change supported */
    0x04,                           /* Output terminal ID : 4 */
#ifdef STILL_CAPTURE_ENABLE
    0x02,                               /* Method 2 Still image capture supported */
#else
    0x00,                               /* No Still image capture method supported */
#endif
    0x00,                               /* Hardware trigger not supported */
    0x00,                               /* Hardware to initiate still image capture not supported*/
    0x01,                           /* Size of controls field : 1 byte */
    0x00,                               /* D2 : Compression quality supported - No compression */

    /* Class specific VS format descriptor */
    0x1B,                           /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class-specific VS interface Type */
    0x04,                               /* Subtype : VS_FORMAT_UNCOMPRESSED  */
    0x01,                           /* Format desciptor index */
    0x02,                               /* Number of Frame Descriptors that follow this descriptor: 2 */
    /* GUID, globally unique identifier used to identify streaming-encoding format: YUY2  */
    0x59, 0x55, 0x59, 0x32,             /*MEDIASUBTYPE_YUY2 GUID: 32595559-0000-0010-8000-00AA00389B71 */
    0x00, 0x00, 0x10, 0x00,
    0x80, 0x00, 0x00, 0xAA,
    0x00, 0x38, 0x9B, 0x71,
    0x10,                               /* Number of bits per pixel: 16*/
    0x01,                               /* Optimum Frame Index for this stream: 1 (640x480) */
    0x00,                               /* X dimension of the picture aspect ratio; Non-interlaced */
    0x00,                               /* Y dimension of the pictuer aspect ratio: Non-interlaced */
    0x00,                               /* Interlace Flags: Progressive scanning, no interlace */
    0x00,                               /* duplication of the video stream restriction: 0 - no restriction */

    /* Class specific Uncompressed VS frame descriptor 1 - 640x480 @ 30 fps*/
    0x1E,                           /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype: Uncompressed frame interface*/
    0x01,                               /* Frame Descriptor Index: 1 */
    0x00,                               /* No Still image capture method supported */
    0x80, 0x02,                         /* Width in pixel:  640 */
    0xE0, 0x01,                         /* Height in pixel: 480 */
    0x00, 0x00, 0x94, 0x11,             /* Min bit rate (bits/s): 640 x 480 x 2 x 60 x 8 = 294912000 */
    0x00, 0x00, 0x94, 0x11,             /* Max bit rate (bits/s): Fixed rate so same as Min  */
    0x00, 0x60, 0x09, 0x00,             /* Maximum video or still frame size in bytes(Deprecated): 640 x 480 x 2*/
    0x15, 0x16, 0x05, 0x00,             /* Default frame interval (in 100ns units): 333333. */
    0x01,                           /* Frame interval type : No of discrete intervals */
    0x15, 0x16, 0x05, 0x00,             /* Frame interval 3: Same as Default frame interval */

    /* Class specific Uncompressed VS frame descriptor 2 - 640x480 @ 60fps */
    0x1E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype: Uncompressed frame interface*/
    0x02,                               /* Frame Descriptor Index: 2 */
    0x00,                               /* No Still image capture method supported */
    0x80, 0x02,                         /* Width in pixel:  640 */
    0xE0, 0x01,                         /* Height in pixel: 480 */
    0x00, 0x00, 0x94, 0x11,             /* Min bit rate (bits/s): 640 x 480 x 2 x 60 x 8 = 294912000 */
    0x00, 0x00, 0x94, 0x11,             /* Max bit rate (bits/s): Fixed rate so same as Min  */
    0x00, 0x60, 0x09, 0x00,             /* Maximum video or still frame size in bytes(Deprecated): 640 x 480 x 2*/
    0x0A, 0x8B, 0x02, 0x00,             /* Default frame interval (in 100ns units): 166666. */
    0x01,                               /* Frame interval type : No of discrete intervals */
    0x0A, 0x8B, 0x02, 0x00,             /* Frame interval 3: Same as Default frame interval */

#ifdef STILL_CAPTURE_ENABLE
    /* Still image descriptor -YUV with QVGA resolution */
    0x0B,                   /*Size of this descriptor*/
    0x24,                   /*CS_INTERFACE descriptor type*/
    0x03,                   /*VS_STILL_IMAGE_FRAME descriptor subtype*/
    0x00,                   /*If method 3 is used, endpoint address is mentioned here*/
    0x01,                   //No of frame Resolutions Follows
    0x80, 0x02,                         /* Width in pixel:  640 */
    0xE0, 0x01,                         /* Height in pixel: 480 */
    0x01,                   /*Compression patterns supported*/
    0x00,                   /*No compression*/
#endif

    /* Color matching descriptor */
    0x06,
    0x24,
    0x0D,
    0x00,
    0x00,
    0x00,

    /* Endpoint descriptor for Bulk streaming video data */
    0x07,                           /* Descriptor size */
    CY_U3P_USB_ENDPNT_DESCR,            /* Endpoint Descriptor Type */
    CX3_EP_BULK_VIDEO,                  /* Endpoint address and description: EP 3 IN */
    CY_U3P_USB_EP_BULK,                 /* BULK End point */
    0x00,                               /* Packet Size: 512 bytes */
    0x02,
    0x00                                /* Servicing interval for data transfers */
};

/* Standard Full Speed Configuration Descriptor*/
const uint8_t CyCx3USBFSConfigDscr[] =
{
    /* Configuration descriptor */
    0x09,                           /* Descriptor size */
    CY_U3P_USB_CONFIG_DESCR,        /* Configuration descriptor type */
#ifdef CX3_UVC_1_0_SUPPORT
    0xEB, 0x00,                         /* Length of this descriptor and all sub descriptors */
#else
    0xEC, 0x00,                         /* Length of this descriptor and all sub descriptors */
#endif
    0x02,                               /* Number of interfaces */
    0x01,                           /* Configuration number */
    0x05,                               /* Configuration string index */
    0xC0,                               /* Config characteristics - self powered */
    0x32,                           /* Max power consumption of device (in 2mA unit) : 100mA */

    /* Interface Association Descriptor */
    0x08,                               /* Descriptor Size */
    CX3_INTRFC_ASSN_DESCR,              /* Interface Association Descriptor Type */
    0x00,                               /* Interface number of the VideoControl interface
                                           that is associated with this function*/
    0x02,                               /* Number of contiguous Video interfaces that are
                                           associated with this function */
    0x0E,                               /* Video Interface Class Code: CC_VIDEO */
    0x03,                               /* Subclass code: SC_VIDEO_INTERFACE_COLLECTION*/
    0x00,                               /* Protocol: PC_PROTOCOL_UNDEFINED*/
    0x00,                               /* String Descriptor index for interface */

    /* Standard Video Control Interface Descriptor (Interface 0, Alternate Setting 0)*/
    0x09,                               /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,            /* Interface Descriptor type */
    0x00,                               /* Index of this Interface */
    0x00,                               /* Alternate setting number */
    0x01,                               /* Number of end points - 1 Interrupt Endpoint*/
    0x0E,                               /* Video Interface Class Code: CC_VIDEO  */
    0x01,                               /* Interface sub class: SC_VIDEOCONTROL */
    0x00,                               /* Interface protocol code: PC_PROTOCOL_UNDEFINED.*/
    0x00,                               /* Interface descriptor string index */

    /* Class specific VC Interface Header Descriptor */
    0x0D,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class Specific Interface Descriptor type: CS_INTERFACE */
    0x01,                               /* Descriptor Sub type: VC_HEADER */
#ifdef CX3_UVC_1_0_SUPPORT
    0x00, 0x01,                         /* Revision of UVC class spec: 1.0 - Legacy version */
    0x50, 0x00,                         /* Total Size of class specific descriptors
                                           (till Output terminal) */
#else
    0x10, 0x01,                         /* Revision of UVC class spec: 1.1 - Minimum version required
                                           for USB Compliance. Not supported on Windows XP*/
    0x51, 0x00,                         /* Total Size of class specific descriptors
                                           (till Output terminal) */
#endif
    0x00, 0x6C, 0xDC, 0x02,             /* Clock frequency : 48MHz(Deprecated) */
    0x01,                               /* Number of streaming interfaces */
    0x01,                               /* VideoStreaming interface 1 belongs to this
                                           VideoControl interface*/

    /* Input (Camera) Terminal Descriptor */
    0x12,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* CS_INTERFACE */
    0x02,                               /* VC_INPUT_TERMINAL subtype */
    0x01,                               /* ID of this input terminal */
    0x01, 0x02,                         /* ITT_CAMERA type. This terminal is a camera
                                           terminal representing the CCD sensor*/
    0x00,                               /* No association terminal */
    0x00,                               /* Unused */
    0x00, 0x00,                         /* No optical zoom supported */
    0x00, 0x00,                         /* No optical zoom supported */
    0x00, 0x00,                         /* No optical zoom supported */
    0x03,                               /* Size of controls field for this terminal : 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */

    /* Processing Unit Descriptor */
#ifdef CX3_UVC_1_0_SUPPORT
    0x0C,                               /* Descriptor size */
#else
    0x0D,                               /* Descriptor size */
#endif
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x05,                               /* Processing Unit Descriptor type: VC_PROCESSING_UNIT*/
    0x02,                               /* ID of this unit */
    0x01,                               /* Source ID: 1: Conencted to input terminal */
    0x00, 0x40,                         /* Digital multiplier */
    0x03,                               /* Size of controls field for this terminal: 3 bytes */
    0x00, 0x00, 0x00,                   /* No controls supported */
    0x00,                               /* String desc index: Not used */
#ifndef CX3_UVC_1_0_SUPPORT
    0x00,                               /* Analog Video Standards Supported: None */
#endif


    /* Extension Unit Descriptor */
    0x1C,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x06,                               /* Extension Unit Descriptor type */
    0x03,                               /* ID of this terminal */
    0xFF, 0xFF, 0xFF, 0xFF,             /* 16 byte GUID */
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0x00,                               /* Number of controls in this terminal */
    0x01,                               /* Number of input pins in this terminal */
    0x02,                               /* Source ID : 2 : Connected to Proc Unit */
    0x03,                               /* Size of controls field for this terminal : 3 bytes */
    0x3F, 0x00, 0x00,                   /* No controls supported */
    0x00,                               /* String descriptor index : Not used */

    /* Output Terminal Descriptor */
    0x09,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class specific interface desc type */
    0x03,                               /* Output Terminal Descriptor type */
    0x04,                               /* ID of this terminal */
    0x01, 0x01,                         /* USB Streaming terminal type */
    0x00,                               /* No association terminal */
    0x03,                               /* Source ID : 3 : Connected to Extn Unit */
    0x00,                               /* String desc index : Not used */

    /* Video Control Status Interrupt Endpoint Descriptor */
    0x07,                               /* Descriptor size */
    CY_U3P_USB_ENDPNT_DESCR,            /* Endpoint Descriptor Type */
    CX3_EP_CONTROL_STATUS,              /* Endpoint address and description: EP-2 IN */
    CY_U3P_USB_EP_INTR,                 /* Interrupt End point Type */
    0x40, 0x00,                         /* Max packet size: 64 bytes */
    0x01,                               /* Servicing interval */

    /* Class Specific Interrupt Endpoint Descriptor */
    0x05,                               /* Descriptor size */
    0x25,                               /* Class specific endpoint descriptor type */
    CY_U3P_USB_EP_INTR,                 /* End point sub type */
    0x40, 0x00,                         /* Max packet size = 64 bytes */

    /* Standard Video Streaming Interface Descriptor (Interface 1, Alternate Setting 0) */
    0x09,                               /* Descriptor size */
    CY_U3P_USB_INTRFC_DESCR,            /* Interface descriptor type */
    0x01,                               /* Interface number: 1 */
    0x00,                               /* Alternate setting number: 0 */
    0x01,                               /* Number of end points: 1 Bulk endopoint*/
    0x0E,                               /* Interface class : CC_VIDEO */
    0x02,                               /* Interface sub class : SC_VIDEOSTREAMING */
    0x00,                               /* Interface protocol code : PC_PROTOCOL_UNDEFINED */
    0x00,                               /* Interface descriptor string index */

    /* Class-specific Video Streaming Input Header Descriptor */
    0x0E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class-specific VS interface type */
    0x01,                               /* Descriptotor subtype : Input Header */
    0x01,                               /* 1 format desciptor follows */
    0x65, 0x00,                         /* Total size of class specific VS descr */
    CX3_EP_BULK_VIDEO,                  /* EP address for BULK video data: EP 3 IN  */
    0x00,                               /* No dynamic format change supported */
    0x04,                               /* Output terminal ID : 4 */
    0x00,                               /* No Still image capture method supported */
    0x00,                               /* Hardware trigger not supported */
    0x00,                               /* Hardware to initiate still image capture not supported*/
    0x01,                               /* Size of controls field : 1 byte */
    0x00,                               /* D2 : Compression quality supported - No compression */

    /* Class specific VS format descriptor */
    0x1B,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Class-specific VS interface Type */
    0x04,                               /* Subtype : VS_FORMAT_UNCOMPRESSED  */
    0x01,                               /* Format desciptor index */
    0x02,                               /* Number of Frame Descriptors that follow this descriptor: 2 */
    /* GUID, globally unique identifier used to identify streaming-encoding format: YUY2  */
    0x59, 0x55, 0x59, 0x32,             /* MEDIASUBTYPE_YUY2 GUID: 32595559-0000-0010-8000-00AA00389B71 */
    0x00, 0x00, 0x10, 0x00,
    0x80, 0x00, 0x00, 0xAA,
    0x00, 0x38, 0x9B, 0x71,
    0x10,                               /* Number of bits per pixel: 16*/
    0x02,                               /* Optimum Frame Index for this stream: 1 (320x240) */
    0x00,                               /* X dimension of the picture aspect ratio; Non-interlaced */
    0x00,                               /* Y dimension of the pictuer aspect ratio: Non-interlaced */
    0x00,                               /* Interlace Flags: Progressive scanning, no interlace */
    0x00,                               /* duplication of the video stream restriction: 0 - no restriction */

    /* Class specific Uncompressed VS Frame Descriptor 1 - 320x240@5fps*/
    0x1E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype: Uncompressed frame interface*/
    0x01,                               /* Frame Descriptor Index: 1 */
    0x00,                               /* No Still image capture method supported */
    0x40, 0x01,                         /* Width in pixel:  320 */
    0xF0, 0x00,                         /* Height in pixel: 240 */
    0x00, 0xC0, 0x5D, 0x00,             /* Min bit rate (bits/s): 320 x 240 x 2 x 5 x 8 = 6144000 */
    0x00, 0xC0, 0x5D, 0x00,             /* Max bit rate (bits/s): Fixed rate so same as Min  */
    0x00, 0x58, 0x02, 0x00,             /* Maximum video or still frame size in bytes(Deprecated): 320 x 240 x 2*/
    0x80, 0x84, 0x1E, 0x00,             /* Default frame interval (in 100ns units): (1/5)x10^7 */
    0x01,                               /* Frame interval type : No of discrete intervals */
    0x80, 0x84, 0x1E, 0x00,             /* Frame interval 3: Same as Default frame interval */

    /* Class specific Uncompressed VS frame descriptor 2 - 320 x 240 @2fps - Needed only for compliance.
     * The USBCV30 USB 2.0 UVC Tests 'Standard VS Interface Descriptor Test - Device Configured' and
     * 'Standard VS Interface Descriptor Test - Device Addressed', Fail if only one VS Frame descriptor
     * is provided.
     */
    0x1E,                               /* Descriptor size */
    CX3_CS_INTRFC_DESCR,                /* Descriptor type*/
    0x05,                               /* Subtype: Uncompressed frame interface*/
    0x02,                               /* Frame Descriptor Index: 1 */
    0x00,                               /* No Still image capture method supported */
    0x40, 0x01,                         /* Width in pixel:  320 */
    0xF0, 0x00,                         /* Height in pixel: 240 */
    0x00, 0x80, 0x25, 0x00,             /* Min bit rate (bits/s): 320 x 240 x 2 x 2 x 8 = 2457600 */
    0x00, 0x80, 0x25, 0x00,             /* Max bit rate (bits/s): Fixed rate so same as Min  */
    0x00, 0x58, 0x02, 0x00,             /* Maximum video or still frame size in bytes(Deprecated): 320 x 240 x 2*/
    0x40, 0x4B, 0x4C, 0x00,             /* Default frame interval (in 100ns units): (1/2)x10^7 */
    0x01,                               /* Frame interval type : No of discrete intervals */
    0x40, 0x4B, 0x4C, 0x00,             /* Frame interval 3: Same as Default frame interval */

    /* Endpoint descriptor for Bulk streaming video data */
    0x07,                               /* Descriptor size */
    CY_U3P_USB_ENDPNT_DESCR,            /* Endpoint Descriptor Type */
    CX3_EP_BULK_VIDEO,                  /* Endpoint address and description: EP 3 IN */
    CY_U3P_USB_EP_BULK,                 /* BULK End point */
    0x40,                               /* EP Packet Size: 64 bytes */
    0x00,
    0x00                                /* Servicing interval for data transfers */
};

/* Standard language ID string descriptor */
const uint8_t CyCx3USBStringLangIDDscr[] =
{
    0x04,                               /* Descriptor size */
    CY_U3P_USB_STRING_DESCR,            /* Device descriptor type */
    0x09, 0x04                          /* Language ID supported */
};



/* Standard Product String Descriptor */
uint8_t CyCx3USBSerialNumberDscr[] =
{
    0x22,                           /* Descriptor Size */
    CY_U3P_USB_STRING_DESCR,        /* Device Descriptor Type */
    '0', 0x00,
    '1', 0x00,
    '0', 0x00,
    '1', 0x00,
    '0', 0x00,
    '1', 0x00,
    '0', 0x00,
    '0', 0x00,
    '1', 0x00,
    '0', 0x00,
    '1', 0x00,
    '0', 0x00,
    '1', 0x00,
    '0', 0x00,
    '0', 0x00,
    '1', 0x00

};


/* Standard product string descriptor */
const uint8_t CyCx3USBConfigSSDscr[] =
{
    0x10,                               /* Descriptor Size */
    CY_U3P_USB_STRING_DESCR,            /* Device descriptor type */
    'U', 0x00,                          /* Super-Speed Configuration Descriptor */
    'S', 0x00,
    'B', 0x00,
    '-', 0x00,
    '3', 0x00,
    '.', 0x00,
    '0', 0x00
};
/* Standard product string descriptor */
const uint8_t CyCx3USBConfigHSDscr[] =
{
    0x10,                               /* Descriptor Size */
    CY_U3P_USB_STRING_DESCR,            /* Device descriptor type */
    'U', 0x00,                          /* High-Speed Configuration Descriptor */
    'S', 0x00,
    'B', 0x00,
    '-', 0x00,
    '2', 0x00,
    '.', 0x00,
    '1', 0x00
};
/* Standard product string descriptor */
const uint8_t CyCx3USBConfigFSDscr[] =
{
    0x10,                               /* Descriptor Size */
    CY_U3P_USB_STRING_DESCR,            /* Device descriptor type */
    'U', 0x00,                          /* Full-Speed Configuration Descriptor */
    'S', 0x00,
    'B', 0x00,
    '-', 0x00,
    '1', 0x00,
    '.', 0x00,
    '1', 0x00
};

/* UVC Probe Control Settings */
uint8_t glProbeCtrl[CX3_APP_MAX_PROBE_SETTING] = {
    0x00, 0x00,                         /* bmHint : No fixed parameters */
    0x01,                               /* Use 1st Video format index */
    0x01,                               /* Use 1st Video frame index */
    0x0A, 0x8B, 0x02, 0x00,             /* Desired frame interval in 100ns */
    0x00, 0x00,                         /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                         /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                         /* Compression quality control */
    0x00, 0x00,                         /* Window size for average bit rate */
    0x00, 0x00,                         /* Internal video streaming i/f latency in ms */
    0x00, 0x48, 0x3F, 0x00,             /* Max video frame size in bytes */
#ifdef CX3_UVC_1_0_SUPPORT
    0x00, 0x90, 0x00, 0x00              /* No. of bytes device can rx in single payload: 32KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
#ifdef BULK_TRANS_MODE
	0x00, 0x90, 0x00, 0x00, 			/* No. of bytes device can rx in single payload: 32KB */
#else
	0x00, 0x30, 0x00, 0x00, 			/* No. of bytes device can rx in single payload: 12KB */
#endif
    0x00, 0x60, 0xE3, 0x16,             /* Device Clock */
    0x00,                               /* Framing Information - Ignored for uncompressed format*/
    0x00,                               /* Preferred payload format version */
    0x00,                               /* Minimum payload format version */
    0x00                                /* Maximum payload format version */
#endif
};


/* UVC Probe Control Setting - 1280*400@60fps*/
uint8_t const gl1280_400_60ProbeCtrl[CX3_APP_MAX_PROBE_SETTING] ={
    0x00, 0x00,                         /* bmHint : No fixed parameters */
    0x01,                               /* Use 1st Video format index */
    0x01,                               /* Use 2nd Video frame index */
	0x0A, 0x8B, 0x02, 0x00,             /* Desired frame interval in 100ns = (1/60)x10^7*/ 
    0x00, 0x00,                         /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                         /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                         /* Compression quality control */
    0x00, 0x00,                         /* Window size for average bit rate */
    0x00, 0x00,                         /* Internal video streaming i/f latency in ms */
#ifndef YUY2_COLOR_MODE
    0x00, 0x70, 0x17, 0x00,             /* Max video frame size in bytes: 400 x 1280 x 3*/
#else
	0x00, 0xa0, 0x0f, 0x00, 			/* Max video frame size in bytes: 400 x 1280 x 2*/
#endif


#ifdef CX3_UVC_1_0_SUPPORT
    0x00, 0x30, 0x00, 0x00              /* No. of bytes device can rx in single payload: 36KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
#ifdef BULK_TRANS_MODE
	0x00, 0x90, 0x00, 0x00, 			/* No. of bytes device can rx in single payload: 36KB */
#else
	0x00, 0x30, 0x00, 0x00, 			/* No. of bytes device can rx in single payload: 12KB */
#endif
    0x00, 0x60, 0xE3, 0x16,             /* Device Clock */
    0x00,                               /* Framing Information - Ignored for uncompressed format*/
    0x00,                               /* Preferred payload format version */
    0x00,                               /* Minimum payload format version */
    0x00                                /* Maximum payload format version */
#endif
};

/* UVC Probe Control Setting - 2560*800*/
uint8_t const gl2560_800ProbeCtrl[CX3_APP_MAX_PROBE_SETTING] =
{
    0x00, 0x00,                         /* bmHint : No fixed parameters */
    0x01,                               /* Use 1st Video format index */
    0x02,                               /* Use 2nd Video frame index */
    0x15, 0x16, 0x05, 0x00,             /* Desired frame interval in 100ns = (1/30)x10^7*/
    0x00, 0x00,                         /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                         /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                         /* Compression quality control */
    0x00, 0x00,                         /* Window size for average bit rate */
    0x00, 0x00,                         /* Internal video streaming i/f latency in ms */
#ifndef YUY2_COLOR_MODE
    0x00, 0xc0, 0x5d, 0x00,             /* Max video frame size in bytes: 800 x 2560 x 3*/
#else
	0x00, 0x80, 0x3e, 0x00, 			/* Max video frame size in bytes: 800 x 2560 x 2*/
#endif
#ifdef CX3_UVC_1_0_SUPPORT
    0x00, 0x90, 0x00, 0x00              /* No. of bytes device can rx in single payload: 36KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
#ifdef BULK_TRANS_MODE
	0x00, 0x90, 0x00, 0x00, 			/* No. of bytes device can rx in single payload: 36KB */
#else
	0x00, 0x30, 0x00, 0x00, 			/* No. of bytes device can rx in single payload: 12KB */
#endif
    0x00, 0x60, 0xE3, 0x16,             /* Device Clock */
    0x00,                               /* Framing Information - Ignored for uncompressed format*/
    0x00,                               /* Preferred payload format version */
    0x00,                               /* Minimum payload format version */
    0x00                                /* Maximum payload format version */
#endif
};


/* UVC Probe Control Setting - VGA @30fps (Super Speed)*/
uint8_t const glVga30ProbeCtrl[CX3_APP_MAX_PROBE_SETTING] = {
    0x00, 0x00,                         /* bmHint : No fixed parameters */
    0x01,                               /* Use 1st Video format index */
    0x04,                               /* Use 1st Video frame index */
    0x15, 0x16, 0x05, 0x00,             /* Desired frame interval in 100ns = (1/60)x10^7 */
    0x00, 0x00,                         /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                         /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                         /* Compression quality control */
    0x00, 0x00,                         /* Window size for average bit rate */
    0x00, 0x00,                         /* Internal video streaming i/f latency in ms */
    0x00, 0x60, 0x09, 0x00,             /* Max video frame size in bytes: 640 x 480 x 2*/
#ifdef CX3_UVC_1_0_SUPPORT
    0x00, 0x90, 0x00, 0x00              /* No. of bytes device can rx in single payload: 36KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
    0x00, 0x90, 0x00, 0x00,             /* No. of bytes device can rx in single payload: 36KB */
    0x00, 0x60, 0xE3, 0x16,             /* Device Clock */
    0x00,                               /* Framing Information - Ignored for uncompressed format*/
    0x00,                               /* Preferred payload format version */
    0x00,                               /* Minimum payload format version */
    0x00                                /* Maximum payload format version */
#endif
};


/* UVC Probe Control Setting - VGA @30fps (High Speed)*/
uint8_t const glVga30ProbeCtrl_HS[CX3_APP_MAX_PROBE_SETTING] = {
    0x00, 0x00,                         /* bmHint : No fixed parameters */
    0x01,                               /* Use 1st Video format index */
    0x01,                               /* Use 1st Video frame index */
    0x15, 0x16, 0x05, 0x00,             /* Desired frame interval in 100ns = (1/60)x10^7 */
    0x00, 0x00,                         /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                         /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                         /* Compression quality control */
    0x00, 0x00,                         /* Window size for average bit rate */
    0x00, 0x00,                         /* Internal video streaming i/f latency in ms */
    0x00, 0x60, 0x09, 0x00,             /* Max video frame size in bytes: 640 x 480 x 2*/
#ifdef CX3_UVC_1_0_SUPPORT
    0x00, 0x90, 0x00, 0x00              /* No. of bytes device can rx in single payload: 36KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
    0x00, 0x90, 0x00, 0x00,             /* No. of bytes device can rx in single payload: 36KB */
    0x00, 0x60, 0xE3, 0x16,             /* Device Clock */
    0x00,                               /* Framing Information - Ignored for uncompressed format*/
    0x00,                               /* Preferred payload format version */
    0x00,                               /* Minimum payload format version */
    0x00                                /* Maximum payload format version */
#endif
};

/* UVC Probe Control Setting - VGA @60fps (High Speed) */
uint8_t const glVga60ProbeCtrl[CX3_APP_MAX_PROBE_SETTING] = {
    0x00, 0x00,                         /* bmHint : No fixed parameters */
    0x01,                               /* Use 1st Video format index */
    0x02,                               /* Use 2nd Video frame index */
    0x0A, 0x8B, 0x02, 0x00,             /* Desired frame interval in 100ns = (1/60)x10^7 */
    0x00, 0x00,                         /* Key frame rate in key frame/video frame units */
    0x00, 0x00,                         /* PFrame rate in PFrame / key frame units */
    0x00, 0x00,                         /* Compression quality control */
    0x00, 0x00,                         /* Window size for average bit rate */
    0x00, 0x00,                         /* Internal video streaming i/f latency in ms */
    0x00, 0x60, 0x09, 0x00,             /* Max video frame size in bytes: 640 x 480 x 2*/
#ifdef CX3_UVC_1_0_SUPPORT
    0x00, 0x90, 0x00, 0x00              /* No. of bytes device can rx in single payload: 36KB */
#else
    /* UVC 1.1 Probe Control has additional fields from UVC 1.0 */
    0x00, 0x90, 0x00, 0x00,             /* No. of bytes device can rx in single payload: 36KB */
    0x00, 0x60, 0xE3, 0x16,             /* Device Clock */
    0x00,                               /* Framing Information - Ignored for uncompressed format*/
    0x00,                               /* Preferred payload format version */
    0x00,                               /* Minimum payload format version */
    0x00                                /* Maximum payload format version */
#endif
};


/* Configuration parameters for 1280*480 @60FPS for the ap1302 sensor */
CyU3PMipicsiCfg_t cfgUvc1280_400_60NoMclk =
{
#ifndef YUY2_COLOR_MODE
    CY_U3P_CSI_DF_RGB888,           /* dataFormat   */
#else
    CY_U3P_CSI_DF_YUV422_8_1,             /* dataFormat   */
#endif
    2,                                  /* numDataLanes */
    1,                                  /* pllPrd       */
    62,                                 /* pllFbd       */
    CY_U3P_CSI_PLL_FRS_500_1000M,       /* pllFrs      */
    CY_U3P_CSI_PLL_CLK_DIV_8,           /* csiRxClkDiv  */
    CY_U3P_CSI_PLL_CLK_DIV_8,           /* parClkDiv    */
    0x00,                               /* mclkCtl      */
    CY_U3P_CSI_PLL_CLK_DIV_8,           /* mClkRefDiv   */
    1280,                               /* hResolution  */
    0x01                                /* fifoDelay    */
};


/* Configuration parameters for 1280*480 @30FPS for the OV5640 sensor */
CyU3PMipicsiCfg_t cfgUvc2560_800NoMclk =
{
#ifndef YUY2_COLOR_MODE
    CY_U3P_CSI_DF_RGB888,           /* dataFormat   */
#else
    CY_U3P_CSI_DF_YUV422_8_1,             /* dataFormat   */
#endif
    2,                                  /* uint8_t numDataLanes */ 
#ifndef YUY2_COLOR_MODE
    1,                                  /* uint8_t pllPrd */
    62,                                 /* uint16_t pllFbd */
    CY_U3P_CSI_PLL_FRS_500_1000M,       /* CyU3PMipicsiPllClkFrs_t pllFrs */
    CY_U3P_CSI_PLL_CLK_DIV_8,           /* CyU3PMipicsiPllClkDiv_t csiRxClkDiv */
    CY_U3P_CSI_PLL_CLK_DIV_8,           /* CyU3PMipicsiPllClkDiv_t parClkDiv */
#else
    2,                                  /* uint8_t pllPrd */
    119,                                 /* uint16_t pllFbd */
    CY_U3P_CSI_PLL_FRS_250_500M,       /* CyU3PMipicsiPllClkFrs_t pllFrs */
    CY_U3P_CSI_PLL_CLK_DIV_4,           /* CyU3PMipicsiPllClkDiv_t csiRxClkDiv */
    CY_U3P_CSI_PLL_CLK_DIV_4,           /* CyU3PMipicsiPllClkDiv_t parClkDiv */
#endif
    0,                                  /* uint16_t mClkCtl */
    CY_U3P_CSI_PLL_CLK_DIV_2,           /* CyU3PMipicsiPllClkDiv_t mClkRefDiv */
    2560,                               /* uint16_t hResolution */ 
#ifndef YUY2_COLOR_MODE
    6                                   /* uint16_t fifoDelay */
#else
	0									/* uint16_t fifoDelay */
#endif
};


/* Configuration parameters for VGA for the OV5640 sensor */
CyU3PMipicsiCfg_t cfgUvcVgaNoMclk ={
    CY_U3P_CSI_DF_YUV422_8_1,       /* dataFormat   */
    4,                            /* numDataLanes */
    0x1,                          /* pllPrd       */
    90,                           /* pllFbd       */
    CY_U3P_CSI_PLL_FRS_125_250M,   /* pllFrs      */
    CY_U3P_CSI_PLL_CLK_DIV_2,     /* csiRxClkDiv  */
    CY_U3P_CSI_PLL_CLK_DIV_8,     /* parClkDiv    */
    0x00,                         /* mclkCtl      */
    CY_U3P_CSI_PLL_CLK_DIV_8,     /* mClkRefDiv   */
    640,                          /* hResolution  */
    0x01                          /* fifoDelay    */
};

/* [ ] */


