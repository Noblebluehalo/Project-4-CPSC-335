Project 4 
CPSC 335- Fall 2024

This project contains three C++ programs:

Algo1.cpp – Target Terms / Substring Search

Algo2.cpp – Run-Length Encoding

Algo3.cpp – Merge k Sorted Arrays (Min-Heap)

This README explains how to compile and execute each program.

System Requirements

You will need:

A C++ compiler such as g++

A terminal or the VS Code terminal

Input files:

in2a.txt for Algorithm 1 (if used)

in2c.txt for Algorithm 3

Important: All .txt files must be placed in the same folder as the .cpp files and the compiled executable.

How to Compile the Programs

Open a terminal inside the folder containing the .cpp files and type:

g++ Algo1.cpp -o algo1
g++ Algo2.cpp -o algo2
g++ Algo3.cpp -o algo3

This will generate executables:
algo1, algo2, algo3 (or algo1.exe on Windows)

How to Run Algorithm 1 (Substring Search)

Run:

./algo1

The program will prompt you for:

The concatenated string A

The number of words n

One line containing all n words separated by spaces

Example input:

Enter the concatenated string A: thismetoaklandrialtofullertonmarcolongchinofresnovallejoclovissimithound
Enter number of words to search for: 4
Enter the words on one line: marco clovis rialto oakland

Example output:

Output_order = [7, 14, 29, 56]
Output_array = [oakland, rialto, marco, clovis]

How to Run Algorithm 2 (Run-Length Encoding)

Run:

./algo2

Then enter any string to encode.

Example:

Enter the string to encode: heloooooooo there

Output:

Encoded string: hel8o there

How to Run Algorithm 3 (Merge k Sorted Arrays)

Algo3.cpp automatically reads input from the file in2c.txt.

Important:
Place in2c.txt in the same folder as Algo3.cpp and the executable.

Run:

./algo3

The program will:

Load and parse all array groups from in2c.txt

Merge each group using a custom min-heap

Print the merged sorted arrays

Example output:

Merged Array_1 = [-10, -1, 0, 2, 2, 4, 5, 6, 9, 12, 20, 21, 81, 121, 150]
Merged Array_2 = [-3, 0, 3, 7, 8, 9, 10, 11, 11, 12, 17, 18, 19, 21, 29, 29, 81, 88, 121, 131]
Merged Array_3 = [-4, -2, 0, 2, 4, 5, 6, 6, 7, 10, 10, 12, 14, 15, 20, 24, 25]
