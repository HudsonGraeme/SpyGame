/*
	ICS3U

	Spencer Graham
	01/15/19
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <Windows.h>

int menu();
void welcome_screen();
void game_preferences();
void high_scores();
void help();
void play_game();
void exit_screen();
void invalidInput();
void Row_Column_Pane();
void Rounds_Pane();
void Help_Gameplay();
void Help_Preferences();
void Help_Menus();


int rows = 10,																		// The number of rows in the game, global variables which are modified in game preferences.
	cols = 10, 																		// The number of columns, also modified by the user in the preferences
	games = 3,																		// The number of rounds which are in a game, again can be modified in preferences.
	WelcomeShown = 0,
	extremeMode = 0,
	potentialPoints = 0;																// Used to determine if the welcome_screen has been shown already. 


static void setColor() {															// Sets the console color.
	system("COLOR 02");
}



void removeSpaces(char *str) {

	char *source, *dest;
	for (source = dest = str; *source != '\0'; source++) {
		*dest = *source;
		if (*dest != '\n') dest++;													//Skips over the empty spaces in the input
	}
	*dest = '\0';
}																					// This function removes unneccesary newlines which are found in the text files.

HCURSOR SetCursor(int x, int y, DWORD Std)														// Sets the cursor position on the output screen.
{

	COORD location;
	location.X = x;
	location.Y = y;																	// Creates the coordinates at which to move the cursor

	HANDLE hConsole = GetStdHandle(Std);								// Gets the console's output screen for use in setting the position of the cursor

	if (!SetConsoleCursorPosition(hConsole, location))								// Sets the cursor location and checks if the location is ok
	{
		return 1;																	// Returns a nonzero; failure
	}
	return 0;																		// Returns a sucess 
}

void fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0); 
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);									// This function emulates menu and return keys being pressed in order to force fullscreen mode.
}
void main(void)
{
	int select = 0,
		go = 1;
	if (!WelcomeShown) {
		welcome_screen();
	}

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
			//go = 0;
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
			printf("\n");
			do {
				FILE *fm = fopen("..\\Art\\MenuOptions.txt", "r");
				printf("\n\n");
				for (i = 0;i <= 46;i++) {
					fgets(currStr, 1000, fm);
					if (strchr(currStr, '\n') != NULL) {
						removeSpaces(currStr);
					}
					puts(currStr);
				}
				fclose(fm);
			} while (stop == 1);
			fclose(fp);
			fseek(stdin, 0, SEEK_END);
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
		for (i = 0;i <= 60;i++) {
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
	fseek(stdin, 0, SEEK_END);
	_getch();
}




//************** CHANGE THE GAME PREFERENCES *************************

void game_preferences()
{
	system("cls");
	char currStr[1000];
	int i = 0,
		choice = 0,
		fallback = 0;
	while (!fallback) {
		system("cls");
		do {
			FILE *fm = fopen("..\\Art\\Preferences.txt", "r");
			for (i = 0; i <= 52; i++) {
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
		fseek(stdin, 0, SEEK_END);
		scanf("%d", &choice);
		while (choice <= 0 || choice > 4) {
			invalidInput();
			system("cls");
			do {
				FILE *fm = fopen("..\\Art\\Preferences.txt", "r");
				for (i = 0; i <= 50; i++) {
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
			fseek(stdin, 0, SEEK_END);
			scanf("%d", &choice);
		}
		switch (choice) {
		case 1:
			Rounds_Pane();
			break;
		case 2:
			Row_Column_Pane();
			break;
		case 3:
			extremeMode = 1;
			printf("\nExtreme Mode has been enabled. Good luck :)");
		case 4:
			fallback = 1;
			break;
		}
	}
}


void Row_Column_Pane() {
	int tempCols,
		tempRows;
	system("cls");
	char currStr[1000];
	int i = 0;
	FILE *fm = fopen("..\\Art\\PreferencePanes.txt", "r");
	printf("\n\n");
	for (i = 0; i <= 8; i++) {
		fgets(currStr, 1000, fm);
		if (strchr(currStr, '\n') != NULL) {
			removeSpaces(currStr);

		}
		puts(currStr);
	}

	fseek(stdin, 0, SEEK_END);
	scanf("%d", &tempCols);
	while (tempCols <= 0 || tempCols >= 24) {
		printf("\nPlease enter a value between 1 and 23\n");
		scanf("%d", &tempCols);
	}
	system("cls");
	for (i = 2; i <= 12; i++) {
		fgets(currStr, 1000, fm);
		if (strchr(currStr, '\n') != NULL) {
			removeSpaces(currStr);

		}
		puts(currStr);
	}
	fclose(fm);
	scanf("%d", &tempRows);
	while (tempRows >= 30 || tempRows <= 0) {

		printf("\nPlease enter a value between 1 and 30\n");
		scanf("%d", &tempRows);
	}
	rows = tempRows;
	cols = tempCols;
	fseek(stdin, 0, SEEK_END);
	_getch();
}


void Rounds_Pane() {
	system("cls");
	char currStr[1000];
	int i = 0,
		tempRounds = 0;
	FILE *fm = fopen("..\\Art\\PreferencePanes.txt", "r");
	printf("\n\n");
	for (i = 0; i <= 24; i++) {
		fgets(currStr, 1000, fm);
		if (strchr(currStr, '\n') != NULL) {
			removeSpaces(currStr);
		}
		if (!(i <= 18)) {
		puts(currStr);
		}
	}
	fclose(fm);
	scanf("%d", &tempRounds);
	while (tempRounds > 10 || tempRounds <= 0) {

		printf("\nPlease enter a value between 1 and 10\n");
		scanf("%d", &tempRounds);
	}
	games = tempRounds;
	fseek(stdin, 0, SEEK_END);
	_getch();

}
//********************* VIEW THE HIGH SCORES ***********************

void high_scores()
{
	int i = 0, 
		flag = 1,
		lineCount = 0;
	char Users[50][100],
		currStr[100];
	int score[50];
	system("cls");
	FILE *fp = fopen("..\\Art\\HSS.Txt", "r");
	for (i = 0; i <= 24; i++) {
		char currStr[1000];
		fgets(currStr, 1000, fp);
		if (strchr(currStr, '\n') != NULL) {
			removeSpaces(currStr);
		}
			puts(currStr);
	}
	fclose(fp);
	printf("\n\n");
	FILE *fm = fopen("..\\Art\\Highscores", "r");

	while (fgets(currStr, 100, fm) != NULL) {
		lineCount++;
	}
	rewind(fm);
	for (i = 0; i <= lineCount / 2; i++) {
			if (i <= 50) {
				fscanf(fm, "%s\n", &Users[i]);
				fscanf(fm, "%d\n", &score[i]);
		}
	}

	while (flag == 1)
	{
		flag = 0;
		for (i = 0; i < lineCount / 2; i++)
		{
			if (score[i] < score[i+1]) //sort by # of credits
			{
				int tempScore = 0;
				char tempUsername[10];
				flag = 1;

				tempScore = score[i];
				score[i] = score[i + 1];
				score[i + 1] = tempScore;

				strcpy(tempUsername, Users[i]);
				
				strcpy(Users[i], Users[i + 1]);

				strcpy(Users[i + 1], tempUsername);
			}
		}
	}
	printf("\t\t\t\t\t\t\t ________________________________________________________________________________________________\n");
	printf("\t\t\t\t\t\t\t/|     Place\t|\t\t\tName\t\t\t|\t\tScore\t\t|\\\n");
	printf("\t\t\t\t\t\t\t\\|______________|_______________________________________________|_______________________________|/\n");
	if (lineCount / 2 == 0) {
		printf("\t\t\t\t\t\t\t/|\t\t\t\t\tNo records found.\t\t\t|\t\t\t\t|\\\n");
	}
	else if (lineCount / 2 < 5) {
		for (i = 0; i < lineCount / 2; i++) {
			if (i % 2 == 0) {
				printf("\t\t\t\t\t\t\t/|\t%d\t|\t\t\t%s\t\t\t|\t\t%d\t\t|\\\n", i + 1, Users[i], score[i]);
			}
			else {
				printf("\t\t\t\t\t\t\t\\|\t%d\t|\t\t\t%s\t\t\t|\t\t%d\t\t|/\n", i + 1, Users[i], score[i]);
			}
		}
	}
	else {
		for (i = 0; i < 5; i++) {
			if (i % 2 == 0) {
				printf("\t\t\t\t\t\t\t/|\t%d\t|\t\t\t%s\t\t\t|\t\t%d\t\t|\\\n", i + 1, Users[i], score[i]);
			}
			else {
				printf("\t\t\t\t\t\t\t\\|\t%d\t|\t\t\t%s\t\t\t|\t\t%d\t\t|/\n", i + 1, Users[i], score[i]);
			}
		}
	}
	printf("\t\t\t\t\t\t\t\\|______________|_______________________________________________|_______________________________|/\n");
	_getch();
}


//**************************** HELP **********************************

void help()
{
	system("cls");
	char currStr[1000];
	int i = 0,
		choice = 0,
		fallback = 0;
	while (!fallback) {
		system("cls");
		FILE *fm = fopen("..\\Art\\HelpScreen.txt", "r");
		printf("\n\n");
		for (i = 0; i <= 54; i++) {
			fgets(currStr, 1000, fm);
			if (strchr(currStr, '\n') != NULL) {
				removeSpaces(currStr);
			}
			puts(currStr);
		}
		fclose(fm);
		fseek(stdin, 0, SEEK_END);
		scanf("%d", &choice);

		while (choice <= 0 || choice > 4) {
			printf("\nPlease enter a valid choice between 1 and 4.\n");
			scanf("%d", &choice);
		}
		system("cls");
		switch (choice) {
		case 1:
			Help_Gameplay();
			break;
		case 2:
			Help_Preferences();
			break;
		case 3:
			Help_Menus();
			break;
		case 4:
			fallback = 1;
			break;
		}
	}
}

void Help_Gameplay() {
	char currStr[1000];
	int i = 0;
	FILE *fp = fopen("..\\Art\\HelpScreen.txt", "r");
	printf("\n\n");
	for (i = 0; i <= 23; i++) {
		fgets(currStr, 1000, fp);
		if (strchr(currStr, '\n') != NULL) {
			removeSpaces(currStr);
		}
		puts(currStr);
	}
	fclose(fp);
	FILE *fm = fopen("..\\Art\\HelpPanes.txt", "r");
	printf("\n\n");
	for (i = 0; i <= 15; i++) {
		fgets(currStr, 1000, fm);
		if (strchr(currStr, '\n') != NULL) {
			removeSpaces(currStr);
		}
		puts(currStr);
	}
	_getch();
}


void Help_Preferences() {
	char currStr[1000];
	int i = 0;
	FILE *fp = fopen("..\\Art\\HelpScreen.txt", "r");
	printf("\n\n");
	for (i = 0; i <= 23; i++) {
		fgets(currStr, 1000, fp);
		if (strchr(currStr, '\n') != NULL) {
			removeSpaces(currStr);
		}
		puts(currStr);
	}
	fclose(fp);
	FILE *fm = fopen("..\\Art\\HelpPanes.txt", "r");
	printf("\n\n");
	for (i = 0; i <= 34; i++) {
		fgets(currStr, 1000, fm);
		if (strchr(currStr, '\n') != NULL) {
			removeSpaces(currStr);
		}
		if (i > 15 && i < 32) {
			puts(currStr);
		}
	}
	_getch();
}

void Help_Menus() {
	char currStr[1000];
	int i = 0;
	FILE *fp = fopen("..\\Art\\HelpScreen.txt", "r");
	printf("\n\n");
	for (i = 0; i <= 23; i++) {
		fgets(currStr, 1000, fp);
		if (strchr(currStr, '\n') != NULL) {
			removeSpaces(currStr);
		}
		puts(currStr);
	}
	fclose(fp);
	FILE *fm = fopen("..\\Art\\HelpPanes.txt", "r");
	printf("\n\n");
	for (i = 0; i <= 46; i++) {
		fgets(currStr, 1000, fm);
		if (strchr(currStr, '\n') != NULL) {
			removeSpaces(currStr);
		}
		if (i >= 32 && i < 44) {
			puts(currStr);
		}
	}
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
	fseek(stdin, 0, SEEK_END);
	scanf("%c", &choice);

	while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y') {
		invalidInput();
		fseek(stdin, 0, SEEK_END);
		_getch();
		system("cls");
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
		fseek(stdin, 0, SEEK_END);
		choice = getchar();
	}

	if (choice == 'Y' || choice == 'y') {
		exit(0);
	}
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
	fseek(stdin, 0, SEEK_END);
	_getch();
}







//**************************** GAME **************************



void play_game()
{

	int count = 0,
		win = 0,
		actualpoints = 0;
	potentialPoints = rows * cols* games;
	actualpoints = potentialPoints;
	while (count < games) {
		win = 0;
		int attempts = 0;
		int  randy, randx, row, column;
		if (!extremeMode) {
			unsigned int seed = (unsigned int)time(NULL);
			srand(seed);
			randx = rand() % cols;
			randy = rand() % rows;
		}
		system("cls");
		printf("\n\n\n");
		for (row = 0; row <= rows; row++) {
			if (extremeMode) {
				unsigned int seed = (unsigned int)time(NULL);
				srand(seed);
				randx = rand() % cols;
				randy = rand() % rows;
			}
			printf("\t\t\t");
			if (row != 0 && row < 10) {
				printf("%d ", row);
			}
			else if (row > 9) {
				printf("%d ", row);
			}
			for (column = 0; column < cols; column++) {
				printf("\t");
				if (row == 0) {
					printf("%d ", column + 1);
				}
				else {
					printf("X ");
				}
			}
			printf("\n\n");

		}
		int escape = 0;
		while (!win && !escape) {
			SetCursor(30,0, STD_OUTPUT_HANDLE);
			printf("Score: %d", actualpoints);
			
			int x = 0, y = 0, i = 0;
			SetCursor(0, (rows + 2) * 2, STD_OUTPUT_HANDLE);
			for (i = 0; i <= 20; i++) {
				printf("\33[2K\n", 67);
			}
			SetCursor(0, (rows + 4) * 2, STD_OUTPUT_HANDLE);
			printf("Please enter your coordinates below. (x,y)\n");
			fseek(stdin, 0, SEEK_END);
			scanf("%d,%d", &x, &y);
			if (x == 0 && y == 0) {
				escape = 1;
				return;
			}
			else {
				while ((x > cols || y > rows || x <= 0 || y <= 0 || isalpha(x) || isalpha(y)) && !(x == 0 && y == 0)) {
					printf("Please enter a valid row/column.\n Valid entries for rows: 1-%d, valid entries for columns: 1-%d.\n", rows, cols);
					printf("Please enter your coordinates below. (x,y)\n");
					fseek(stdin, 0, SEEK_END);
					scanf("%d,%d", &x, &y);
				}
				if (x == 0 && y == 0) {
					escape = 1;
					return;
				}
				else {
					x -= 1;
					y -= 1;
					if (!extremeMode) {
						if (x == randx && y == randy) {
							printf("You found the spy!");
							int winPointX,
								winPointY;
							winPointX = x * 8 + 32;
							winPointY = y * 2 + 5;
							SetCursor(winPointX - 2, winPointY, STD_OUTPUT_HANDLE);
							printf("--+--");
							SetCursor(winPointX - 1, winPointY - 1, STD_OUTPUT_HANDLE);
							printf("\\|/");
							SetCursor(winPointX - 1, winPointY + 1, STD_OUTPUT_HANDLE);
							printf("/|\\");
							win = 1;
							if (actualpoints > 0) {
								actualpoints -= 5 * attempts;
							}
						}
						else {
							printf("Nothing there!\n");
							if (x > randx) {
								printf("Go Left\n");
							}
							else if (x < randx) {
								printf("Go Right\n");
							}
							if (y > randy) {
								printf("Go Up\n");
							}
							else if (y < randy) {
								printf("Go Down\n");
							}

							SetCursor(x * 8 + 32, y * 2 + 5, STD_OUTPUT_HANDLE);
							printf("-");
						}
					}
					else {
						if ((x == randx || x == randx+1 || x == randx-1) && (y == randy || y == randy+1 || y == randy-1)) {
							printf("You found the spy!");

							int Xpoints[3] = { randx * 8 + 32, (randx - 1) * 8 + 32, (randx + 1) * 8 + 32};
							int Ypoints[3] = { randy * 2 + 5 , (randy - 1) * 2 + 5, (randy + 1) * 2 + 5};
							for (i = 0; i < 3; i++) {
								int control = Xpoints[i];
								int x = 0;
								for (x = 0; x < 3; x++) {
									SetCursor(control - 1, Ypoints[x], STD_OUTPUT_HANDLE);
									printf("(+)");
									SetCursor(control - 1, Ypoints[x] + 1, STD_OUTPUT_HANDLE);
									printf("/|\\");
									SetCursor(control - 1, Ypoints[x] - 1, STD_OUTPUT_HANDLE);
									printf("\\|/");
								}
								
							}
							win = 1;
							if (actualpoints > 0) {
								actualpoints -= 5 * attempts;
							}
						}
						else {
							printf("Nothing there!\n");

							SetCursor(x * 8 + 32, y * 2 + 5, STD_OUTPUT_HANDLE);
							printf("-");
						}
					}
				}
				fseek(stdin, 0, SEEK_END);
				_getch();
				attempts++;
			}
		}
		count++;
	}
	system("cls");
	char username[20];
	printf("Please enter your desired username below:\n");
	scanf("%s", username);
	FILE *fm = fopen("..\\Art\\Highscores", "a");
	char tempStr[100];
	fprintf(fm, "\n%s", username);
	fprintf(fm, "\n%d", actualpoints);
	fclose(fm);
}