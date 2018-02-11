#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE1 100
#define SIZE2 100
#define TIMESTEPS 1000
void after_growth (int, int);
void after_fire (int, int);
void burn_them_all (int grid[SIZE1][SIZE2], int i, int j);

int main(void)
{
	int t, i, j;
	int num_tree = 0, num_total = 0;
	int grid[SIZE1][SIZE2] = {{0}};   /* initializing the value of each cell, 0 indicates no tree in that cell while 1 indicates otherwise */
	float g, f;
	float P;
	printf("please enter the value of growth probability g and lighting strike probability f.\n");
	scanf("%f %f", &g, &f);
	srand((unsigned) time(NULL));
	for(t = 1; t <= TIMESTEPS; t++)
	{
			for(i = 0; i < SIZE1; i++)		/* starting the growth phase */
			{
				for(j = 0; j < SIZE2; j++)
				{
					if(rand()%100 < 100*g)
					{
						grid[i][j] = 1;
						num_tree += 1;			/* counting the total number of trees after a growth phase of a time step */
					}
				}

			}
			/* next line is to check the status of the forest after each growth phase, which has been written as comment. */
			//after_growth (t, num_tree);
			for (i = 0; i < SIZE1; i++)			/* starting the fire phase */
			{
				for (j = 0; j < SIZE2; j++)
				{
					if(rand()%100 < 100*f)
					{
						burn_them_all (grid, i, j);
					}
				}
			}
			num_tree = 0;                       /* clearing the old data of growth phase */
			for (i = 0; i < SIZE1; i++) 	 	/* counting the number of the trees left after a fire phase */
			{
				for (j = 0; j < SIZE2; j++)
				{
					if (grid[i][j] == 1)
						num_tree+= 1;
				}
			}
			/* next line is to check the status of the forest after each fire phase, which has been written as comment. */
			//after_fire (t, num_tree);
			num_total += num_tree;

	}
	P = num_total / (TIMESTEPS * 1.00);      /* multiplying by 1.00 is to transform the right part into floating number */
	printf("With the growing posibility of %f and catching-fire possibility of %f,"
			"The average number of occupied cells P after %d time steps is %f.\n", g, f, TIMESTEPS, P );
	return 0;
}




void after_growth (int t, int num_tree)   //this function is to check the status of the forest.
{
	printf("After the growth phase of %d time steps, there are %d trees in the forest.\n", t, num_tree);
}

void after_fire (int t, int num_tree)   	//this function is to check the status of the forest.
{
	printf("After the fire phase of %d time steps, there are %d trees in the forest.\n", t, num_tree);
}

void burn_them_all (int grid[SIZE1][SIZE2], int i, int j)   //this function of recursion is to simulate the fire spreading process,
{															//according to the directions of the neighboring cells each cell has,
	if(grid[i][j] ==0)										//the whole grid is divided into 9 situations to discuss.
		return;
	grid[i][j] = 0;
	if (i == 0 && j == 0)
	{
		 burn_them_all (grid, i + 1, j);
		 burn_them_all (grid, i, j + 1);
	}
	else if (i == 0 && j != 0 && j!= (SIZE2 - 1))
	{
		burn_them_all (grid, i + 1, j);
		burn_them_all (grid, i, j + 1);
		burn_them_all (grid, i, j - 1);
	}
	else if (i == 0 && j == (SIZE2 - 1))
	{
		burn_them_all (grid, i + 1, j);
		burn_them_all (grid, i, j - 1);
	}
	else if (i != 0 && i !=  (SIZE1 - 1) && j == (SIZE2 - 1))
	{
		burn_them_all (grid, i + 1, j);
		burn_them_all (grid, i -1, j);
		burn_them_all (grid, i , j - 1);
	}
	else if (i == (SIZE1 - 1) && j != (SIZE2 - 1) && j != 0)
	{
		burn_them_all (grid, i, j + 1);
		burn_them_all (grid, i , j - 1);
		burn_them_all (grid, i - 1, j);
	}
	else if (i == (SIZE1 - 1) && j == 0)
	{
		burn_them_all (grid, i, j + 1);
		burn_them_all (grid, i - 1, j);
	}
	else if (i != 0 && i != (SIZE1 - 1) && j == 0)
	{
		burn_them_all (grid, i + 1, j);
		burn_them_all (grid, i, j + 1);
		burn_them_all (grid, i - 1, j);
	}
	else if (i != 0 && i !=  (SIZE1 - 1) && j != (SIZE2 - 1) && j != 0)
	{
		burn_them_all (grid, i + 1, j);
		burn_them_all (grid, i, j + 1);
		burn_them_all (grid, i - 1, j);
		burn_them_all (grid, i , j - 1);
	}
	else
	{
		burn_them_all (grid, i - 1, j);
		burn_them_all (grid, i , j - 1);
	}
	return;
}
