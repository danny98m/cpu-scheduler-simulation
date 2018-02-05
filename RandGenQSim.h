#ifndef _MYRAND_H
#define _MYRAND_H

//----------------------------------------------------------------
// SPECIFICATION FILE (RandGenQSim.h)
// designed for implementation independent randomization
// if all system dependent calls included in this class, then
// other classes can make use of this class in independent manner
//
// all random numbers are uniformly distributed in given range
//-----------------------------------------------------------------

//===Preprocessors=================================================
#include <limits.h>                     // for INT_MAX
#include <iostream>

using namespace std;
//=================================================================

class RandGen
	{
	public:
		RandGen();                                  // CTOR: set seed once for all instances

		long RandInt(long max = INT_MAX);           // returns int in [0..max)
		long RandInt(long low, long max);           // returns int in [low..max]
        
		double RandReal();                          // returns double in [0..1)
		double RandReal(double low, double max);    // returns double range [low..max]

		string RandJob();                           // returns random job name based on probability
        
		
	private:
		static long ourInitialized;                 // for 'per-class' initialization
	};

#endif    // _MYRAND_H not defined

//------------------------------------EOF-------------------------------------------------------