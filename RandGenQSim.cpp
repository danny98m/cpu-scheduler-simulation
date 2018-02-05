//--------------------------------------------------
// Summary: This file contains several methods for
//          the class RandGen, a random generator
//          that works with integers, reals, and
//          job names that relate to the time share
//          simulation.
//--------------------------------------------------

//===Preprocessors==================================
#include <ctime>                // for time()
#include <cstdlib>              // for rand/srand
#include <iostream>
#include "RandGenQSim.h"
#include "constants.h"

using namespace std;
//===================================================

long RandGen::ourInitialized = 0;            // initializes seed

RandGen::RandGen()
// POSTcondition: system srand() used to initialize seed
//                once per program for all RandGen objects
{
    if (0 == ourInitialized)
    {
        ourInitialized = 1;      // only call srand once
        srand(static_cast<unsigned>(time(0)));       // set seed
		rand();
    }
}


long RandGen::RandInt(long max)
// PREcondition: max > 0
// POSTcondition: returns int in [0..max)
{  
    return static_cast<long>(RandReal() * max);
}

long RandGen::RandInt(long low, long max)
// PREcondition: low <= max
// POSTcondition: returns int in [low..max]
{ 
    return low + RandInt(max-low+1);
}

double RandGen::RandReal()
// POSTcondition: returns double in [0..1)
{     
    return rand() / (static_cast<double>(RAND_MAX) + 1); 
}

double RandGen::RandReal(double low, double max)
// PREcondition: low <= max
// POSTcondition: returns double in [low..max]
{
    return  low + RandReal() * (max-low);
}

string RandGen::RandJob()
//POSTcondition: returns string of job name based on probability generated randomly
{
    RandGen probability;
    short probabilityNum = probability.RandInt(PROBABILITY_MIN, PROBABILITY_MAX);

    if (probabilityNum >= PRINT_PROB_MIN and probabilityNum <= PRINT_PROB_MAX)
    {
        return "print";
    } // end if

    else if (probabilityNum >= COMPILE_PROB_MIN and probabilityNum <= COMPILE_PROB_MAX)
    {
        return "compile";
    } // end else if

    else if (probabilityNum >= EMAIL_PROB_MIN and probabilityNum <= EMAIL_PROB_MAX)
    {
        return "email";
    } // end else if

    else if (probabilityNum >= OTHER_PROB_MIN and probabilityNum <= OTHER_PROB_MAX)
    {
        return "other";
    } // end else if

    else
    {
        cout << "Random generator failure..." << endl;
    } // end else

}

//------------------------EOF---------------------------------------------------\\