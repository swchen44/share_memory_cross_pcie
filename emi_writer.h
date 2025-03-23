/*
Copyright (c) 2025, Your Name or Organization

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef EMI_WRITER_H
#define EMI_WRITER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Structure to hold the DRAM buffer and related information
typedef struct {
    uint8_t* buffer;
    size_t buffer_size;
    size_t write_ptr;
    size_t read_ptr;
    bool data_available;
} emi_writer_emi_writer_dram_buffer_t;

// Function to initialize the DRAM buffer
void emi_writer_init(uint8_t* buffer, size_t buffer_size);

// Function to write data to the DRAM buffer
size_t emi_writer_write(const uint8_t* data, size_t data_len);

// Function to simulate sending an MSI interrupt to the host
void emi_writer_send_msi_interrupt(void);

// Function to simulate receiving a CCIF interrupt from the host
void emi_writer_receive_ccif_interrupt(void);

// Function to check if there is more data to send
bool emi_writer_has_more_data(void);

#ifdef __cplusplus
}
#endif

#endif // EMI_WRITER_H
