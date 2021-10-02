#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NUM 4

struct square {
	int num;
	int poss[NUM];
};

struct square board[NUM][NUM];
struct square board_backup[NUM][NUM];

int colup[NUM];
int coldown[NUM];
int rowleft[NUM];
int rowright[NUM];

void remove_possibility(int i, int j, int n) {	
	board[i][j].poss[n-1] = 0;
}

void decrease_possibilities(int i, int j, int n) {
	
	int k = 0;
	int l = 0;
	
	printf("Decreasing...\n");
	while(l < NUM) {
		remove_possibility(i, l, n);
		l++;
	}

	while(k < NUM) {
		remove_possibility(k, j, n);
		k++;
	}
}

void add_number(int i, int j, int n) {
	board[i][j].num = n;
	decrease_possibilities(i, j, n);
}

// it will return 0 if more than one possibility is found
// else return the uniaue possibility
int check_if_one_possibility(int i, int j) {
	int k = 0;
	int counter = 0;
	int index;
	
	printf("check if one possibility called\n");
	while(k < NUM) {
		if (board[i][j].poss[k] != 0) {
			counter++;
			index = k;
		}
		k++;
	}

	if (counter == 1)
		return board[i][j].poss[index];
	else
		return 0;
}

int fill_if_one_poss_exist(void) {
	int i;
	int j;
	int n;
	int counter;

	counter = 0;
	i = 0;
	j = 0;
	while(i < NUM) {
		j = 0;
		while(j < NUM) {
			printf("fill %d %d\n", i, j);
			if (board[i][j].num == 0) {
				n = check_if_one_possibility(i, j);

				if (n != 0) {
					add_number(i, j, n);
					counter++;
				}
			}
			j++;
		}
		i++;
	}
	printf("++++++++++++NUMBER OF ITEMS FIXED %d\n", counter);
	return counter;
}

void initialize_values(void) {
	int i = 0;
	int j = 0;
	int n;
	
	n = 1;
	while(j < NUM) {
		if (colup[j] == 1) {
			add_number(i, j, NUM);
		}
		// it will work only on 4x4
		
		if (colup[j] == 2) {
			remove_possibility(i, j, 4);
		}

		if (colup[j] == 3) {
			remove_possibility(i, j, 4);
			remove_possibility(i, j, 3);
		}

		if (colup[j] == NUM) {
			while(i < NUM) {
				add_number(i, j, n);
				n++;
				i++;
			}
		}
		n = 1;
		i = 0;
		j++;
	}
	
	// ROWRIGHT
	i = 0;
	j = 3;
	n = 1;
	while(i < NUM) {
		if (rowright[i] == 1) {
			add_number(i, j, NUM);
		}
		
		if (rowright[i] == 2) {
			remove_possibility(i, j, 4);
		}

		if (rowright[i] == 3) {
			remove_possibility(i, j, 4);
			remove_possibility(i, j, 3);
		}

		if (rowright[i] == NUM) {
			while (j >= 0) {
				add_number(i, j, n);
				n++;
				j--;
			}
		}
		n = 1;
		j = 3;
		i++;
	}

	// COLDOWN.
	j = 0;
	i = 3;
	n = 1;
	while(j < NUM) {
		if (coldown[j] == 1) {
			add_number(i, j, NUM);
		}
		
		if (coldown[j] == 2) {
			remove_possibility(i, j, 4);
		}

		if (coldown[j] == 3) {
			remove_possibility(i, j, 4);
			remove_possibility(i, j, 3);
		}

		if (coldown[j] == NUM) {
			while(i >= 0) {
				add_number(i, j, n);
				n++;
				i--;
			}
		}
		n = 1;
		i = 3;
		j++;
	}
	
		
	// ROWLEFT
	i = 0;
	j = 0;
	n = 1;
	while(i < NUM) {
		if (rowleft[i] == 1) {
			add_number(i, j, NUM);
		}
		
		if (rowleft[i] == 2) {
			remove_possibility(i, j, 4);
		}

		if (rowleft[i] == 3) {
			remove_possibility(i, j, 4);
			remove_possibility(i, j, 3);
		}
		if (rowleft[i] == NUM) {
			while (j <= 3) {
				add_number(i, j, n);
				n++;
				j++;
			}
		}
		n = 1;
		j = 0;
		i++;
	}
	
}

void show_board(void) {
	int i = 0;
	int j = 0;

	while(i < NUM) {
		j = 0;
		while(j < NUM) {
			printf("%d ", board[i][j].num);
			j++;
		}
		printf("\n");
		i++;
	}
}

int check_if_duplicate(int *p) {
	printf("is DUP\n");
	int i = 0;
	
	for(int j = 0; j < NUM; j++) {
		printf("j = %d %d\n", j, p[j]);
	}

	while(i < NUM) {
		if (p[i] != 1) {
			printf(" is DUP retuned 0\n");
			return 0;
		}
		p[i] = 0;
		i++;
	}
	printf("is DUP returned 1\n");
	return 1;
}

int is_solved_last(void);
int is_solved()
{
	// return 1 if solved else return 0.
	int i = 0;
	int j = 0;
	int n;
	int dup[NUM] = {0};
	
	// Check all duplicates in lines.
	while(i < NUM) {
		j = 0;
		while (j < NUM) {
			n = board[i][j].num;
			dup[n-1] += 1;
			j++;	
		}
		
		// Check duplicate if found return 0.
		if (check_if_duplicate(dup) == 0) {
			return 0;
		}
		i++;
	}
	
	printf("FIRST WHLE DONE\n");
	// Check all duplicates in columns
	i = 0;
	j = 0;
	while(j < NUM) {
		i = 0;
		while (i < NUM) {
			n = board[i][j].num;
			dup[n-1] += 1;
			i++;	
		}
		
		// Check duplicate if found return 0.
		if (check_if_duplicate(dup) == 0) {
			return 0;
		}
		j++;
	}
	
	if (is_solved_last()) {
		return 1;
	}
	else {
		return 0;
	}

}

