//-------------------------------------------------------------------------
// Programmer: Daniel P. Mullen
//
// Summary: This program simulates a round-robin CPU
//          scheduler. Starting with zero (0) jobs,
//          New jobs may enter during a user
//          provided time period during each (user
//          provided) time slice with a (also user
//          provided) probability of a new job arriving
//          during this add period. Jobs that still have processing time
//          remaining will be added back at the end of the waiting queue.
//          Once the add period ends,
//          the jobs that are left continue to be processed until
//          finished, ending the simulation. Each time slice and
//          the number of jobs currently in a queue to be processed
//          is output to a file every time slice iteration. The time
//          the cpu sits idle is also reported to the console.
//
// Date Last Modified:
//          10/12/17 - (DPM) Tested Job objects
//          10/14/17 - (DPM) Created que and time
//          slice subtraction, adds back to queue
//          if not done. Code is ugly tho
//          10/15/17 - (DPM) Made some print
//          functions. Made code less ugly.
//          10/16/17 - (DPM) Idle time calculated
//                     more print functions created.
//          10/17/17 - (DPM) Period for new jobs to
//                     enter created. (Finished part II)
//          10/18/17 - (DPM) Defined more constants.
//                     added some documentation.
//          10/19/17 - (DPM) FOUT added.
//          10/20/17 - (DPM) Part III finished deleted some not needed code.
//
//---------------------------------------------------------------------------
// Input: Three Real numbers from keyboard (stdin).
//        A time slice to assign to each job (in seconds).
//        A length of time to allow new jobs to enter the queue (in seconds).
//        Probability that a new job will enter the queue (0.0 to 1.0).
//        All of these are assigned prior to the simulation starting.
//
// Output: All output to console (stdout).
//         Outputs if a new job has been added or not for each time slice
//         during the add period. Also outputs the current job's ID, job type,
//         total time, and the time remaining prior to the time slice being
//         subtracted and after the time slice is subtracted. Outputs if the
//         current job is finished and how much idle time remains. At the end
//         of the simulation will output the total idle time without any jobs
//         and then the total general idle time.
//
//---------------------------------------------------------------------------


//===Preprocessors==================================
#include <iostream>
#include <fstream>
#include <queue>
#include <cassert>
#include <cmath>
#include "JOB.h"
#include "RandGenQSim.h"

using namespace std;
//==================================================

//===FunctionDeclarations===========================
void print_TimeShareTitle ();
void print_TimeShareFooter ();
void print_NotFinishedMessage (JOB currentJob);
void print_FinishedMessage(JOB currentJob);
void print_IdleTimeMessage (JOB currentJob, double idleTime);
void print_Divider();

//===EndFunctionDeclarations========================

