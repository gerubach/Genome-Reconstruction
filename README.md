All of the code for this project is in the .cpp and .h files. For the executable, download the zip file (there is also a short report in the zip file which does an analysis on the results collected). Once downloaded, DO NOT DELETE ANYTHING IN THE ZIP FILE! 
When the program is started, it will ask you to enter 1 for the first set of trials and 0 for the second set of trials.

The first set of trials constructs an arbitrary genome using a specified read length (there are no repeats in these trials). 
The program will prompt you for the read length and will terminate after performing 10 trials. 
When the program terminates, it will say "All data has been generated."
The output will be in the text file results.txt. In results.txt there will be a single number which is the number of trials out of 10 that the arbitrary genome that was generated was the same as the original genome.

The second set of trials keeps generating random genomes until the correct one is generated. The program will prompt you for read length, repeat length, and number of repeats. 
Putting in negative values for any of these may crash the program. 
Just as in the first set, it will terminate after performing 10 trials, will say "All data has been generated" when it terminates, and the output will be in results.txt.
In results.txt there will be 10 numbers which are the number of random walks generated before success in each trial.

Both sets of trials may take a while to generate data, especially the second set. THIS IS NORMAL. 
For some values of read length, repeat length, and number of repeats the program will take an indefinite amount of time to terminate.
All this means is that the program has, by random chance, had to calculate tens of thousands of attempts for this particular genome. 
