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

// emi_reader.c - PCIE Host (EMI Reader) Module
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "dram_buffer.h"

// Declare the global variable for the DRAM buffer (shared with emi_writer.c)
extern dram_buffer_t emi_writer_shared_dram;

// Function to initialize the DRAM buffer (in case it's needed on the host side)
void emi_reader_init_dram_buffer() {
}

// Function to read data from the DRAM buffer
bool emi_reader_read_data_from_dram(uint8_t *data) {
    // Check if the buffer is empty
    if (emi_writer_shared_dram.read_ptr == emi_writer_shared_dram.write_ptr) {
        fprintf(stderr, "DRAM buffer is empty!\n");
        return false;
    }

    // Read data from the buffer
    *data = emi_writer_shared_dram.buffer[emi_writer_shared_dram.read_ptr];

    // Update the read pointer
    emi_writer_shared_dram.read_ptr = (emi_writer_shared_dram.read_ptr + 1) % DRAM_BUFFER_SIZE;

    // Check if the buffer is now empty
    if (emi_writer_shared_dram.read_ptr == emi_writer_shared_dram.write_ptr) {
        emi_writer_shared_dram.data_available = false;
    }

    return true;
}

// Function to simulate sending a CCIF interrupt to the slave
void emi_reader_send_ccif_interrupt() {
    printf("Sending CCIF interrupt to the slave...\n");
    // In a real system, this would involve writing to a specific register
    // to trigger the CCIF interrupt.
}

// Function to simulate receiving an MSI interrupt from the slave
void emi_reader_receive_msi_interrupt() {
    printf("Receiving MSI interrupt from the slave...\n");
    // In a real system, this would involve reading a specific register
    // to detect the CCIF interrupt.
}

int emi_reader_main() {
    // Initialize the DRAM buffer (optional, if the host also needs to write)
    emi_reader_init_dram_buffer();

    // Simulate receiving MSI interrupts and reading data from the DRAM buffer
    for (int i = 0; i < 10; ++i) {
        // Simulate receiving an MSI interrupt from the slave
        emi_reader_receive_msi_interrupt();

        // Read data from the DRAM buffer
        uint8_t data;
        if (emi_reader_read_data_from_dram(&data)) {
            printf("Read data %d from DRAM buffer.\n", data);

            // Send a CCIF interrupt to the slave
            emi_reader_send_ccif_interrupt();
        } else {
            // Handle buffer empty condition
            printf("Failed to read data from DRAM buffer (buffer empty).\n");
        }
    }

    return 0;
}
