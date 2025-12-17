#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash
{
    HASH_INDEX_T rValues[5]{983132572, 1468777056, 552714139, 984953261, 261934300};
    bool debug_;
    MyStringHash(bool debug = true)
        : debug_(debug)
    {
        if (false == debug)
        {
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string &k) const
    {
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        int len = k.length();
        int group_index = 4; // last 6 chars

        for (int end = len; end > 0 && group_index >= 0; end -= 6)
        {
            unsigned long long groupValue = 0;

            int start;
            if (end - 6 >= 0)
            {
                start = end - 6;
            }
            else
            {
                start = 0;
            }

            for (int j = start; j < end; j++)
            {
                groupValue = groupValue * 36 + letterDigitToNumber(k[j]);
            }

            w[group_index] = groupValue;
            group_index--;
        }
        if (debug_)
        {
            for (int i = 0; i < 5; i++)
            {
                std::cout << "w[" << i << "] = " << w[i] << std::endl;
            }
        }
        unsigned long long hashValue = 0;
        for (int i = 0; i < 5; i++)
        {
            hashValue += rValues[i] * w[i];
        }
        return hashValue;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        if (letter >= 'a' && letter <= 'z')
        {
            return letter - 'a'; 
        }
        else if (letter >= 'A' && letter <= 'Z')
        {
            return letter - 'A'; 
        }
        else if (letter >= '0' && letter <= '9')
        {
            return (letter - '0') + 26;
        }
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed); // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for (int i{0}; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
