#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

int main(){    
    std::vector<int> intcode;
    int intcodevalue;

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

    //print debugging to ensure I grabbed the entire file correctly.
    // for (int i=0; i<intcode.size(); i++){
    //     std::cout << intcode[i] << " ";
    // }

    bool bHalt = false;
    int intcodeInspect = 0;

    //manual replacement of intcode values as described by the problem description.
    intcode[1] = 12;
    intcode[2] = 2;

    while (!bHalt){
        for (int i = 0; i < intcode.size(); i+=4){
            int opcode = intcode[i];

            
            int posA = intcode[i+1];
            int posB = intcode[i+2];
            int posResult = intcode[i+3];

            //log out each encountered opcode
            //std::cout << "\nopcode: " << opcode << " PosA: " << posA << " PosB: " << posB << " posResult: " << posResult;

        
            switch(opcode){
            case 1:
                intcode[posResult] = intcode[posA] + intcode[posB];
                break;
            case 2: 
                intcode[posResult] = intcode[posA] * intcode[posB];
                break;
            case 99:
                bHalt = true;
                i = intcode.size();
                std::cout << "OPCODE 99 DETECTED. \nWhich intcode position would you like to investigate?: ";
                std::cin >> intcodeInspect;
                std::cout << intcode[intcodeInspect];
                break;
            }
        }
    }
}

/*
    What I learned in this challenge:
    -- Manipulating the index of a for loop can allow you non-linear jumps through an array, which is helpful when processing groups of items at once.
    -- I had a lot of practice with discovering how to manipulate vectors in this program.
    -- How to ask for help on Stack Overflow!

    The puzzle's solution is 2894520.
*/