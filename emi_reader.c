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

#include "emi_reader.h"
#include "emi_writer.h"

// Global variable for the DRAM buffer
extern emi_writer_emi_writer_dram_buffer_t emi_writer_shared_dram;

// Function to initialize the DRAM buffer
void emi_reader_init(uint8_t* buffer, size_t buffer_size) {
    emi_writer_shared_dram.buffer = buffer;
    emi_writer_shared_dram.buffer_size = buffer_size;
    emi_writer_shared_dram.write_ptr = 0;
    emi_writer_shared_dram.read_ptr = 0;
    emi_writer_shared_dram.data_available = false;
}

// Function to read data from the DRAM buffer
size_t emi_reader_read(uint8_t* data, size_t max_len) {
    size_t bytes_read = 0;

    // Check if the buffer is valid
    if (!emi_writer_shared_dram.buffer || emi_writer_shared_dram.buffer_size == 0) {
        fprintf(stderr, "EMI Reader: DRAM buffer is not initialized!\\n");
        return 0;
    }

    // Check if there is data available in the buffer
    while (bytes_read < max_len) {
        if (emi_writer_shared_dram.read_ptr == emi_writer_shared_dram.write_ptr && !emi_writer_shared_dram.data_available) {
            fprintf(stderr, "EMI Reader: DRAM buffer is empty!\\n");
            break;
        }

        // Read data from the buffer
	if(emi_writer_shared_dram.buffer && emi_writer_shared_dram.read_ptr < emi_writer_shared_dram.buffer_size) {
        data[bytes_read] = emi_writer_shared_dram.buffer[emi_writer_shared_dram.read_ptr];
        emi_writer_shared_dram.read_ptr = (emi_writer_shared_dram.read_ptr + 1) % emi_writer_shared_dram.buffer_size;
        bytes_read++;
	} else {
	    fprintf(stderr, "EMI Reader: Invalid read pointer!\\n");
	    break;
	}
    }

    // Check if the buffer is now empty
    if (emi_writer_shared_dram.read_ptr == emi_writer_shared_dram.write_ptr && !emi_writer_shared_dram.data_available) {
        emi_writer_shared_dram.data_available = false;
    } else {
        emi_writer_shared_dram.data_available = false;
    }

    return bytes_read;
}

// Function to simulate sending a CCIF interrupt to the slave
void emi_reader_send_ccif_interrupt(void) {
    printf("EMI Reader: Sending CCIF interrupt to the slave...\\n");
    // In a real system, this would involve writing to a specific register
    // to trigger the CCIF interrupt.
}

// Function to simulate receiving an MSI interrupt from the slave
void emi_reader_receive_msi_interrupt(void) {
    printf("EMI Reader: Receiving MSI interrupt from the slave...\\n");
    // In a real system, this would involve reading a specific register
    // to detect the CCIF interrupt.
}
#ifdef EMI_READER_TEST
int main() {
    // Example usage
    uint8_t buffer[4096]; // Example buffer
    emi_reader_init(buffer, sizeof(buffer));

    uint8_t data[1024];
    size_t bytes_read = emi_reader_read(data, sizeof(data));
    printf("EMI Reader: Read %zu bytes from DRAM buffer.\\n", bytes_read);

    emi_reader_send_ccif_interrupt();
    emi_reader_receive_msi_interrupt();

    return 0;
}
#endif
