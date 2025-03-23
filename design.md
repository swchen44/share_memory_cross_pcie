# PCIE Slave to Host Data Transfer System Design

## 1. Introduction

This document describes the design of a system for transferring data from a PCIE slave device to a PCIE host using a shared DRAM memory buffer. The system utilizes interrupts for communication between the slave and the host.

## 2. Functional Overview

The system consists of the following components:

*   **emi writer (emi\_writer):** Writes data to the DRAM memory buffer and notifies the emi reader via PCIE MSI interrupt.
*   **emi reader (emi\_reader):** Reads data from the DRAM memory buffer, updates the read pointer, and notifies the emi writer via CCIF interrupt.
*   **DRAM Memory Buffer:** A shared memory region accessible by both the emi writer and the emi reader.

## 3. Detailed Design

### 3.1. DRAM Memory Buffer

The DRAM memory buffer is a circular buffer with a fixed size. It stores the data transferred from the PCIE slave to the PCIE host. The buffer is managed using two pointers:

*   **Write Pointer:** Indicates the location where the emi writer will write the next data.
*   **Read Pointer:** Indicates the location where the emi reader will read the next data.

### 3.2. Data Transfer Process

1.  The emi writer (implemented in `emi_writer.c`) writes data to the DRAM memory buffer at the location indicated by the `emi_writer_write_pointer`.
2.  The emi writer updates the `emi_writer_write_pointer` to the next available location in the buffer.
3.  The emi writer triggers a PCIE MSI interrupt to notify the emi reader that new data is available.
4.  The emi reader (implemented in `emi_reader.c`) receives the MSI interrupt and reads data from the DRAM memory buffer at the location indicated by the `emi_reader_read_pointer`.
5.  The emi reader updates the `emi_reader_read_pointer` to the next location to be read.
6.  The emi reader checks if there is more data available in the buffer by comparing `emi_reader_read_pointer` and `emi_writer_write_pointer`.
7.  The emi reader triggers a CCIF interrupt to notify the emi writer that it has read the data.
8.  If the emi writer has more data to send, it repeats steps 1-3.

### 3.3. Interrupts

*   **PCIE MSI Interrupt:** Used by the emi writer to notify the emi reader that new data is available in the DRAM memory buffer.
*   **CCIF Interrupt:** Used by the emi reader to notify the emi writer that it has read data from the DRAM memory buffer.

## 4. Error Handling

*   **Buffer Overflow:** The emi writer should check if the buffer is full before writing data. If the buffer is full, the emi writer should wait until the emi reader has read some data and freed up space in the buffer.
*   **Buffer Underflow:** The emi reader should check if the buffer is empty before reading data. If the buffer is empty, the emi reader should wait until the emi writer has written new data to the buffer.

## 5. Future Considerations

*   Implement a mechanism for dynamic buffer resizing.
*   Add support for multiple data channels.
*   Implement a more sophisticated error handling mechanism.
