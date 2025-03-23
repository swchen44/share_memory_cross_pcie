# PCIE Slave to Host Data Transfer System

This project demonstrates a system for transferring data from a PCIE slave device to a PCIE host using a shared DRAM memory buffer. The system utilizes interrupts for communication between the slave and the host.

## Overview

The system consists of the following components:

*   **emi writer (emi\_writer.c):** Writes data to the DRAM memory buffer and notifies the emi reader via PCIE MSI interrupt.
*   **emi reader (emi\_reader.c):** Reads data from the DRAM memory buffer, updates the read pointer, and notifies the emi writer via CCIF interrupt.
*   **DRAM Memory Buffer:** A shared memory region accessible by both the emi writer and the emi reader.

## Design

The design of the system is described in detail in the [design.md](design.md) file.

## Flowcharts and Sequence Diagrams

The system's flowchart and sequence diagrams are available in the following files:

*   [flowchart.plantuml](flowchart.plantuml)
*   [sequence\_diagram.plantuml](sequence_diagram.plantuml)
*   [flowchart.mermaid](flowchart.mermaid)
*   [sequence\_diagram.mermaid](sequence_diagram.mermaid)

## Building the Code

To build the code, use the following command:

```bash
make
```

## Running the Code

To run the code, use the following command:

```bash
make run
```

## Testing the Code

To test the code, use the following command:

```bash
make test
```

**Note:** You will need to create a `test.c` file with gtest tests to run this command.

## License

This project is licensed under the BSD 2-Clause License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements

*   This project was inspired by the need for efficient data transfer between PCIE devices.

## Author

Your Name or Organization
