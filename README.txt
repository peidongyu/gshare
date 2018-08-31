========================================================================================
GShare Branch Predictor: Introduction
========================================================================================
This project implements a simple GShare Branch Predictor simulator. This simulator takes
program counter address and performs the GShare predictions reduce penalties from 
stalls and in pipelines and reduce the number of incorrect predictions.


========================================================================================
ABOUT: THE SOURCE CODE
========================================================================================
The structure of the cache simulator is written with a C++ class called gshare. This has 
fields for the number of global history register bits, program counter bits, the 
global history buffer, as well as the prediction history table.

The constructor calls *set_params() which generates the GShare predictor and initializes 
the correct and mispredicts to 0. A function called *branch_predict() gets the address 
with the 2 LSB's removed. The M bits from the PC address are XORed with global history
buffer and the prediction and outcome are compared. The corresponding correct/mispredict
variables are updated along with updating the 2-bit prediction state from *increment()
and updating the global history with *updateGHB().

The main function is also written in the source file. This takes in 4 arguments and 
will exit upon failure to input correct number of paramters. A file stream is used to 
read in the trace file. An instance of the class is called in main to generate the 
appropriate cache type. If the file is not present, then the system will exit on failure.
This can be seen in the *while-loop where the cache reads in the file and updates the 
cache with the read address. The end of main prints out the results.

----------------------------------------------------------------------------------------
Notes:
    * The report provides more detail on these function as they are much more complex
      and deserve more attention.
----------------------------------------------------------------------------------------
========================================================================================
GETTING STARTED
========================================================================================
****************************************************************************************
To compile the code, the GNU g++ compiler is required:
    1. LINUX:
        Do the following:
            sudo apt-get update
            sudo apt-get update install g++
    2. Mac:
        Do the following:
            In the Terminal window type g++ and press the Return key.
            Choose Install.
            After installation, type g++ in the Terminal, press the Return key, and 
                verify the terminal prints the message, "no input files".
    3. Windows 10:
        Install the windows bash terminal if not already done.
        Then follow the steps for Linux

    Note : Below windows 10 will be an issue. Please refer to other outlets on how to 
            install g++ into CMD.
****************************************************************************************

Once g++ is installed. To compile the code, execute

    g++ cache.cpp -o gshare.out

If required the following will work for C++11

    g++ --std=c++11 gshare.cpp -o gshare.out

========================================================================================
RUNNING THE TESTS
========================================================================================

1 .To run the file execute the following: 
    
    ./gshare.out <M> <N> <FILENAME>

Main will be looking for five arguments (including the name "simulator.out") so it will 
not execute otherwise.

2. A bash script has been provided to run the cases posted on webcourses. To run execute:

    bash test-cases.sh
