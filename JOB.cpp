//---------------------------------------------------
// Programmer: Daniel P. Mullen
//
// Summary: This file holds various methods
//          for the class JOB which includes
//          a user id, a job name, total time
//          of job, and the remaining time
//          of a job.
//
// Date Last Modified:
//          10/12/17 - (DPM) created setters
//          and getters with randgen functions
//          10/14/17 - (DPM) created print
//          function and subtract function
//          10/15/17 - (DPM) methods now work
//          for real numbers. Methods also have
//          better documentation
//---------------------------------------------------

//===Preprocessors===================================
#include "JOB.h"
#include "RandGenQSim.h"
#include <vector>
#include <iostream>

using namespace std;
//===================================================

vector <long> ids;
//===ConstructorMethods=======================================================================

//---------------------\
// JOB() \
//---------------------------------------------------------------------------------------------
// Summary: Constructs JOB object with random id, name, and total time
//
// POST: Create an object of data type JOB with a random id, name, and total time.
// timeRemainingSecs initialized to total time.
//
// SIDE EFFECTS: no side effects
//---------------------------------------------------------------------------------------------
JOB::JOB()
{
    JOB::set_ID();                      // sets random ID
    JOB::set_name();                    // sets random Job name
    JOB::set_totalTimeSecs();           // sets total time
    timeRemainingSecs = totalTimeSecs;  // initially makes time remaining same as total time

} // end JOB()

//---------------------\
// JOB(useThisId) \
//---------------------------------------------------------------------------------------------
// Summary: Constructs JOB object with user assigned ID and a random name and total time
//
// PRE: Must pass a short to be assigned to id of JOB object
//
// POST: Create an object of data type JOB with a user assigned id a random name and total time.
// timeRemainingSecs initialized to total time.
//
// SIDE EFFECTS: no side effects
//---------------------------------------------------------------------------------------------
JOB::JOB(short useThisId) // random gen everything except the id
{
    id = useThisId;                     // sets id to given id
    JOB::set_name();                    // sets random job name
    JOB::set_totalTimeSecs();           // sets random total time
    timeRemainingSecs = totalTimeSecs;  // initially makes time remaining same as total time

} // end JOB(useThisID)

//===EndConstructorMethods=====================================================================


//===SetterMethods=============================================================================

//---------------------\
// set_ID() \
//---------------------------------------------------------------------------------------------
// Summary: Creates a random and unique id for a JOB object
//
// POST: A random and unique id is assigned to id for an object of type JOB
//
// SIDE EFFECTS: no side effects
//---------------------------------------------------------------------------------------------

void JOB::set_ID()
{
    RandGen Rand_Id;                // makes a RandGen object called Rand_ID

    id = Rand_Id.RandInt(ID_MIN, ID_MAX);       // sets id to a random int called by the RandInt method from RandGen

    for (short i = 0; i < ids.size(); i++)
    {
        if (id == ids[i])
        {

            id = Rand_Id.RandInt(ID_MIN, ID_MAX);

        } // if id has already been chosen, generate a new one

    }

    ids.push_back(id);


} // end set_ID

//---------------------\
// set_name() \
//---------------------------------------------------------------------------------------------
// Summary: Sets job name to one of four options
//
// POST: Randomly selects one of four job options based on a probability calculator and sets
//       name equal to the selected job.
//
// SIDE EFFECTS: No side effects
//---------------------------------------------------------------------------------------------
void JOB::set_name()
{
    RandGen Rand_Job_Name;          // makes a RandGen object called Rand_Job_Name
    name = Rand_Job_Name.RandJob(); // sets name to a random job called by the RandJob method from RandGen

} // end set_name

