#ifndef DRAM_BUFFER_H
#define DRAM_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

// Define the size of the DRAM buffer
#define DRAM_BUFFER_SIZE 1024

// Define the structure for the DRAM buffer
typedef struct {
    uint8_t buffer[DRAM_BUFFER_SIZE];
    uint32_t write_ptr;
    uint32_t read_ptr;
    bool data_available;
} dram_buffer_t;

#endif
