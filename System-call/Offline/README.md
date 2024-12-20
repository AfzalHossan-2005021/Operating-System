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

   Navigate to the `xv6-riscv` directory and apply the provided patch file using the following command:
   ```bash
   cd xv6-riscv
   git clean -fdx
   git reset --hard
   git apply --whitespace=fix ../System-call/Offline/2005021.patch
   ```  

4. **Emulate xv6**:
   Start the emulator:
   ```bash
   make qemu
   ```

5. **Test**:
   To rest, use the following commands and outputs:
   ```
   trace 15 grep hello README
   ```
   Output:  
   pid: 3, syscall: open, args: (README, 0), return: 3  
   
   ```
   grep hello README
   ```
   Output:  
  
   ```
   trace 3 grep hello README
   ```
   Output:  
  
   ```
   trace 5 grep hello README
   ```
   Output:  
   pid: 6, syscall: read, args: (3, 0x0000000000001010, 1023), return: 1023  
   pid: 6, syscall: read, args: (3, 0x000000000000104e, 961), return: 961  
   pid: 6, syscall: read, args: (3, 0x0000000000001037, 984), return: 321  
   pid: 6, syscall: read, args: (3, 0x0000000000001010, 1023), return: 0  
  
   ```
   trace 21 grep hello README
   ```
   Output:  
   pid: 7, syscall: close, args: (3), return: 0

   ```
   trace 7 echo hello
   ```
   Output:  
   pid: 8, syscall: exec, args: (echo, 0x0000000000003fa0), return: 2
   hello
     
   ```
   load 2 2048
   ```
   Output:
   Parent going to sleep.  
   Child process created.  
   Child allocated 2048 byte.  
   Child going to sleep.  
   Child process created.  
   Child allocated 2048 byte.  
   Child going to sleep.  
   Parent wake up.  
   Current system information:  
   Processes: 3/64  
   RAM : 0.245760/128 (in MB)  

   
6. **Terminate the Emulator**:
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
  
