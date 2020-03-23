#include <stdio.h>
#include <string.h>

#define NAME_MAX 32 // 2 extra bytes to accomodate '\0' and '\n', so remember to subtract 2 during char* length checks
#define NUL '\0' // used to "nullify" a char

typedef enum { false, true } bool;

struct Settings {
	int boardX;
	int boardY;
	char* player1;
	char* player2;
	bool solo;
};

void setup(struct Settings *settings);

static inline void cleanStdin()
{
	char c = NUL;
	while ((c = getchar()) != '\n' && c != EOF) {
		// Do nothing until input buffer is fully flushed. 
	}
}

int main(int argc, char **argv) {
	system("cls");

	struct Settings* settings = (struct Settings*) malloc(sizeof(struct Settings));
	settings->boardX = 9;
	settings->boardY = 7;
	settings->player1 = (char*)malloc(sizeof(char) * NAME_MAX);
	settings->player2 = (char*)malloc(sizeof(char) * NAME_MAX);

	printf("Welcome to Connect 4! Reproduced virtually using C by Taylor Courtney - 40398643\nTo begin, select either:\n\n 1 - how it works\n 2 - change board size (currently %dx%d)\n 3 - start Player versus Player\n 4 - start Player versus AI\n 5 - quit", settings->boardX, settings->boardY);
	
	//mainmenu:
	int option = 0;
	while (option == 0) {
		settings->solo = false;
		printf("\n\nWhat would you like to do?\n> ");
		option = validateOption(1, 5);
		switch (option) {
			case 1:
				printf("\nConnect 4 is a rather simple game. Both users take a turn each selecting a column\nwhich they would like to drop their token (player 1 = O, player 2 = X) into next.\n\nThis continues until one player has connected 4 of their tokens in a row either\nhorizontally, vertically or diagonally.", settings->boardX, settings->boardY);
				//goto mainmenu;
				option = 0;
				break;

			case 2:
				printf("\nPlease enter the width (amount of columns) you want to play with\n> ");
				settings->boardX = validateOption(3, 12);
				printf("\nPlease enter the height (amount of rows) you want to play with\n> ");
				settings->boardY = validateOption(3, 12);
				printf("\nBoard dimensions changed successfully to %dx%d", settings->boardX, settings->boardY);
				//goto mainmenu;
				option = 0;
				break;

			case 3:
				setup(settings);
				//goto mainmenu;
				option = 0;
				break;

			case 4:
				settings->solo = true;
				setup(settings);
				//goto mainmenu;
				option = 0;
				break;

			case 5:
				break;
		}
	}
	free(settings->player1);
	free(settings->player2);
	free(settings);
	system("cls");
	printf("Connect 4 closed, goodbye!\n");
	return 0;
}

int validateOption(int min, int max) {
	bool valid = false;
	int num;
	while (!valid) { // still causes an infinite loop if a char is entered
		char term;
		num = 0;
		if (scanf("%d%c", &num, &term) != 2 || term != '\n' || !(num >= min && num <= max)) {
			printf("\n! invalid input: please re-enter an number between %d and %d\n> ", min, max);
			//cleanStdin();
		} else
			valid = true;
	}
	return num;
}

void removeExcessSpaces(char* str) { // used to remove preceeding and exceeding spaces from strings
	int i, x;
	for (i = x = 0; str[i]; ++i)
		if (!isspace(str[i]) || (i > 0 && !isspace(str[i - 1])))
			str[x++] = str[i];
	if (isspace(str[x - 1]))
		str[x - 1] = '\0';
	else
		str[x] = '\0';
}

void getName(char** player) { // dynamically resizes the allocation of the player name char array based on the input
	char* buffer = (char*)malloc(sizeof(char) * NAME_MAX);
	memset(buffer, NUL, NAME_MAX);

	char* input = NULL;
	while (input == NULL) {
		input = fgets(buffer, NAME_MAX, stdin);
		size_t bufLen = strlen(buffer);
		removeExcessSpaces(buffer);

		if (buffer == 0 || buffer[0] == '\0') {
			printf("\n! name empty, please enter one\n> ");
			input = NULL;
		}
		
		else if (buffer[bufLen - 1] != '\n') {
			printf("\n! name too long, please re-enter\n> ");
			cleanStdin();
			input = NULL;
		}
		else {
			if (input[bufLen - 1] == '\n') {
				input[bufLen - 1] = '\0';
				bufLen--;
			}
			removeExcessSpaces(input);

			if (bufLen > sizeof(*player))
				*player = (char*)realloc(*player, sizeof(char) * bufLen);

			strcpy(*player, input);
		}
	}
	free(buffer);
}

void setup(struct Settings *settings) {
	printf("\nPlayer 1, please enter your name\n> ");
	getName(&(settings)->player1);

	if (settings->solo) {
		settings->player2 = "Bot";
		printf("\nWelcome %s!", settings->player1);
	}
	else {
		printf("\nPlayer 2, please enter your name\n> ");
		getName(&(settings)->player2);
		printf("\nWelcome %s and %s!", settings->player1, settings->player2);
	}
	//*settings = (struct Settings*)realloc(*settings, sizeof(int) * 2 + sizeof(bool) + sizeof(char) * strlen(settings->player1) + sizeof(char) * strlen(settings->player2));
}