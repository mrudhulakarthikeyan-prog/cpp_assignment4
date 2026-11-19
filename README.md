# DSA01 Assignment 4 – Designing Reusable Class Hierarchies

**Environment:** Visual Studio Code / Visual Studio terminal with MSYS2 UCRT64 GCC, C++17.

## Compile and run (PowerShell or MSYS2 UCRT64 terminal)
Open the project folder in VS Code. Ensure `C:\msys64\ucrt64\bin` is on PATH and `g++ --version` works.

Compile one task: `g++ -std=c++17 -Wall -Wextra -pedantic Task01_Class_Design/main.cpp -o Task01.exe`
Run: `./Task01.exe` (PowerShell: `./Task01.exe`). Repeat with the relevant source path and executable name.

Run all tasks on Windows PowerShell: `./run_all.bat`. The script compiles each main.cpp and stores console output in `Outputs`.

## Tasks
- Task01: common abstract Staff base, encapsulation and virtual pay().
- Task02: virtual Person base, multiple inheritance, research scholar and diamond demonstration.
- Task03: initializer lists, Address/Course member objects, construction/destruction traces and completed TODO 1 program.
- Task04: virtual dispatch, virtual destructor, unique_ptr ownership, slicing and non-virtual dispatch demonstration.
- Task05: direct/pointer/reference/dynamic object access, this pointer, chaining and pointer-array maximum search.
- Task06: abstract Vehicle hierarchy, polymorphic fleet, renting/returning/late fee and ElectricBus extension.

## Prediction-first requirement
Before executing the two prediction programs in Tasks 2–4, fill in `PREDICTIONS_BEFORE_RUN.md` using the question paper. Then run the corresponding program and compare. Expected outputs are in `Expected_Outputs.md`; they are provided as a verification reference, not as a substitute for your own pre-run prediction.

## AddressSanitizer (Task 4)
`g++ -std=c++17 -Wall -Wextra -pedantic -fsanitize=address -fno-omit-frame-pointer Task04_Polymorphism/main.cpp -o Task04_asan.exe`
Run `./Task04_asan.exe`. This repaired implementation should not report a leak. The original defective snippet is discussed in `Task04_Polymorphism/DEFECT_ANALYSIS.md`; intentionally executing `delete` through a non-virtual base destructor is undefined behaviour and is not included as a routine run.

## GitHub requirement
Create `DSA01-<RegisterNumber>-Assignment4`, add your name/register number and actual compiler version below, and commit each task separately after execution and screenshot capture. Do not claim a commit or screenshot until you have actually made it.

**Student:** ____________________  
**Register number:** ____________________  
**Compiler/version actually used:** ____________________  
**GitHub repository URL:** ____________________