void show_possibilities(int i, int j) {
	printf("POSSIBILITIES for %d %d\n", i, j);

	int l = 0;
	while(l < NUM) {
		printf("%d ", board[i][j].poss[l]);
		l++;
	}
	printf("\n");

}

int return_first_possibility(int i, int j) {
	int l = 0;

	while(board[i][j].poss[l] == 0) {
		l++;
	}

	return board[i][j].poss[l];
}

void copy_to_backup() {
	int i;
	int j;

	i = 0;
	while(i < NUM) {
		j = 0;
		while(j < NUM) {
			board_backup[i][j] = board[i][j];
			j++;
		}
		i++;
	}
}

void copy_to_board() {
	int i;
	int j;

	i = 0;
	while(i < NUM) {
		j = 0;
		while(j < NUM) {
			board[i][j] = board_backup[i][j];
			j++;
		}
		i++;
	}
}
void pick_one_poss(void) {
	int i;
	int j;
	int n;

	i = 0;
	j = 0;
	while(i < NUM) {
		j = 0;
		while(j < NUM) {
			if (board[i][j].num == 0) {
				n = return_first_possibility(i, j);
				remove_possibility(i, j, n);
				copy_to_backup();
				add_number(i, j, n);
			}
			j++;
		}
		i++;
	}
}

int is_solved_last() {
	int i = 0;
	int j = 0;
	int n;
	int c;

	c = 1;
	while(j < NUM) {
		n = colup[j];
		if (n == 2) {
			while (i < NUM-1) {
				if (board[i][j].num < board[i+1][j].num)
					c++;
				i++;
			}	
		}
		if (c != 2)
			return 0;
		c = 1;
		i = 0;
		if (n == 3) {
			while (i < NUM-1) {
				if (board[i][j].num < board[i+1][j].num)
					c++;
				i++;
			}
		}
		if (c != 3)
			return 0;
		j++;
	}
	
	j = 0;
	i = 3;
	c = 1;

	while(j < NUM) {
		n = coldown[j];
		if (n == 2) {
			while (i > 0) {
				if (board[i][j].num < board[i-1][j].num)
					c++;
				i--;
			}
			
		}
		if (c != 2)
			return 0;
		c = 1;
		i = 3;
		if (n == 3) {
			while (i > 0) {
			if (board[i][j].num < board[i-1][j].num)
				c++;
			i--;
			}
		}
		if (c != 3)
			return 0;
		j++;
	}
	
	i = 0;
	j = 0;
	c = 1;

	while(i < NUM) {
		n = rowleft[i];
		if (n == 2) {
			while (j < NUM - 1) {
				if (board[i][j].num < board[i][j+1].num)
					c++;
				j++;
			}
			
		}
		if (c != 2)
			return 0;
		c = 1;
		j = 0;
		if (n == 3) {
			while (j < NUM - 1) {
				if (board[i][j].num < board[i][j+1].num)
					c++;
				j++;
			}
		}
		if (c != 3)
			return 0;
		i++;
	}
	
	i = 0;
	j = 3;
	c = 1;
	while(i < NUM) {
		n = rowleft[i];
		if (n == 2) {
			while (j > 0) {
				if (board[i][j].num < board[i][j-1].num)
					c++;
				j--;
			}
			
		}
		if (c != 2)
			return 0;
		c = 1;
		j = 3;
		if (n == 3) {
			while (j > 0) {
				if (board[i][j].num < board[i][j-1].num)
					c++;
				j--;
			}
		}
		if (c != 3)
			return 0;
		i++;
	}

	return 1;
}

int main() {
	
	int i = 0;
	int j = 0;
	int p = 1;

	while(i < NUM) {
		j = 0;
		while(j < NUM) {
			board[i][j].num = 0;
			while(p <= NUM) {
				printf("setting poss\n");
				board[i][j].poss[p-1] =  p;
				p++;
			}
			p = 1;
			j++;
		}
		i++;
	}

	
	board[0][0].num = 1;
	board[0][1].num = 2;
	board[0][2].num = 3;
	board[0][3].num = 4;
	board[1][0].num = 2;
	board[1][1].num = 3;
	board[1][2].num = 4;
	board[1][3].num = 1;
	board[2][0].num = 3;
	board[2][1].num = 4;
	board[2][2].num = 1;
	board[2][3].num = 2;
	board[3][0].num = 4;
	board[3][1].num = 1;
	board[3][2].num = 2;
	board[3][3].num = 3;
	
	/*
	show_board();
	printf("IS SOLVED ; %d\n", is_solved());
	*/
	colup[0] = 4;
	colup[1] = 3;
	colup[2] = 2;
	colup[3] = 1;

	coldown[0] = 1;
	coldown[1] = 2;
	coldown[2] = 2;
	coldown[3] = 2;
	
	rowleft[0] = 4;
	rowleft[1] = 3;
	rowleft[2] = 2;
	rowleft[3] = 1;

	rowright[0] = 1;
	rowright[1] = 2;
	rowright[2] = 2;
	rowright[3] = 2;
	
	/*
	initialize_values();
	
	//add_number(1, 1, 3);
	
	int ret;

	copy_to_backup();
	while(!is_solved())
	{
		ret = fill_if_one_poss_exist();
		if (ret == 0)
		{
			copy_to_board();		
			pick_one_poss();
		}
	}
	*/

	show_board();
	printf("IS SOLVED %d\n", is_solved());
	return 0;
}
