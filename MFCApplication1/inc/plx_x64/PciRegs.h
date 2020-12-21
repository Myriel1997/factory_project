#ifndef __PCI_REGS_H
#define __PCI_REGS_H

/*******************************************************************************
 * Copyright 2013-2015 Avago Technologies
 * Copyright (c) 2009 to 2012 PLX Technology Inc.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directorY of this source tree, or the
 * BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/

/******************************************************************************
 *
 * File Name:
 *
 *      PciRegs.h
 *
 * Description:
 *
 *      This file defines the generic PCI Configuration Registers
 *
 * Revision:
 *
 *      05-01-13 : PLX SDK v7.10
 *
 ******************************************************************************/


// PCI Extended Capability IDs
#define CAP_ID_NULL                            0x00
#define CAP_ID_POWER_MAN                       0x01
#define CAP_ID_AGP                             0x02
#define CAP_ID_VPD                             0x03
#define CAP_ID_SLOT_ID                         0x04
#define CAP_ID_MSI                             0x05
#define CAP_ID_HOT_SWAP                        0x06
#define CAP_ID_PCIX                            0x07
#define CAP_ID_HYPER_TRANSPORT                 0x08
#define CAP_ID_VENDOR_SPECIFIC                 0x09
#define CAP_ID_DEBUG_PORT                      0x0A
#define CAP_ID_RESOURCE_CTRL                   0x0B
#define CAP_ID_HOT_PLUG                        0x0C
#define CAP_ID_BRIDGE_SUB_ID                   0x0D
#define CAP_ID_AGP_8X                          0x0E
#define CAP_ID_SECURE_DEVICE                   0x0F
#define CAP_ID_PCI_EXPRESS                     0x10
#define CAP_ID_MSI_X                           0x11
#define CAP_ID_SATA                            0x12
#define CAP_ID_ADV_FEATURES                    0x13


// PCI Express Extended Capability IDs
#define PCIE_CAP_ID_NULL                       0x000        // Empty capability
#define PCIE_CAP_ID_ADV_ERROR_REPORTING        0x001        // Advanced Error Reporting (AER)
#define PCIE_CAP_ID_VIRTUAL_CHANNEL            0x002        // Virtual Channel (VC)
#define PCIE_CAP_ID_DEV_SERIAL_NUMBER          0x003        // Device Serial Number
#define PCIE_CAP_ID_POWER_BUDGETING            0x004        // Power Budgeting
#define PCIE_CAP_ID_RC_LINK_DECLARATION        0x005        // Root Complex Link Declaration
#define PCIE_CAP_ID_RC_INT_LINK_CONTROL        0x006        // Root Complex Internal Link Control
#define PCIE_CAP_ID_RC_EVENT_COLLECTOR         0x007        // Root Complex Event Collector Endpoint Association
#define PCIE_CAP_ID_MF_VIRTUAL_CHANNEL         0x008        // Multi-Function Virtual Channel (MFVC)
#define PCIE_CAP_ID_VC_WITH_MULTI_FN           0x009        // Virtual Channel with Multi-Function
#define PCIE_CAP_ID_RC_REG_BLOCK               0x00A        // Root Complex Register Block (RCRB)
#define PCIE_CAP_ID_VENDOR_SPECIFIC            0x00B        // Vendor-specific (VSEC)
#define PCIE_CAP_ID_CONFIG_ACCESS_CORR         0x00C        // Configuration Access Correlation
#define PCIE_CAP_ID_ACCESS_CTRL_SERVICES       0x00D        // Access Control Services (ACS)
#define PCIE_CAP_ID_ALT_ROUTE_ID_INTERPRET     0x00E        // Alternate Routing-ID Interpretation (ARI)
#define PCIE_CAP_ID_ADDR_TRANS_SERVICES        0x00F        // Address Translation Services (ATS)
#define PCIE_CAP_ID_SR_IOV                     0x010        // SR-IOV
#define PCIE_CAP_ID_MR_IOV                     0x011        // MR-IOV
#define PCIE_CAP_ID_MULTICAST                  0x012        // Multicast
#define PCIE_CAP_ID_PAGE_REQUEST               0x013        // Page request (for ATS)
#define PCIE_CAP_ID_AMD_RESERVED               0x014        // Reserved for AMD
#define PCIE_CAP_ID_RESIZABLE_BAR              0x015        // Resizable BAR
#define PCIE_CAP_ID_DYNAMIC_POWER_ALLOC        0x016        // Dynamic Power Allocation (DPA)
#define PCIE_CAP_ID_TLP_PROCESSING_HINT        0x017        // TLP Processing Hints (TPH)
#define PCIE_CAP_ID_LATENCY_TOLERANCE_REPORT   0x018        // Latency Tolerance Reporting (LTR)
#define PCIE_CAP_ID_SECONDARY_PCI_EXPRESS      0x019        // Secondary PCI Express
#define PCIE_CAP_ID_PROTOCOL_MULTIPLEX         0x01A        // Protocol Multiplexing (PMUX)
#define PCIE_CAP_ID_PROCESS_ADDR_SPACE_ID      0x01B        // Process Address Space ID (PASID)
#define PCIE_CAP_ID_LTWT_NOTIF_REQUESTER       0x01C        // Lightweight Notification Requester (LNR)
#define PCIE_CAP_ID_DS_PORT_CONTAINMENT        0x01D        // Downstream Port Containment (DPC)
#define PCIE_CAP_ID_L1_PM_SUBSTRATES           0x01E        // L1 Power Management Substrates (L1PM)
#define PCIE_CAP_ID_PRECISION_TIME_MEAS        0x01F        // Precision Time Measurement (PTM)
#define PCIE_CAP_ID_PCIE_OVER_M_PHY            0x020        // PCIe over M-PHY (M-PCIe)
#define PCIE_CAP_ID_FRS_QUEUEING               0x021        // FRS Queueing
#define PCIE_CAP_ID_READINESS_TIME_REPORTING   0x022        // Readiness Time Reporting


// Function codes for PCI BIOS operations
#define PCI_FUNC_ID                            0xb1
#define PCI_FUNC_BIOS_PRESENT                  0x01
#define PCI_FUNC_FIND_PCI_DEVICE               0x02
#define PCI_FUNC_FIND_PCI_CLASS_CODE           0x03
#define PCI_FUNC_GENERATE_SPECIAL_CYC          0x06
#define PCI_FUNC_READ_CONFIG_BYTE              0x08
#define PCI_FUNC_READ_CONFIG_WORD              0x09
#define PCI_FUNC_READ_CONFIG_DWORD             0x0a
#define PCI_FUNC_WRITE_CONFIG_BYTE             0x0b
#define PCI_FUNC_WRITE_CONFIG_WORD             0x0c
#define PCI_FUNC_WRITE_CONFIG_DWORD            0x0d
#define PCI_FUNC_GET_IRQ_ROUTING_OPTS          0x0e
#define PCI_FUNC_SET_PCI_HW_INT                0x0f



#endif