//---------------------\
// set_totalTimeSecs() \
//---------------------------------------------------------------------------------------------
// Summary: Sets total time of job to a random number based on job.
//
// POST: totalTimeSecs == random number between jobTimeMin & jobTimeMax.
//
// SIDE EFFECTS: No side effects
//---------------------------------------------------------------------------------------------
void JOB::set_totalTimeSecs()
{
    RandGen jobTime;                // makes a rand gen object called jobTime

    if (name == "print")
    {
        totalTimeSecs = jobTime.RandReal(PRINT_TIME_MIN, PRINT_TIME_MAX);
    } // if print job, set totaltime to num between min print times and max print times inclusive

    else if (name == "compile")
    {
        totalTimeSecs = jobTime.RandReal(COMPILE_TIME_MIN, COMPILE_TIME_MAX);
    } // if compile job, set totaltime to num between min compile times and max compile times inclusive

    else if (name == "email")
    {
        totalTimeSecs = jobTime.RandReal(EMAIL_TIME_MIN, EMAIL_TIME_MAX);
    } // if email job, set totaltime to num between min email times and max email times inclusive

    else if (name == "other")
    {
        totalTimeSecs = jobTime.RandReal(OTHER_TIME_MIN, OTHER_TIME_MAX);
    } // if other job, set totaltime to num between min other times and max other times inclusive

    else
    {
        cout << "Job type not found" << endl;
    }

} // end set_totalTimeSecs

//===EndSetterMethods===========================================================================

//===GetterMethods==============================================================================

//---------------------\
// get_ID() \
//---------------------------------------------------------------------------------------------
// Summary: Returns id of object
//
// POST: id is returned
//
// SIDE EFFECTS: No side effects
//---------------------------------------------------------------------------------------------
long JOB::get_ID()
{
    return id;

} // end get_ID

//---------------------\
// get_name() \
//---------------------------------------------------------------------------------------------
// Summary: Returns job name of object
//
// POST: name is returned
//
// SIDE EFFECTS: No side effects
//---------------------------------------------------------------------------------------------
string JOB::get_name()
{
    return name;

} // end get_name

//---------------------\
// get_totalTimeSecs () \
//---------------------------------------------------------------------------------------------
// Summary: Returns total time of job
//
// POST: totalTimeSecs of object is returned
//
// SIDE EFFECTS: No side effects
//---------------------------------------------------------------------------------------------
double JOB::get_totalTimeSecs()
{
    return totalTimeSecs;

} // end get_totalTimeSecs

//---------------------\
// get_remainingTimeSecs() \
//---------------------------------------------------------------------------------------------
// Summary: Returns remaining time for job of object
//
// POST: timeRemainingSecs of object is returned
//
// SIDE EFFECTS: No side effects
//---------------------------------------------------------------------------------------------
double JOB::get_remainingTimeSecs()
{
    return timeRemainingSecs;

} // end get_remainingTimeSecs

//===EndGetterMethods================================================

//===MiscUtilityMethods==============================================

//---------------------\
// print() \
//---------------------------------------------------------------------------------------------
// Summary: Prints all data of object
//
// POST: logs id, name, totalTimeSecs, and timeRemainingSecs to console (stdout)
//
// SIDE EFFECTS: No side effects
//---------------------------------------------------------------------------------------------
void JOB::print()
{
    cout << "ID: " << JOB::get_ID() << endl;
    cout << "Job Type: " << JOB::get_name() << endl;
    printf("Total Time of Job: %.2f\n", JOB::get_totalTimeSecs());
    printf("Time Remaining Prior to Time Slice: %.2f\n", timeRemainingSecs);
    cout << endl;

} // ends print

//---------------------\
// subtract_timeSlice(timeSlice) \
//---------------------------------------------------------------------------------------------
// Summary: Subtracts timeSlice from timeRemainingSecs
//
// PRE: Must pass a double
//
// POST: IF timeSlice is a double. Subtracts timeSlice from timeRemainingSecs and assigns
//       timeRemainingSecs to the new time remaining.
//
// SIDE EFFECTS: No side effects
//---------------------------------------------------------------------------------------------
void JOB::subtract_timeSlice(double timeSlice)
{
    timeRemainingSecs = timeRemainingSecs - timeSlice;

} // ends subtract_timeSlice

//===EndMiscUtilityMethods=========================================================

//------------------------------------EOF------------------------------------------