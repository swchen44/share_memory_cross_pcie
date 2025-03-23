#include "gtest/gtest.h"
#include "emi_writer.h"
#include "emi_reader.h"

#define TEST_BUFFER_SIZE 4096

TEST(EMIWriterTest, WriteAndRead) {
    uint8_t test_test_buffer[TEST_BUFFER_SIZE];
    emi_writer_init(test_test_buffer, TEST_BUFFER_SIZE);
    emi_reader_init(test_test_buffer, TEST_BUFFER_SIZE);

    uint8_t write_data[] = {1, 2, 3, 4, 5};
    size_t write_len = sizeof(write_data);

    size_t written = emi_writer_write(write_data, write_len);
    ASSERT_EQ(written, write_len);

    uint8_t read_data[5];
    size_t read_len = sizeof(read_data);
    size_t total_read = 0;
    while (total_read < write_len) {
        size_t read = emi_reader_read(read_data + total_read, read_len - total_read);
        if (read == 0) break;
        total_read += read;
    }

    ASSERT_EQ(total_read, write_len);
    ASSERT_EQ(memcmp(write_data, read_data, write_len), 0);
}

TEST(EMIWriterTest, WriteMoreThanRead) {
    uint8_t test_test_buffer[TEST_BUFFER_SIZE];
    emi_writer_init(test_test_buffer, TEST_BUFFER_SIZE);
    emi_reader_init(test_test_buffer, TEST_BUFFER_SIZE);

    uint8_t write_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t write_len = sizeof(write_data);

    size_t written = emi_writer_write(write_data, write_len);
    ASSERT_EQ(written, write_len);

    uint8_t read_data[5];
    size_t read_len = sizeof(read_data);
    size_t read = emi_reader_read(read_data, read_len);

    ASSERT_EQ(read, read_len);
    ASSERT_EQ(memcmp(write_data, read_data, read_len), 0);
}

TEST(EMIWriterTest, BufferWrapAround) {
    uint8_t test_test_buffer[10];
    size_t buffer_size = sizeof(test_test_buffer);
    emi_writer_init(test_test_buffer, buffer_size);
    emi_reader_init(test_test_buffer, buffer_size);

    // Fill the buffer
    uint8_t initial_data[] = {1, 2, 3, 4, 5, 6, 7, 8};
    size_t initial_written = emi_writer_write(initial_data, sizeof(initial_data));
    uint8_t read_data[8];
    size_t initial_read = emi_reader_read(read_data, sizeof(read_data));

    // Write new data that wraps around
    uint8_t write_data[] = {9, 10, 11};
    emi_writer_write(write_data, sizeof(write_data));

    uint8_t read_data2[3];
    size_t wrap_read = emi_reader_read(read_data2, sizeof(read_data2));

    ASSERT_EQ(wrap_read, sizeof(read_data2));
    ASSERT_EQ(read_data2[0], 9);
    ASSERT_EQ(read_data2[1], 10);
    ASSERT_EQ(read_data2[2], 11);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
