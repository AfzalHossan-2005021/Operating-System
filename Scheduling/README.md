# Repository Setup Instructions

This repository includes a submodule and a patch file that must be applied after cloning. Follow the steps below to set up the repository correctly.

## Steps to Clone and Set Up

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/AfzalHossan-2005021/Operating-System.git
   ```

2. **Initialize and Update Submodules**:
   Navigate to the cloned repository's directory and initialize the submodules:
   ```bash
   cd Operating-System
   git submodule update --init --recursive
   ```

3. **Apply the Patch File**:
   Navigate to the `xv6-riscv` directory and apply the singlecpu patch file using the following command:
   ```bash
   cd xv6-riscv
   git apply --whitespace=fix ../Scheduling/2005021_singlecpu.patch
   ```

   or

   Navigate to the `xv6-riscv` directory and apply the multicpu patch file using the following command:
   ```bash
   cd xv6-riscv
   git apply --whitespace=fix ../Scheduling/2005021_multicpu.patch
   ```

4. **Emulate xv6**:
   Start the emulator:
   ```bash
   make qemu
   ```

5. **Show log**:
   To show log, use the following command:
   ```
   showlog
   ```

6. **Hide log**:
   To hide log, use the following command:
   ```
   hidelog
   ```

7. **Test**:
   To test, use the following command:
   ```
   dummyproc 10 1000000000 &; dummyproc 10 1000000000 &; testprocinfo
   ```

8. **Terminate the Emulator**:
   To terminate the emulator, use the following keyboard sequence:
   ```
   ctrl + a
   x
   ```

## Notes

- If you encounter issues while applying the patch, verify the patch file's location and ensure it is compatible with the current state of the repository.
- Use `git status` to confirm that the patch was successfully applied.

## Additional Commands

- To check the status of submodules:
  ```bash
  git submodule status
  ```
- To update submodules to the latest commit:
  ```bash
  git submodule update --remote
  ```