int main()
{
    //===FileOutPreparation==========================================================
    ofstream FOUT;                       // stream to connect to output file
    FOUT.open("programA3Plot.csv");      // name and extension of output file

    FOUT << "Time" << DELIMITER << "Number of Jobs" << endl; // header
    //===EndFileOutPreparation=======================================================

    double                               //--Input-Variables---------------------------------------
            timeSlice,                   // time allotted to each job
            acceptNewJobTime,            // length of time allowed for a new job to enter the queue
            newJobProbability;           // probability that a new job will enter the queue
                                         //--End-Input-Variables-----------------------------------

    double simulationTotalTime = SIM_TIME_INITIAL;    // total time simulation has been running

    //===ReceivingTimeSlice=======================================================
    cout << "Please Enter the Allotted Time Slice for Each Job" << endl;
    cin >> timeSlice;

    //===TimeSliceReceived========================================================

    //===ReceivingacceptNewJobTime================================================
    cout << "Please Enter the Length of Time New Jobs May Enter the Queue" << endl;
    cin >> acceptNewJobTime;

    //===acceptNewJobTimeReceived=================================================

    //===newJobProbability========================================================
    cout << "Please Enter the Probability(0.0 to 1.0) a New Job Will Enter the Queue" << endl;
    cin >> newJobProbability;

    assert(newJobProbability >= NEW_JOB_PROBABILITY_MIN  && newJobProbability <= NEW_JOB_PROBABILITY_MAX);
    //===EndNewJobProbability========================================================


    //===QueCreation==============================================================
    queue <JOB> jobQueue;       // creates a que that holds job objects

    //===EndQueCreation===========================================================

    double                                                  //--VariablesKeepTrackOfIdleTime----------------
            idleTimeNoJob = IDLE_TIME_NO_JOBS_INITIAL,      // idle time when there are no jobs in queue
            totalIdleTime = IDLE_TIME_INITIAL;              // total idle time including when no jobs and when
                                                            // job finishes before time slice
                                                            //--EndVariableDeclarations---------------------

    short sizeOfQueue = QUEUE_SIZE_INITIAL;                 // keeps track of the number of jobs in the queue

    //===NewJobsArriving===========================================================================

    cout << "Simulation Starting...\nNew Jobs May Enter for: " << acceptNewJobTime << " seconds" << endl;
    print_Divider();

    while ( acceptNewJobTime > DONE_ACCEPT_NEW_JOB )  // while still time left for accepting new jobs
    {
        RandGen probabilityRoll;        // randgen object to give probability of a new job arriving
        double roll = probabilityRoll.RandReal(NEW_JOB_PROBABILITY_MIN, NEW_JOB_PROBABILITY_MAX);
        // probability will be a real between NEW_JOB_PROBABILITY_MIN && NEW_JOB_PROBABILITY_MAX defined in constants.h

        if(roll <= newJobProbability)
        {
            JOB *newJob = new JOB();             // creates a new job object
            long newJobId = newJob->get_ID();    // holds the id of newest added job.

            cout << "A New Job (ID: " << newJobId << ") Has Arrived" << endl << endl;
            jobQueue.push(*newJob);              // enqueues newest job


        }  // if probability rolls less than percent # a new job is created and added to queue

        else
        {
            cout << "No New Job Added" << endl << endl;

        }  // else if probability rolls greater than.. no new job is created

        sizeOfQueue = jobQueue.size();      // receive size of queue

        FOUT << simulationTotalTime << DELIMITER << sizeOfQueue << endl; // time and size at this time slice to file

        simulationTotalTime += timeSlice;
        //===WorkOnCurrentJobInTimeSlice==============================================================
        if (!jobQueue.empty())
        {
            cout << "Current Job Occupying Time Slice:" << endl;
            JOB currentJob = jobQueue.front();          // job currently occupying time slice

            currentJob.print();                         // print job info
            currentJob.subtract_timeSlice(timeSlice);   // subtracts time slice from time remaining

            if (currentJob.get_remainingTimeSecs() > REMAINING_TIME_MIN)
            {
                print_NotFinishedMessage(currentJob);

                jobQueue.push(currentJob);

            } // if current job needs more time add it back to the queue (at the end)

            else
            {
                if (currentJob.get_remainingTimeSecs() <= REMAINING_TIME_MIN)
                {
                    // idle time is the absolute value of the negative time remaining
                    double idleTime = fabs(currentJob.get_remainingTimeSecs());
                    totalIdleTime += idleTime;     // add idleTime to totalIdleTime

                    //--PrintMessages----------------------------
                    print_FinishedMessage(currentJob);
                    print_IdleTimeMessage(currentJob, idleTime);
                    print_Divider();

                } // if job is done but with time remaining.. add to idle time

                else
                {
                    //--PrintMessages-------------------
                    print_FinishedMessage(currentJob);
                    print_Divider();

                } // if job is done with no time remaining (very small chance this will actually happen)


            } // else report job was permanently removed

            jobQueue.pop(); // remove current job. IF not done has already been added back at the end

        } // if there are jobs in the queue. Work on the front one.

        //===EndWorkOnCurrentJobInTimeSlice===========================================================

        else if (jobQueue.empty())
        {
            idleTimeNoJob += timeSlice;
            totalIdleTime += timeSlice;

        } // if job is empty add this time with no job to total time slice

        acceptNewJobTime -= timeSlice; // decrement the time slice from the time allowed for new jobs to come in
    }  // while still accepting new jobs

    assert(acceptNewJobTime <= DONE_ACCEPT_NEW_JOB);  // cannot have time left looking for jobs at this point
    //===EndAcceptingNewJobs===========================================================

    cout << "New Jobs Can No longer Enter the Queue" << endl;
    print_Divider();

    //===FinishQueue================================================
    // finishes whatever is left in the queue

    print_TimeShareTitle();   // prints title

    while ( !jobQueue.empty() ) // While jobQueue is not empty continue time share sim
    {
        JOB currentJob = jobQueue.front();          // job currently occupying time slice

        currentJob.print();                         // print job info
        currentJob.subtract_timeSlice(timeSlice);   // subtracts time slice from time remaining

        if (currentJob.get_remainingTimeSecs() > REMAINING_TIME_MIN)
        {
            print_NotFinishedMessage(currentJob);

            jobQueue.push(currentJob);

        } // if current job needs more time add it back to the queue (at the end)

        else
        {
            if (currentJob.get_remainingTimeSecs() <= REMAINING_TIME_MIN)
            {
                // idle time is the absolute value of the negative time remaining
                double idleTime = fabs(currentJob.get_remainingTimeSecs());
                totalIdleTime += idleTime;

                //--PrintMessages----------------------------
                print_FinishedMessage(currentJob);
                print_IdleTimeMessage(currentJob, idleTime);
                print_Divider();
            }  // if job is done but with time remaining.. add to idle time

            else
            {
                //--PrintMessages----------------------------
                print_FinishedMessage(currentJob);
                print_Divider();

            }  // if job is done with no time remaining (very small chance this will actually happen)


        } // else report job was permanently removed

        jobQueue.pop(); // remove current job. IF not done has already been added back at the end

        sizeOfQueue = jobQueue.size();

        FOUT << simulationTotalTime << DELIMITER << sizeOfQueue << endl; // time and size at this time slice to file

        simulationTotalTime += timeSlice;

    } // end while
    assert(jobQueue.empty());  // jobQueue must be empty after while loop

    //print_Divider();
    cout << "Job Queue is now finished.." << endl;
    cout << "Total Time Idle With No Jobs: " <<  idleTimeNoJob << endl;
    cout << "Total Idle Time: " << totalIdleTime << endl;

    print_TimeShareFooter();    // prints footer

    //===EndFinishQueue============================================================

    return 0;

} // end main



