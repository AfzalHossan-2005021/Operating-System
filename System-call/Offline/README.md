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
   Apply the provided patch file using the following command:
   ```bash
   cd xv6-riscv
   git clean -fdx
   git reset --hard
   git apply --whitespace=fix ../System-call/Offline/2005021.patch
   ```  

4. **Emulate xv6**:
   Navigate to the `xv6-riscv` directory and start the emulator:
   ```bash
   make qemu
   ```

5. **Terminate the Emulator**:
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
  
