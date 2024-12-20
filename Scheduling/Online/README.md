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
   git clean -fdx
   git reset --hard
   git apply --whitespace=fix ../Scheduling/Online/2005021.patch
   ```  
   
4. **Emulate xv6**:
   Start the emulator:
   ```bash
   make qemu
   ```

7. **Test**:
   To test, use the following command (quickly):
   ```
   testloop 120 &;
   testloop 110 &;
   testloop 100 &;
   ls
   ```  
   Output:  
   Process 5: Starting 120 iterations at time 46  
   Process 8: Starting 110 iterations at time 73  
   Process 11: Starting 100 iterations at time 105  
   .              1 1 1024  
   ..             1 1 1024  
   README         2 2 2305  
   cat            2 3 35144  
   echo           2 4 33992  
   forktest       2 5 16232  
   grep           2 6 38520  
   init           2 7 34488  
   kill           2 8 33952  
   ln             2 9 33776  
   ls             2 10 37080  
   mkdir          2 11 34016  
   rm             2 12 33992  
   sh             2 13 56448  
   stressfs       2 14 34880  
   testloop       2 15 34776  
   usertests      2 16 182992  
   grind          2 17 49872  
   wc             2 18 36096  
   zombie         2 19 33360  
   console        3 20 0  
   Process 11: Finished at time 138  
   Process 8: Finished at time 144  
   Process 5: Finished at time 157  

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
