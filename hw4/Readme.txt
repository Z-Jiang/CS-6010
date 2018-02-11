How to compile and run this program on the jinx cluster；

1.Connect your computer to the Jinx;
2.Transfer this C program to the Jinx home directory using file-transferring application;
3.Run this command in the terminal when connected to Jinx:
 “qsub -I -q class -l nodes=1”, this is to log you in to the home directory of a compute node;
4.To compile the sequential program, type in “gcc Sequential.c -std=c99 -o se”;
5.To run this program: type in “./se 500000 Sequential_Output”;
6.To log out of the compute node and go back to the head node, type”exit”.
7.To compile the parallel program, type in “gcc Parralel.c -fopenmp -std=c99 -o pa”;
8.To run this program: type in “./pa 500000 Parralel_Output”;
9.To log out of the compute node and go back to the head node, type”exit”.