Emily Bodenhamer
CS 471 Project 4
README

Purpose
----------
Code three different new meta-heristics, Particle Swarm Optimization (PSO), Firefly Algorithm (FA), and Harmony Search Algorithm (HS). Thirty experimentations were done on each algorithm to perform statistical analysis on the results obtained from the three algorithms. 

PSO is modeled based on the flocking and schooling patterns of birds and fish and was invented by Russell Eberhart and James Kennedy in 1995. FA is modeled after the social behavior of fireflies based on the flashing and attraction characteristcs of fireflies. It was invented by Yang in 2010. HS is based on the process of musicians when they improvise their instruments' pitch by searching for a perfect state of harmony. 
 
A population matrix are made up from pseudo random values based on specified bounds based on the 18 different functions. The fitness of individual vectors from the population are calculated and sent to the algorithms inorder to aquire a furher minimization.

The experimentation parameters for all three algorithms is a minimum of 500 iterations on both algorithms, a population size of 500 and dimensions of 30.

Parameters for PSO are: k, the dampening factor; range from 0.8 - 1.2
		       c1, value that goes towards the pBest (fitness of the vectors in the population; range from  0-2
		       c2, value that goes towards the pBest (the best fitness of the whole population); range from  0-2
		      
Parameters for FA are: alpha, constant; 0.5
		       beta min, constant; 0.2
		       gamma, light absorption coefficient; 0.001-100
		       beta, attractiveness of a firefly
		       r, distance from one firefly to another

Parameters for HS are: HMCR, harmony memory considering rate; 0.7-0.95
		       PAR, pitch adjusting rate; 0.1-0.5
		       BW, bandwidth; 0.2

Source Files
---------------
main.c: The main file to run the program. This file contains parameters that are used for all three algorithms, number of solutions, number of dimensions, number of iterations and function call counter. Files are created and opened, the three algorithms are then ran.

mt19937ar.h: header file for the MT19937 C source file
mt19937ar.c:  C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto. This file is used to generate random numbers for the 30 pseudo random solution vectors.

Functions.h: header file for the Functions C source file
Functions.c: Contains 18 different optimization functions to be used on the matrix declared in main.c

ArrayMem.h: header file for the ArrayMem C source file
ArrayMem.c: Contains methods that initilizes, fills in, and frees memory from a double pointer array.

SelectFunction.h: header file for the goFun C source file
SelectFunction.c: contains methods for a switch statement that calculates the fitness of a specified function from the Functions file.

PSO.h: the header file for PSO C source file, contains the struct for the algorithm
PSO.c: contains methods to perform particle swarm optimization, such as initilizing the PSO structure, starting the algorithm, calculating the velocity vector, and updating the population.

FA.h: the header file for FA C source file, contains the struct for the algorithm
FA.c: contains methods to perform the firefly algorithm, such as initilizing the FA structure, starting the algorithm, calculating beta for the algorithm, finding the distance between two fireflies, create a new firefly vector using the firefly parameters, and updating the intensity of the fireflies.

HS.h: the header file for HS C source file, contains the struct for the algorithm
HS.c: contains methods to perform harmony search algorithm, such as initilizing the HS structure, starting the algorithm, updating the values from the HS vector using PAR, checking the bounds after updating the values, and updating the population.

Util.h: the header file for a utility C source file, contains a struct for bounds, population, fitness and a dedicated function number
Util.c: contains methods that are used for a number of different files, methods to copy arrays and double arrays, returning the minimal value from a vector, sorting and printing out values.
 
txt and csv Files
----------------------
The three csv files will have new results everytime the program is ran.

mainInput.txt: This file will be used to read the bounds and the determine which function to do for this project.

PSOInput.txt, FAInput.txt, HSInput.txt: These files are used to read the PSO, FA, and HS parameters that are then stored into the each struct.

PSOInput.csv, HSInput.csv, FAInput.csv: contains the results, time and number of function calls for each algorithm

Running
-------------
!-changing the path for the mainInput.txt, PSOInput.txt, FAInput.txt and HSInput.txt files will need to be changed to absolute to run on certain systems-!
!-transfer the inputs.txt, userInput.txt, and DEinput.txt files to the cmake-build-debug folder. If the file is not located in this folder the project will exit giving the user a message that the file was not found.-!

For the Clion IDE, run the whole project by clicking the green run button or 'Shift +F10' on Windows.

If user is using a different IDE, transfer the files using Cmake to have the files work on their choice of system/IDE.

The project can be built using the CMakeLists.txt using the appropriate commands. 

IDE and Compilers used
-----------------------------
IDE: Clion
Compiler: Cmake
Environment: Mingw
Operating System: Windows 10

this prject can be used on all IDEs if Cmake is installed. 
Use Cmake to make the files available on all operating systems and IDEs.

Results
---------
included in the results file for the three algorithms is the time, fitness call counter, and best solution.

Issues
---------
Trying to perform 30 experiments were not working, the data would not update correctly except for PSO. Stagnation was not recorded because the CSV file did not have enough memory to save the population at every iteration.