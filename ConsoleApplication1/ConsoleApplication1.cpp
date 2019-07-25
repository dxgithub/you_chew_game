// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>

#define SIZE 5
#define LENGTH 1024

int sortScore(int diceScore[], int size);
void calculateScore(int diceScore[], int size);
int assert_intput(int in[SIZE]);
int calculate_same_face_score(int diceScore[]);
int check_sequence_score(int diceScore[]);
int sum(int diceScore[]);

int main(void) {
	int countOfSameNumber = 0;
	int score = 0;
	int condition = 0;
	//explain what different number represents
	int i = 0;
	int diceScore[SIZE] = { 0 };
	while (i < SIZE) {
		scanf_s("%d", &diceScore[i]);
		i++;
	}
	if (i < 5)
	{
		printf("Less than 5 inputs, invalid... \n");
		return 0;
	}
	/*need to find a way to simply this*/
	if (assert_intput(diceScore)==0)
	{
		printf("Invalid input: 5 integers 1..9 must be supplied. \n");
	}
	else {
		sortScore(diceScore, SIZE);
		calculateScore(diceScore, SIZE);
		
	}
	return 0;
}

int assert_intput(int in[SIZE])
{
	int  i = 0;
	int flag = 0;
	for (i = 0; i < SIZE; i++)
	{
		if(in[i]<1 || in[i] > 9)
		{
			flag = 0;
			return flag;
		}
	}
	flag = 1;
	return flag;
}
//Arrange scores from the smallest to the biggest
int sortScore(int diceScore[], int size) {
	int j = 0;
	int d = 0;
	int swap = 0;
	for (j = 0; j < SIZE;j++) {
		for (d = j+1; d < SIZE; d++) {
			if (diceScore[j] > diceScore[d]) {
				swap = diceScore[j];
				diceScore[j] = diceScore[d];
				diceScore[d] = swap;
			}
		}
		//printf("%d", diceScore[j]);
	}
	//printf("sorted score : ");
	//for (j = 0; j < SIZE; j++) printf("%d", diceScore[j]);
	//printf("\n");
	return 0;
}

//Calculating scores under different condition
void calculateScore(int diceScore[], int size) {
	int condition = 0;
	int score = 0;
	int i = 0;
	score = check_sequence_score(diceScore);
	if (score > 0)
	{
		//printf("sequence score.");
		return ;
	}
	else
	{
		score = calculate_same_face_score(diceScore);
		if (score > 0)
		{
			//printf("same face score.");
			return ;
		}
		else
		{
			//printf("Any same face score.");
			while (i < SIZE) {
				score = score + diceScore[i];
				i++;
			}
			printf("You Chew score is %d:sum  \n", score);
			return ;
		}
	}
}

int calculate_same_face_score(int diceScore[])
{
	int j = 0;
	int d = 0;
	int same_face_num = 0;
	int result[11] = { 0 };
	int score = 0;
	int two_same_cnt = 0;
	int three_same_cnt = 0;
	int buf = 0;
	int two_same_buff[3] = {0};
	int s = 0;
	s = sum(diceScore);
	for (j = 0; j < SIZE; j++) {
		result[diceScore[j]]++;
	}
	for (j = 1; j < 11; j++)
	{
		if (result[j] == 2)
		{
			score = score + 2 * j;
			two_same_buff[two_same_cnt] = j;
			two_same_cnt++;
		}
		else if (result[j] == 3)
		{
			score = score + 3 * j;
			buf = j;
			three_same_cnt++;
		}
		else if (result[j] == 4)
		{
			score = score + 4 * j;
			score = score + 16;
			buf = j;
			if (score <= s)
			{
				score = s;
				printf("You Chew score is %d:sum.  \n", score, buf);
				
			}
			else
			{
				printf("You Chew score is %d: four %d's  \n", score, buf);
			}

			
		}
		else if (result[j] == 5)
		{
			score = score + 5 * j;
			score = score + 17;
			
			buf = j;
			if (score <= s)
			{
				score = s;
				printf("You Chew score is %d: sum.  \n", score);
			}
			else
			{
				printf("You Chew score is %d: five %d's  \n", score, buf);
			}
			
		}
	}
	if (two_same_cnt == 2)
	{
		score = score + 13;
		if (score <= s)
		{
			score = s;
			printf("You Chew score is %d: sum.  \n", score);
		}
		else
		{
			printf("You Chew score is %d: pair of %d's and pair of %d's  \n", score, two_same_buff[0], two_same_buff[1]);
		}
	}
	else if (two_same_cnt == 1 && three_same_cnt == 1)
	{
		score = score + 15;
		if (score < s)
		{
			score = s;
			printf("You Chew score is %d: sum.  \n", score);
		}
		else
		{
			printf("You Chew score is %d: pair of %d's and three %d's  \n", score, two_same_buff[0], buf);
		}
		

	}
	else if (two_same_cnt == 1)
	{
		score = score + 14;
		if (score < s) {
			score = s;
			printf("You Chew score is %d: sum.  \n", score);
		}
		else
		{
			printf("You Chew score is %d: pair of %d's  \n", score, two_same_buff[0]);
		}
		
	}
	else if (three_same_cnt == 1)
	{
		score = score + 15;
		if (score < s)
		{
			score = s;
			printf("You Chew score is %d: sum. \n", score);
		}
		else
		{
			printf("You Chew score is %d: three %d's \n", score, buf);
		}
		
	}
	return score;

}

int check_sequence_score(int diceScore[])
{
	int j = 0;
	int d = 0;
	int sequence_cnt = 0;
	int result[11] = {0};
	int cnt = 0;
	int score = 0;
	int s = 0;
	s = sum(diceScore);
	for (j = 0; j < SIZE; j++) {
			result[diceScore[j]]++;
		}
	//printf("Sequence score map: ");
	//for (j = 0; j < 11; j++)
	//{
	//	printf(" %d ", result[j]);
	//}
	//5 sequential dice faces
	for (j = 0; j <= 6; j++)
	{
		cnt = 0;
		for (d = j; d < j + 5; d++)
		{
			if (d > 11)
				break;
			if (result[d] > 0)
				cnt++;
		}
		if (cnt >= 5)
		{
			score=37+d - 1;
			if (score <= s) 
			{
				score = s;
				printf("You Chew score is %d: sum. \n", score);
			}
			else {
				printf("You Chew score is %d: long sequence %d..%d  \n", score, d - 5, d - 1);
			}
			
			return score;
		}
	}
	for (j = 0; j <= 7; j++)
	{
		cnt = 0;
		for (d = j; d < j + 4; d++)
		{
			if (d > 11)
				break;
			if (result[d] > 0)
				cnt++;
		}
		if (cnt >= 4)
		{
			score = 25 + d - 1;
			if (score <= s) 
			{
				score = s;
				printf("You Chew score is %d: sum  \n", score);
			}
			else {
				printf("You Chew score is %d: short sequence %d..%d  \n", score, d - 4, d - 1);
			}
			
			return score;
		}
	}
	return 0;
}
int sum(int diceScore[])
{
	int ss = 0;
	int j = 0;
	for (j = 0; j < SIZE; j++) {
		ss = ss + diceScore[j];
	}
	return ss;

}



