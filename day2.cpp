#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

int main(){    
    std::vector<int> intcode;
    int intcodevalue, target = 19690720, noun = 0, verb = 0;
    bool bHalt = false, bTargetFound = false, bReplaced = false;

    // the following blocks were derived from example code given by a question I asked on stackoverflow here: https://stackoverflow.com/a/63516670/2600603

    std::ifstream file("input.txt");
    std::string inputLine;

    if (getline(file,inputLine)) {                  //if we can get a line of text successfully from "file", and store it in a string...
        int tempint;                                //a temp int to store the line
        std::stringstream sstream(inputLine);       //create a string stream from input line - This looks like a cast!

        while(sstream >> tempint){                  //while an integer can be extracted from the string stream
            std::string tempstring;                 //create a temp string to hold the delimiter
            intcode.push_back(tempint);             //write the integer into the array
            getline(sstream, tempstring, ',');      //get the next line from the stringstream, write it to temp string, while searching for comma delimiters.
        }
    }

    //create a copy of the intcode
    std::vector<int> freshCopyOfIntcode;
    for (int i=0;i < intcode.size();i++)
    {
        freshCopyOfIntcode.push_back(intcode[i]);
    }

    //loop through potential intcode values until we find the correct combination:
    for (int n = 0; n <= 99; n++){
        for (int v = 0; v <= 99; v++)
        {
            //reset the intcode to the fresh copy again
            for (int c=0;c<freshCopyOfIntcode.size();c++){
                intcode[c] = freshCopyOfIntcode[c];
            }

            while(!bHalt && !bTargetFound){
                for (int i =0; i < intcode.size(); i+=4){
                    if(!bReplaced){
                        intcode[1] = n;
                        intcode[2] = v;
                        bReplaced = true;
                    }

                    int opcode = intcode[i];
                    int parameterA = intcode[i+1];
                    int parameterB = intcode[i+2];
                    int resultLocation = intcode[i+3];

                    std::cout << "OpCode, Position: " << opcode << "[" << intcode[i] << "]\n";
                    std::cout << "Parameter A, Position: " << intcode[i+2] << "[" << parameterA << "]\n";
                    std::cout << "Parameter B, Position: " << intcode[i+2] << "[" << parameterB << "]\n";
                    std::cout << "Parameter Result, Position: " << intcode[i+3] << "[" << resultLocation << "]\n";

                    switch(opcode){
                        case 1:
                            intcode[resultLocation] = intcode[parameterA] + intcode[parameterB];
                            break;
                        case 2:
                            intcode[resultLocation] = intcode[parameterA] * intcode[parameterB];
                            break;
                        case 99:
                            bHalt = true;
                            std::cout << "OPCODE 99 DETECTED....Processing: ";
                            if (intcode[0] == target){
                                bTargetFound = true;
                                std::cout << "TARGET FOUND.";
                            }
                            else{
                                std::cout << "Target Not Found.";
                            }
                            break;
                    }
                    
                    if (!bTargetFound){
                        bHalt = false;
                    }
                }
            }

            //re-initialize using the new noun/verb combo:
            intcode[1] = noun;
            intcode[2] = verb;
            bHalt = true;
        }
    }
}

/*
    What I learned in this challenge:
    -- The intcode challenge is an analogy for working with computer memory. positions in the intcode are memory addresses. Opcodes are processor instructions. The values following an opcode are parameters. I've renamed some variables to reflect this!

    -- Seriously, asking for help is invaluable. Google has a lot of great answers but unless someone is solving something incredibly similar it may not always be helpful!
*/


/*

You have a correct understanding that the answer is 100 * noun + verb when mem[0] is the goal number when the program halts, but I would not necessarily express that as mem[1] and mem[2] because the program can modify itself as it executes and there are no guarantees it doesn't touch those addresses. Just keep track of what you provided for noun and verb.

And yes, each test run gets a fresh, independent copy of the initial program. To test n = 1, v = 5, you would take a fresh copy of the input, set mem[1] = 1 and mem[2] = 5, then execute it until it halts and inspect mem[0].


"To solve the problem, you need to determine what pair of inputs produces the output 19690720."

So when intcode[0] == 19690720, inspect intcode[1] and intcode[2]. Then do 100 * intcode[1] + intcode[2] for the answer (NOTE! NOT FOLLOWING THE ORDER OF OPERATIONS.)


Intcode programs are a list of integers; these values are used as the initial state for the computer's memory. 

When you run an Intcode program, make sure to start by initializing memory to the program's values. 

A position in memory is called an address (for example, the first value in memory is at "address 0").

Opcodes (mark the beginning of an instruction. The values used immediately after an opcode, if any, are the instruction's parameters.

The address of the current instruction is the instruction pointer. After an instruction finishes, the  pointer increases by the number of values in the instruction (in the case of 0/1, by 4. In the case of 99, by 1.). 

The inputs should still be provided to the program by replacing the values at addresses 1 and 2, just like before. In this program, the value placed in address 1 is called the noun, and the value placed in address 2 is called the verb. Each of the two input values will be between 0 and 99, inclusive.

Once the program has halted, its output is available at address 0, also just like before. Each time you try a pair of inputs, make sure you first reset the computer's memory to the values in the program (your puzzle input) - in other words, don't reuse memory from a previous attempt.

Find the input noun and verb that cause the program to produce the output 19690720. What is 100 * noun + verb? (For example, if noun=12 and verb=2, the answer would be 1202.)


*/