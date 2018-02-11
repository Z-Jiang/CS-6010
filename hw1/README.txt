How to compile and run this program on the jinx cluste；

1.Connect your computer to the Jinx;
2.Transfer this C program to the Jinx home directory using file-transferring application;
3.Run this command in the terminal when connected to Jinx: “qsub -I -q class -l nodes=1 -l walltime=00:05:00”, this is to log you in to the home directory of a compute node;
4.To compile the program, type in “gcc HW1_ZHUO/ JIANG.c -std=c99 -o myprog”;
5.To run this program: type in “./myprog”;
6.To log of the compute node and go back to the head node, type”exit”.