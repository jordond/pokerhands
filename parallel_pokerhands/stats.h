#ifndef STATS_H
#define STATS_H

#include <map>
#include <iomanip>
#include <ctime>
#include "deck.h"

class Stats {
private:
    typedef Hand::HandType type_t;      // Used to shorten handtype
    std::map<std::string, int> stats_;  // Map that contains all the frequencies
    int hands_;                         // Counter of all the hands that have been drawn
    std::string version_;               // Parallel or Serial version
    clock_t begin_;                     // Timer start variable
    clock_t end_;

public:
    Stats();                            // Default Constructor
    ~Stats();                           // Default destructor

    void start();                       // Start the timer
    void stop();                        // Stop the timer
    void reset();                       // Reset the timer
    double getClock();                  // Get the elapsed time in seconds

    void increment(int);                // Increment the Map of frequencies by single Hand type (int)
    void increment(int, int);           // Increment the Map of frequencies by multiple of the same Hand type (int int)

    int getTypeCount(int);              // Return the number of a specific hand found
    int getHands() { return hands_; }   // Return the number of hands drawn
    bool allHandsFound();               // Return true if all of the 10 hand types have been found

    void printHeader();                 // Print the header information
    void printFooter(int);              // Parallel version of print footer requires int for number of processes
    void printHands();                  // Print the frequency information
    void printHistogram();              // TODO print out a histogram of all freqs

    std::string typeToString(int);      // Take the hand type (enum/int) and return the String equivalent
};

#endif