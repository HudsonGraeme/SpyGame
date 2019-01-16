/*
	ICS3U

	Spencer Graham
	01/15/19
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <Windows.h>

int menu();
void welcome_screen();
void game_preferences();
void high_scores();
void help();
void play_game();
void exit_screen();
void invalidInput();


int rows = 10,																		// The number of rows in the game, global variables which are modified in game preferences.
	cols = 10, 																		// The number of columns, also modified by the user in the preferences
	games = 3,																		// The number of rounds which are in a game, again can be modified in preferences.
	WelcomeShown = 0;																// Used to determine if the welcome_screen has been shown already. 


static void setColor() { // Sets the console color.
	system("COLOR 02");
}



void removeSpaces(char *str) {

	char *source, *dest;
	for (source = dest = str; *source != '\0'; source++) {
		*dest = *source;
		if (*dest != '\n') dest++; //Skips over the empty spaces in the input
	}
	*dest = '\0';
} // This function removes unneccesary newlines which are found in the text files.

int SetCursor(int x, int y) // Sets the cursor position on the output screen.
{

	COORD location;
	location.X = x;
	location.Y = y; // Creates the coordinates at which to move the cursor

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Gets the console's output screen for use in setting the position of the cursor

	if (!SetConsoleCursorPosition(hConsole, location)) // Sets the cursor location and checks if the location is ok
	{
		return 1; // Returns a nonzero; failure
	}
	return 0; // Retruns a sucess 
}

void fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0); 
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); // This function emulates menu and return keys being pressed in order to force fullscreen mode.
}
void main(void)
{
	int select = 0,
		go = 1;

	welcome_screen();

	while (go == 1)
	{
		select = menu();
		switch (select)
		{
		case 1:
			welcome_screen();
			break;
		case 2:
			play_game();
			break;
		case 3:
			game_preferences();
			break;
		case 4:
			high_scores();
			break;
		case 5:
			help();
			break;
		case 6:
			exit_screen();
			go = 0;
			break;
		}
	}
}



//************************* MENU ************************************

int menu()
{
	int choice;

	do
	{

		system("cls");

		int i = 0,
			stop = 0;
		char currStr[1000];
		


			FILE *fp = fopen("..\\Art\\MainMenu.txt", "r");
			for (i = 0;i <= 10;i++) {
				fgets(currStr, 1000, fp);
				if (strchr(currStr, '\n') != NULL) {
					removeSpaces(currStr);
				}
				puts(currStr);
			}
			printf("\n\n\n");
			do {
				FILE *fm = fopen("..\\Art\\MenuOptions.txt", "r");
				printf("\n\n");
				for (i = 0;i <= 7;i++) {
					fgets(currStr, 1000, fm);
					if (strchr(currStr, '\n') != NULL) {
						removeSpaces(currStr);
						
					}
					puts(currStr);
				}
				fclose(fm);
			} while (stop == 1);
			fclose(fp);
			fflush(stdin);
			scanf("%d", &choice);
			system("cls");
		if (choice < 1 || choice > 6)
		{
			printf("Incorrect input. Press any key to continue..\n");
			_getch();
		}
	} while (choice < 1 || choice > 6);

	return choice;
}



//************************* WELCOME SCREEN ************************

void welcome_screen()
{
	if (WelcomeShown == 0) {
		fullscreen();
		WelcomeShown = 1;
	}
	char currStr[1000];
	int i = 0;
	system("cls");
	setColor();
	do {
		FILE *fm = fopen("..\\Art\\WelcomeScreen.txt", "r");
		for (i = 0;i <= 50;i++) {
			fgets(currStr, 1000, fm);
			if (strchr(currStr, '\n') != NULL) {
				removeSpaces(currStr);
			}
			if (i == 1) {
				system("cls");
			}
			puts(currStr);
		}
		fclose(fm);
	} while (1 == 0);
	//while (getchar() != '\n');
	fflush(stdin);
	//_getch();
	_getch();
}




//************** CHANGE THE GAME PREFERENCES *************************

void game_preferences()
{
	system("cls");
	printf("This function will change the game preferences.\n");
	_getch();
}

//********************* VIEW THE HIGH SCORES *************************

void high_scores()
{
	int i = 0;
	while (1==1) {
		char one[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
		char two[] = { '1','2','3','4','5','6','7','8','9' };
		for (i = 0;i <= 8;i++) {
			char col[2];
			strcpy(one[i], col[0]);
			strcpy(two[i], col[1]);
			char str[8] = "COLOR";
			strcpy(col[0],str[6]);
			strcpy(col[1],str[7]);
			system(str);
		}
	}
	system("cls");
	printf("_______________________________________________________|____________________________\n");
	for (i = 0;i <= 5;i++) {
		double UserScore = 0.0;
		char UserName[100];


		printf("|\t%s\t\t|\t%lf\t|", UserName, UserScore);
	}

	_getch();
}


//**************************** HELP **********************************

void help()
{
	system("cls");
	printf("This function will display the Help Screen.\n");
	_getch();
}


//**************************** EXIT SCREEN **************************

void exit_screen()
{
	system("cls");
	char currStr[1000],
		choice = '\0';
	
	int i = 0;
	FILE *fm = fopen("..\\Art\\ExitScreen.txt", "r");
	printf("\n\n");
	for (i = 0; i <= 43; i++) {
		fgets(currStr, 1000, fm);
		if (strchr(currStr, '\n') != NULL) {
			removeSpaces(currStr);

		}
		puts(currStr);
	}
	fclose(fm);
	while (getchar() != '\n');
	choice = getchar();

	while (choice != 'n' || choice != 'N' && choice != 'y' || choice != 'Y') {
		invalidInput();
		int i = 0;
		FILE *fm = fopen("..\\Art\\ExitScreen.txt", "r");
		printf("\n\n");
		for (i = 0; i <= 43; i++) {
			fgets(currStr, 1000, fm);
			if (strchr(currStr, '\n') != NULL) {
				removeSpaces(currStr);

			}
			puts(currStr);
		}
		fclose(fm);
		fflush(stdin);
		choice = getchar();
	}

	_getch();
}

void invalidInput() {
	system("cls");
	char currStr[1000];
	int i = 0;
	FILE *fm = fopen("..\\Art\\InvalidInput.txt", "r");
	printf("\n\n");
	for (i = 0; i <= 33; i++) {
		fgets(currStr, 1000, fm);
		if (strchr(currStr, '\n') != NULL) {
			removeSpaces(currStr);

		}
		puts(currStr);
	}
	fclose(fm);
	fflush(stdin);
	_getch();
}







//**************************** GAME **************************



void play_game()
{
	int count = 0,
		win = 0;
	while (count < games) {
		win = 0;
		int  randy, randx;
		unsigned int seed = (unsigned int)time(NULL);
		srand(seed);
		randx = rand() % rows;
		randy = rand() % cols;
		while (win == 0) {
			int row, column, x = 0, y = 0;

			system("cls");
			setColor();
			for (row = 0;row <= rows;row++) {
				if (row != 0 && row < 10) {
					printf(" %d ", row);
				}
				else if (row > 9) {
					printf("%d ", row);
				}
				for (column = 0;column < cols;column++) {
					if (row == 0) {
						if (column == 0) {
							printf("   ");
						}
						printf("%d ", column + 1);
					}
					else {
						printf("X ");
					}
				}
				printf("\n");

			}
			printf("Please enter your coordinates below. (x,y)\n");
			while (getchar() != '\n');
			scanf("%d,%d", &x, &y);
			x -= 1;
			y -= 1;
			while (x > cols || y > rows || x < 0 || y < 0) {
				printf("Please enter a valid row/column.\n Valid entries for rows: 0-%d, valid entries for columns: 0-%d.\n", rows, cols);
				printf("Please enter your coordinates below. (x,y)\n");
				scanf("%d,%d", x, y);
			}

			if (x == randx && y == randy) {
				SetConsoleCursorPosition(x, y);
				printf("win in %d tries", count);
				win = 1;
			}
			else {
				printf("you lose, %d %d", randx, randy);
			}
			fflush(stdin);
			_getch();
			_getch();
			count++;
		}
	}
}