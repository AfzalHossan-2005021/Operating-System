# Bash Scripting

This project includes a shell script (`2005021.sh`) that can be executed using a Makefile. The following instructions will guide you through setting up and running the script.

## Requirements

Ensure that you have the following files in the same directory:
1. `Makefile`
2. `2005021.sh`
3. `test-cases.zip`

You’ll also need a terminal environment like **Ubuntu** to run the commands below.

## Setup and Execution

1. Open a terminal.
2. Navigate to the directory containing `Makefile`, `2005021.sh`, and `test-cases.zip`.

    ```bash
    cd /path/to/your/directory
    ```
3. Run the shell script by typing the following command:
    ```bash
    make run-script
    ```
4. Press Enter to execute.

## Notes

- The Makefile should include a target for run-script that initiates the 2005021.sh script.
- Ensure that all dependencies and permissions are correctly set to allow the script to execute successfully.

## Troubleshooting

If you encounter any issues:
- Verify that all files (`Makefile`, `2005021.sh`, `test-cases.zip`) are in the same directory.
- Ensure you have the necessary permissions to execute shell scripts. You can grant permissions with:

  ```bash
  chmod +x 2005021.sh
  ```