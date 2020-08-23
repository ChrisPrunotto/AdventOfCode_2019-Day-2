#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

int main(){    
    std::vector<int> intcode;
    std::vector<int> freshIntcode;
    int targetResult = 19690720;


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

    //copy the intcode onto a separate vector, to always have a fresh copy without re-reading the input file.
    for (int c=0; c<intcode.size(); c++){
        freshIntcode.push_back(intcode[c]);
    }

    bool bHalt = false, bSuccess = false;

     while (!bHalt){
        for (int n=0; n<=99;n++) {                                  //iterate noun values
            for (int v=0; v<=99;v++) {                              //interate verb values 
                if (!bSuccess){

                    //refresh the intcode back to default using the copy
                    for (int r=0; r<intcode.size(); r++){
                        intcode[r] = freshIntcode[r];
                    }
                    
                    intcode[1] = n;
                    intcode[2] = v;
                    
                    //iterate over opcodes
                    for (int i=0; i<intcode.size(); i += 4){
                        int opcode = intcode[i];

                        
                        int posA = intcode[i+1];
                        int posB = intcode[i+2];
                        int posResult = intcode[i+3];

                        //DEBUG: log out each encountered opcode
                        //std::cout << "\nopcode: " << opcode << " PosA: " << posA << " PosB: " << posB << " posResult: " << posResult;

                        switch(opcode){
                        case 1:
                            intcode[posResult] = intcode[posA] + intcode[posB];
                            break;
                        case 2: 
                            intcode[posResult] = intcode[posA] * intcode[posB];
                            break;
                        case 99:
                            i = intcode.size();
                            std::cout << "OPCODE 99 DETECTED...Investigating..." << n << ", " << v << "...";

                            if(intcode[0] == targetResult){
                                bSuccess = true;
                                bHalt = true;
                                std::cout << "SUCCESS: " << "NOUN: " << n << " VERB: " << v << ".\n";
                                std::cout << "The solution is: " << (100 * n + v);
                            }
                            else {
                                std::cout << "Failure...\n";
                            }
                            break;
                        }
                    }
                }
            }
        }
        bHalt = true;       //safety break;
    }
}




/*
    What I learned in this challenge:
    -- The intcode challenge is an analogy for working with computer memory. positions in the intcode are memory addresses. Opcodes are processor instructions. The values following an opcode are parameters. I've renamed some variables to reflect this!

    -- Asking for help is invaluable. Google has a lot of great answers but unless someone is solving something incredibly similar it may not always be helpful!

    -- The while loop seems to only get evaluated at the top of the loop when it checks, so I don't think you can break it midway by just changing the value it's testing.
    
    -- I should make sure to get into good practice of immediately cancelling out my while loop test equations when I write one, or risk forgetting to break an infinite loop.

    -- PAY ATTENTION TO THE ACTUAL OUTPUT BEING REQUESTED! I was going nuts searching through the code because I misread the final requested solution as 100 * noun * verb, when it was actually 100 * noun + verb 

    The solution is 9342.
*/