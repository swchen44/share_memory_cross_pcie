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

#include "dram_buffer.h"

// Global variable for the DRAM buffer
dram_buffer_t emi_writer_shared_dram;

// Function to initialize the DRAM buffer
void emi_writer_init_dram_buffer() {
    emi_writer_shared_dram.write_ptr = 0;
    emi_writer_shared_dram.read_ptr = 0;
    emi_writer_shared_dram.data_available = false;
}

// Function to write data to the DRAM buffer
bool emi_writer_write_data_to_dram(uint8_t data) {
    // Check if the buffer is full
    if ((emi_writer_shared_dram.write_ptr + 1) % DRAM_BUFFER_SIZE == emi_writer_shared_dram.read_ptr) {
        fprintf(stderr, "DRAM buffer is full!\n");
        return false;
    }

    // Write data to the buffer
    emi_writer_shared_dram.buffer[emi_writer_shared_dram.write_ptr] = data;

    // Update the write pointer
    emi_writer_shared_dram.write_ptr = (emi_writer_shared_dram.write_ptr + 1) % DRAM_BUFFER_SIZE;

    // Set the data available flag
    emi_writer_shared_dram.data_available = true;

    return true;
}

// Function to simulate sending an MSI interrupt to the host
void send_msi_interrupt() {
    printf("Sending MSI interrupt to the host...\n");
    // In a real system, this would involve writing to a specific register
    // to trigger the MSI interrupt.
}

// Function to simulate receiving a CCIF interrupt from the host
void receive_ccif_interrupt() {
    printf("Receiving CCIF interrupt from the host...\n");
    // In a real system, this would involve reading a specific register
    // to detect the CCIF interrupt.
}

// Function to check if there is more data to send
bool has_more_data() {
    // This is a placeholder. In a real system, this would involve
    // checking a data source to see if there is more data available.
    return true;
}

int emi_writer_main() {
    // Initialize the DRAM buffer
    emi_writer_init_dram_buffer();

    // Simulate writing data to the DRAM buffer and sending interrupts
    for (int i = 0; i < 20; ++i) {
        // Check if there is more data to send
        if (!has_more_data()) {
            printf("No more data to send.\n");
            break;
        }

        // Write data to the DRAM buffer
        uint8_t data = i + 1; // Example data
        if (emi_writer_write_data_to_dram(data)) {
            printf("Wrote data %d to DRAM buffer.\n", data);

            // Send an MSI interrupt to the host
            send_msi_interrupt();

            // Simulate receiving a CCIF interrupt from the host
            receive_ccif_interrupt();
        } else {
            // Handle buffer full condition
            fprintf(stderr, "Failed to write data %d to DRAM buffer (buffer full).\n", data);
        }
    }

    return 0;
}
