/*
Copyright (c) 2025, Your Name or Organization

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1.  Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
2.  Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

// emi_writer.c - PCIE Slave (EMI Writer) Module
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "emi_writer.h"

// Define the unit size for data transfer (default 4096 bytes)
#ifndef EMI_WRITER_UNIT_SIZE
#define EMI_WRITER_UNIT_SIZE 4096
#endif

// Global variable for the DRAM buffer
emi_writer_emi_writer_dram_buffer_t emi_writer_shared_dram;

// Function to initialize the DRAM buffer
void emi_writer_init(uint8_t* buffer, size_t buffer_size) {
    emi_writer_shared_dram.buffer = buffer;
    emi_writer_shared_dram.buffer_size = buffer_size;
    emi_writer_shared_dram.write_ptr = 0;
    emi_writer_shared_dram.read_ptr = 0;
    emi_writer_shared_dram.data_available = false;
}

// Function to write data to the DRAM buffer
size_t emi_writer_write(const uint8_t* data, size_t data_len) {
    size_t bytes_written = 0;

    // Check if the buffer is valid
    if (emi_writer_shared_dram.buffer == NULL || emi_writer_shared_dram.buffer_size == 0) {
        fprintf(stderr, "EMI Writer: DRAM buffer is not initialized!\n");
        return 0;
    }

    // Check if there is enough space in the buffer
    while (bytes_written < data_len) {
        size_t available_space = 0;
        if (emi_writer_shared_dram.write_ptr >= emi_writer_shared_dram.read_ptr) {
            available_space = emi_writer_shared_dram.buffer_size - emi_writer_shared_dram.write_ptr + emi_writer_shared_dram.read_ptr;
        } else {
            available_space = emi_writer_shared_dram.read_ptr - emi_writer_shared_dram.write_ptr;
        }

        if (available_space <= 1) {
            fprintf(stderr, "EMI Writer: DRAM buffer is full!\n");
            break;
        }

        size_t write_size = (data_len - bytes_written) > (available_space - 1) ? (available_space - 1) : (data_len - bytes_written);

        // Write data to the buffer
        for (size_t i = 0; i < write_size; ++i) {
            emi_writer_shared_dram.buffer[emi_writer_shared_dram.write_ptr] = data[bytes_written + i];
            emi_writer_shared_dram.write_ptr = (emi_writer_shared_dram.write_ptr + 1) % emi_writer_shared_dram.buffer_size;
        }

        bytes_written += write_size;
    }

    // Set the data available flag
    emi_writer_shared_dram.data_available = true;

    return bytes_written;
}

// Function to simulate sending an MSI interrupt to the host
void emi_writer_send_msi_interrupt(void) {
    printf("EMI Writer: Sending MSI interrupt to the host...\n");
    // In a real system, this would involve writing to a specific register
    // to trigger the MSI interrupt.
}

// Function to simulate receiving a CCIF interrupt from the host
void emi_writer_receive_ccif_interrupt(void) {
    printf("EMI Writer: Receiving CCIF interrupt from the host...\n");
    // In a real system, this would involve reading a specific register
    // to detect the CCIF interrupt.
}

// Function to check if there is more data to send
bool emi_writer_has_more_data(void) {
    // This is a placeholder. In a real system, this would involve
    // checking a data source to see if there is more data available.
    return true;
}

#ifdef EMI_WRITER_TEST
int main() {
    // Example usage
    uint8_t buffer[4096]; // Example buffer
    emi_writer_init(buffer, sizeof(buffer));

    uint8_t data[1024];
    for (int i = 0; i < 1024; ++i) {
        data[i] = i % 256;
    }

    size_t bytes_written = emi_writer_write(data, sizeof(data));
    printf("EMI Writer: Wrote %zu bytes to DRAM buffer.\n", bytes_written);

    emi_writer_send_msi_interrupt();
    emi_writer_receive_ccif_interrupt();

    return 0;
}
#endif
