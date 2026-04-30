//Addy LaCost
//4-21-2026
//Project 10 : off-brand wordle

#include <stdio.h>
#define ROW 50
#define COL 50
void guess(int* guessnum, char twordle[][COL], int* row);
void respond(char twordle[][COL], int* row);
void checkword(char twordle[][COL], int* row, int* col);
void getword(char answer[]);
void checkanswer(char twordle[][COL], char answer[], int* row, int* correct, int* guessnum);
void win(char twordle[][COL], int* row, int* guessnum);

int main(){
	char twordle[ROW][COL], answer[COL];
	int guessnum = 1;
	int row = 0;
	int col = 0;
	int correct;
	getword(answer);
	do{
		correct = 0;
		guess(&guessnum, twordle, &row);
		checkword(twordle, &row, &col);
		checkanswer(twordle, answer, &row, &correct, &guessnum);
		if(correct == 5){
			win(twordle, &row, &guessnum);
		}
		else{
			if(guessnum != 7){
				respond(twordle, &row);
			}
			if(guessnum == 7){
				respond(twordle, &row);
				win(twordle, &row, &guessnum);
				correct = 5;
			}
		}
	}while(correct != 5);
	return 0;
}

void guess(int* guessnum, char twordle[][COL], int* row){
	if(*guessnum != 6){
		printf("GUESS %d! Enter your guess: ", *guessnum);
	}
	else{
		printf("FINAL GUESS : ");
	}
	scanf("%s", twordle[*row]);
	(*guessnum)++;
	*row = *row +2;
	
}
void respond(char twordle[][COL], int* row){
	int i;
	printf("================================\n");
	for(i = 0; i < *row; i++){
	printf("%s\n", twordle[i]);
	}
}

void checkword(char twordle[][COL], int* row, int* col){
	int letters = 0;
	do{
	letters = 0;
	*col = 0;
	while (twordle[*row - 2][*col] != '\0'){
		letters++;
		(*col)++;
	}
	if(letters != 5){
		printf("Your guess must be 5 letters long.\nPlease try again: ");
		scanf("%s", twordle[*row - 2]);
	}
	}while(letters != 5);
}
void getword(char answer[]){
	FILE* wordptr = fopen("word.txt", "r");
	int i;
	if(wordptr == NULL){
		printf("Could not open file.\n");
	}
	fscanf(wordptr, "%s", answer);
	fclose(wordptr);
	for(i = 0; answer[i] != '\0'; i++){
		if(answer[i] == '\n'){
			answer[i] = '\0';
		}
	}
}
void checkanswer(char twordle[][COL], char answer[], int* row, int* correct, int* guessnum){
	int i, j;
	for(i = 0; twordle[*row - 2][i] != '\0'; i++){
		if(twordle[*row - 2][i] == answer[i]){
			if(twordle[*row - 2][i] >= 'a' && twordle[*row - 2][i]<='z'){
				twordle[*row - 2][i] = twordle[*row - 2][i]-32;
			}
			(*correct)++;
		}
		twordle[*row - 1][i] = ' ';
		for(j = 0; answer[j] != '\0'; j++){
			if(twordle[*row - 2][i] == answer[j]){
				twordle[*row - 1][i] = '^';
			}
		}	
	}
	twordle[*row - 1][i] = '\0';
	twordle[*row][i] = '\0';
	
}

void win(char twordle[][COL], int* row, int* guessnum){
	printf("================================\n");
	printf("                %s\n", twordle[*row - 2]);
	switch(*guessnum - 1){
		case 1 :
			printf("        You won in 1 guess!\n                GOATED!\n");
			break;
		case 2:
			printf("        You won in 2 guesses!\n                Amazing!\n");
			break;
		case 3:
			printf("        You won in 3 guesses!\n                Amazing!\n");
			break;
		case 4:
			printf("        You won in 4 guesses!\n                Nice!\n");
			break;
		case 5:
			printf("        You won in 5 guesses!\n                Nice!\n");
			break;
		case 6: 
			printf("        You won in 6 guesses!\n");
			break;
		default:
			printf("You lost, better luck next time!\n");
	}
}
