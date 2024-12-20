# Repository Setup Instructions

This repository includes a submodule and a patch file that must be applied after cloning. Follow the steps below to set up the repository correctly.

## Steps to Clone and Set Up

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/AfzalHossan-2005021/Operating-System.git
   ```

2. **Navigate to directory**:
   Navigate to the `Online` directory:
   ```bash
   cd Operating-System/Inter-process-Communication/Online
   ```  

3. **Compile**:
   Compile using g++:
   ```bash
   g++ 2005021.cpp -o 2005021 -lpthread
   ```

4. **Test**:
   To rest, use the following commands and outputs:
   ```
   ./2005021
   ```
   Output:  
   Enter the number of iterations: 
   
   ```
   10
   ```
   Output:  
   prq  
   qqpprr  
   ppprrrqqq  
   qqqqrrrrpppp  
   rrrrrqqqqqppppp  
   rrrrrrppppppqqqqqq  
   pppppppqqqqqqqrrrrrrr  
   ppppppppqqqqqqqqrrrrrrrr  
   qqqqqqqqqppppppppprrrrrrrrr  
   qqqqqqqqqqpppppppppprrrrrrrrrr  
