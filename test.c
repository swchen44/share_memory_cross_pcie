#include "gtest/gtest.h"
#include "dram_buffer.h"
#include "emi_writer.c"
#include "emi_reader.c"

TEST(DRAMBufferTest, WriteAndReadData) {
    emi_writer_init_dram_buffer();

    uint8_t data_to_write = 10;
    ASSERT_TRUE(emi_writer_write_data_to_dram(data_to_write));

    uint8_t data_read;
    ASSERT_TRUE(emi_reader_read_data_from_dram(&data_read));

    ASSERT_EQ(data_to_write, data_read);
}

TEST(DRAMBufferTest, BufferFull) {
    emi_writer_init_dram_buffer();

    // Set read_ptr to 0
    emi_writer_shared_dram.read_ptr = 0;
    emi_writer_shared_dram.write_ptr = DRAM_BUFFER_SIZE - 1;

    // Try to write one more byte, it should fail
    uint8_t data_to_write = 10;
    ASSERT_FALSE(emi_writer_write_data_to_dram(data_to_write));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
