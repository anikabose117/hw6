#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here

        // initialize array of unsigned long longs to 0
        unsigned long long w[5] = {0, 0, 0, 0, 0};

        // stillUnused captures how many chars we have not parsed through yet
        int stillUnused = k.length();

        // start at back and increment up by decreasing index
        int index = 4;
        while (stillUnused > 0){
            // initialize temporary list of values to 0
            char tempList[6] = {'0', '0', '0', '0', '0', '0'};
            int count = 0;
            if (stillUnused >= 6) {
                count = 6;
            } else {
                count = stillUnused;
            }
            // start at back of tempList and increment up so that if we have unused element space, the indexes at the front get the '0'
            for (int i = 0; i < count; ++i){
                tempList[i] = k[stillUnused - count + i];
            }
            
            // decrease the count of chars still to capture
            stillUnused -= count;   
            

            // w[i] = 36^5 * a1 + 36^4 * a2 + 36^3 * a3 + 36^2 * a4 + 36 * a5 + a6


            // unsigned long long t_five = 36 * 36 * 36 * 36 * 36;
            // unsigned long long t_four = 36 * 36 * 36 * 36;
            // unsigned long long t_three = 36 * 36 * 36;
            // unsigned long long t_two = 36 * 36;
            // unsigned long long t_one = 36;

            // base conversion approach from class notes
            unsigned long long base = 1;

            // equivalent to:
            // w[index] = t_five * letterDigitToNumber(tempList[0]) + t_four * letterDigitToNumber(tempList[1]) + t_three * letterDigitToNumber(tempList[2]) 
            // + t_two * letterDigitToNumber(tempList[3]) + t_one * letterDigitToNumber(tempList[4]) + letterDigitToNumber(tempList[5]);
            
            for (int i = count - 1; i >= 0; --i) {
                w[index] += letterDigitToNumber(tempList[i]) * base;
                // increases to next power by multiplying by 36
                base *= 36; 
            }

            // move up the array
            index--;
        }

        // rValues taken from either the generate rValues or are added in
        unsigned long long returnVal = rValues[0] * w[0] + rValues[1] * w[1] + rValues[2] * w[2] + rValues[3] * w[3] + rValues[4] * w[4];
        return static_cast<HASH_INDEX_T>(returnVal);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        // checking if letter is capital, if it is then lowercase it
        if (letter >= 'A' && letter <= 'Z'){
            letter = std::tolower(letter);
        }

        // returns the difference, a - a = 0
        if (letter >= 'a' && letter <= 'z'){
            return static_cast<HASH_INDEX_T>(letter - 'a');
        } 

        // for 0 - 9, just add 26 for the new value
        return static_cast<HASH_INDEX_T>(letter - '0' + 26);
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
