#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int num;
	int num1;
	int num2;
	char char_num[8];
	memset(char_num, '\x00', 8);

	printf("Give me your number (Kapernak Routine) :");
	scanf("%d", &num);
	if(num<0){
		printf("can't accept negative numbers.");
		return -1;
	}

	int i, j;
	int count=0;
	int swap;

	for(i=0; i<8 && num != 0; i++){
		char_num[i] = (num % 10) + '0';
		num /= 10;
		count++;
	}
	
	printf("char_num %s\n", char_num);

	// sort char_num
	for(i=0; i<count; i++){
		for(j=i+1; j<count; j++){
			if(char_num[i] > char_num[j]){
				swap = char_num[i];
				char_num[i] = char_num[j];
				char_num[j] = swap;
			}
		}
	}

	num2 = atoi(char_num);
	// Inverse
	//
	i = 0;
	j = count-1;
	while(i<j){
		swap = char_num[i];
		char_num[i] = char_num[j];
		char_num[j] = swap;
		i++;
		j--;
	}

	num1 = atoi(char_num);

	printf("%d - %d = %d\n", num1, num2, num1 - num2);
	


	return 0;
}
