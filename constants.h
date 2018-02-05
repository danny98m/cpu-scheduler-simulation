#ifndef A3_CONSTANTS_H
#define A3_CONSTANTS_H

//----------------------------------------------------------------------
//  SPECIFICATION FILE (constants.h)
//  This file contains the constants used throughout this program
//----------------------------------------------------------------------

//===RangeOfTotalTime===============================================================
const short PRINT_TIME_MIN = 1;             // minimum print job time
const short PRINT_TIME_MAX = 5;             // maximum print job time

const short COMPILE_TIME_MIN = 10;          // minimum compile job time
const short COMPILE_TIME_MAX = 100;         // maximum compile job time

const short EMAIL_TIME_MIN = 3;             // minimum email job time
const short EMAIL_TIME_MAX = 20;            // maximum email job time

const short OTHER_TIME_MIN = 0;             // minimum other job time
const short OTHER_TIME_MAX = 45;            // maximum other job time
//===EndRangeOfTotalTime=============================================================

//===JobProbability==================================================================
const short PROBABILITY_MIN = 1;            // num roll from 1
const short PROBABILITY_MAX = 100;          // to 100

const short PRINT_PROB_MIN = 1;             // min num resulting in print job
const short PRINT_PROB_MAX = 20;            // max num resulting in print job

const short COMPILE_PROB_MIN = 21;          // min num resulting in compile job
const short COMPILE_PROB_MAX = 50;          // max num resulting in compile job

const short EMAIL_PROB_MIN = 51;            // min num resulting in email job
const short EMAIL_PROB_MAX = 90;            // max num resulting in email job

const short OTHER_PROB_MIN = 91;            // min num resulting in other job
const short OTHER_PROB_MAX = 100;           // max num resulting in other job
//===EndJobProbability================================================================

//===ProbabilityOfNewJob==============================================================
const double NEW_JOB_PROBABILITY_MIN = 0;   // min percentage of new job probability
const double NEW_JOB_PROBABILITY_MAX = 1;   // max percentage of new job probability
//===EndProbabilityOfNewJob===========================================================

//===TimeForAcceptingJobs=============================================================
const short DONE_ACCEPT_NEW_JOB = 0;        // end of when new jobs can be accepted
//===EndTimeForAcceptingJobs==========================================================

//===RemainingJobTime=================================================================
const short REMAINING_TIME_MIN = 0;         // end of remaining time
//===EndRemainingJobTime==============================================================

//===Delimiter========================================================================
const char DELIMITER = ',';                 // comma-separated-values (.csv)
//===EndDelimiter=====================================================================

//===SummationConstants===============================================================
const double SIM_TIME_INITIAL = 0;
const double IDLE_TIME_NO_JOBS_INITIAL = 0;
const double IDLE_TIME_INITIAL = 0;
const short  QUEUE_SIZE_INITIAL = 0;
//===EndSummationConstants============================================================

//===RandID===========================================================================
const long ID_MIN = 0;                      // smallest id num
const long ID_MAX = 2147483647;             // largest id num
//===EndRandID========================================================================

#endif //A3_CONSTANTS_H

//-----------------------------------EOF----------------------------------------------