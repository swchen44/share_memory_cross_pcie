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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "emi_writer.h"
#include "emi_reader.h"

#define MAIN_DRAM_BUFFER_SIZE 4096
uint8_t main_main_shared_buffer[MAIN_DRAM_BUFFER_SIZE];

int main() {
    // Initialize the EMI writer and reader with the shared buffer
    emi_writer_init(main_main_shared_buffer, MAIN_DRAM_BUFFER_SIZE);
    emi_reader_init(main_main_shared_buffer, MAIN_DRAM_BUFFER_SIZE);

    // Example data to write
    uint8_t data_to_write[1024];
    for (int i = 0; i < 1024; ++i) {
        data_to_write[i] = i % 256;
    }

    // Write data using EMI writer
    size_t bytes_written = emi_writer_write(data_to_write, sizeof(data_to_write));
    printf("Main: EMI Writer wrote %zu bytes to the buffer.\n", bytes_written);
    emi_writer_send_msi_interrupt(); // Simulate interrupt

    // Read data using EMI reader
    uint8_t data_read[1024];
    size_t bytes_read = emi_reader_read(data_read, sizeof(data_read));
    printf("Main: EMI Reader read %zu bytes from the buffer.\n", bytes_read);
    emi_reader_send_ccif_interrupt(); // Simulate interrupt

    // Basic check: Did we read what we wrote?
    if (bytes_written == bytes_read) {
        bool match = true;
        for (size_t i = 0; i < bytes_read; ++i) {
            if (data_to_write[i] != data_read[i]) {
                match = false;
                break;
            }
        }
        if (match) {
            printf("Main: Data read matches data written!\n");
        } else {
            printf("Main: Data mismatch between written and read data!\n");
        }
    } else {
        printf("Main: Bytes written and bytes read do not match!\n");
    }

    return 0;
}
