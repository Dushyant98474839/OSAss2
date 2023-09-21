
MAIN .C FILE

In q2 of assignment 2, I made 4 .c files in which 1 is main.c file containing the main code and rest 3 are files for counting from 1 to 2^32. 
In the main.c file, first we include the necessary headers required for the code to run.
then in the main function we make two variables of struct timespec (time_start & time_end).
Then make one child using the fork and inside the first child made a variable s of struct sched_param to scheduke the process with specified 
scheduling policies.in fork 1 I have made the policy to be SCHED_OTHER and set the priority to 0 as nice=0.

Then used execl command to execute the p1 file . Also giving errors if execl or fork falied.  

Then similarly creating the second child and keeping the scheduling policy to SCHED_RR with default priority and also handled the errors.

The third child is also created in a same manner keeping the policy to SCHED_FIFO with default priority and also handled the errors.

Then after initiating all the three processes,I added the pids of the children in an array which I used later.

I used a for loop in which I used waitpid to wait for processes to exit one by one the used clock_gettime function to calculate the time of termination of a particular process and the elapsed time is calculated
using the tv_sec and tv_nsec from time_spec struct and subtracting the same for starting and time thus getting the time elapsed.

I opened the file named "RESULT.txt" and adding the time elapsed in the file so that these can be used further in making graphs.


Then I made two py files one for bar graph and one for histogram. I made both as it was not clear in the question what to make.

BAR GRAPH

I opened the RESULT.txt file and read the elapsed time and stored them in a list and used matplotlib lib to plot bar graph. Made a color list to add colours to the columns of the bar graph

HISTOGRAM

I opened the RESULT.txt file and read the elapsed time and stored in a list and made a histogram using plt.hist() function

    