//===FunctionsDefinitions=====================================================================

//---------------------\
// print_TimeShareTitle \
//---------------------------------------------------------------------------------------------
// Summary: Prints Time Share Title which consists of "Time Share Log" encapsulated in '-'
//
// POST: Logs "Time Share Log" encapsulated in '-' to console (stdout)
//
// SIDE EFFECTS: no side effects
//---------------------------------------------------------------------------------------------

void print_TimeShareTitle ()
{
    cout << "-----------------------------------------" << endl
         << "Now Finishing Jobs Left in Queue.." << endl
         << "-----------------------------------------" << endl << endl;

} // end print_TimeShareTitle

//---------------------\
// print_TimeShareFooter \
//---------------------------------------------------------------------------------------------
// Summary: Prints Time Share Footer which consists of "Simulation Finished" encapsulated in '-'
//
// POST: Logs "Simulation Finished" encapsulated in '-' to console (stdout)
//
// SIDE EFFECTS: no side effects
//---------------------------------------------------------------------------------------------

void print_TimeShareFooter ()
{
    cout << "-----------------------------------------" << endl
         << "Simulation Finished" << endl
         << "-----------------------------------------";

} // end print_TimeShareFooter

//---------------------\
// print_NotFinishedMessage \
//---------------------------------------------------------------------------------------------
// Summary: Prints a message for when the job is not finished
//
// PRE: Must pass an assigned currentJob variable of type JOB to access ID and remainingTimeSecs.
//
// POST: Logs currentJob's id and the seconds remanining to console(stdout).
//
// SIDE EFFECTS: no side effects
//---------------------------------------------------------------------------------------------

void print_NotFinishedMessage (JOB currentJob)
{
    cout << "Job ID: " << currentJob.get_ID() << " not finished." << endl;
    printf("%.2f seconds remaining.\nAdded to end of queue.\n", currentJob.get_remainingTimeSecs());
    cout << "-----------------------------------------" << endl << endl;

} // end print_NotFinishedMessage

//---------------------\
// print_FinishedMessage \
//---------------------------------------------------------------------------------------------
// Summary: Prints a message for when the job is finished
//
// PRE: Must pass an assigned currentJob variable of type JOB to access ID.
//
// POST: Logs currentJob's id and removal from queue to console(stdout).
//
// SIDE EFFECTS: no side effects
//---------------------------------------------------------------------------------------------

void print_FinishedMessage(JOB currentJob)
{
    cout << "Job ID: " << currentJob.get_ID() << " finished. \nRemoved from queue." << endl;

} // end print_FinishedMessage

//---------------------\
// print_IdleTimeMessage \
//---------------------------------------------------------------------------------------------
// Summary: Prints a message of the time the cpu sits idle.
//
// PRE: Must pass an assigned currentJob variable of type JOB to access ID and an assigned
//      double that holds the idleTime.
//
// POST: Logs currentJob's id and idle time of cpu (idleTime) to console(stdout).
//
// SIDE EFFECTS: no side effects
//---------------------------------------------------------------------------------------------

void print_IdleTimeMessage (JOB currentJob, double idleTime)
{
    cout << "Job ID: " << currentJob.get_ID() << " did not use entire time slice." << endl;
    printf("CPU sits idle for: %.2f seconds\n", idleTime);

} // end print_IdleTimeMessage

//---------------------\
// print_IdleTimeMessage \
//---------------------------------------------------------------------------------------------
// Summary: Prints a border divider consisting of '-'
//
// POST: Logs '-' to console(stdout) with two line breaks.
//
// SIDE EFFECTS: no side effects
//---------------------------------------------------------------------------------------------

void print_Divider ()
{
    cout << "-----------------------------------------" << endl << endl;

} // end print_Divider

//===EndFunctionDefinitions============================================


//---------------------------------EOF--------------------------------------------