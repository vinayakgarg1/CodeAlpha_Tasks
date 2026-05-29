# CodeAlpha_CGPA_CALCULATOR

A C++ program that calculates a student's Semester GPA and overall Cumulative GPA (CGPA) based on a 10-point grading scale (S, A, B, C, D, E, F). 

## Features
* Calculates total credits and grade points for a semester.
* Computes current semester GPA.
* Accounts for previous semester credits and CGPA to calculate an updated overall CGPA.
* Includes input validation to handle errors (e.g., invalid grades, negative credits, or string inputs where numbers are expected).

## How to Run
1. Compile the code using a C++ compiler:
   `g++ cgpa_calculator.cpp -o cgpa_calc`
2. Run the executable:
   * Windows: `cgpa_calc.exe`
   * Linux/Mac: `./cgpa_calc`