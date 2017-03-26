#input file
File name: a.txt
First number is the number of threads
Second number is the number of elements to be searched in input file


#command line
using redirection to take input from text file
Example: cc -o ass4 ass4.c -pthread
		 ./ass4 < a.txt


#output
File name: out.txt
Format:
"number of threads"  "time taken" 


#using plot to plot the graph
Example: gnuplot > load plot


#Graph
File name: graph.png
From graph it can be seen that initially when we increase the number of threads, time decreases because of parallelism.
But when we further increase the number of threads, time becomes random or increases as at later point number of thread does not matter as number of elements remains constant and threads start conflicting among themselves.