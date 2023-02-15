#include <stdio.h>
#include <time.h> 
#include <stdlib.h> 

int game_Map[5][6];
char* food_Name[15];
int checkFood[5][6];
int wrong_Answer_Count = 0;

void settings();
void set_Food();
void set_Food_Name();
void game_Set_Up();
int get_Empty_Pos();
int conv_Pos_X(int x);
int conv_Pos_Y(int y);
void print_Foods();
void print_Question();
int find_All();
int get_Select1();
int get_Select2();
void game_Settings();



int main(void)
{
    settings();
    while (1)
    {
        game_Settings();
        int select1 = get_Select1();
        int select2 = get_Select2();
        if (select1 == select2)
        {
            continue;
        }

        int first_Card_X = conv_Pos_X(select1);
        int first_Card_Y = conv_Pos_Y(select1);
        int second_Card_X = conv_Pos_X(select2);
        int second_Card_Y = conv_Pos_Y(select2);
        //if select 1 and select 2 is matching, update the game sheet. 
        if ((checkFood[first_Card_X][first_Card_Y] == 0
            && checkFood[second_Card_X][second_Card_Y] == 0)
            && (game_Map[first_Card_X][first_Card_Y] ==
                game_Map[second_Card_X][second_Card_Y]))
        {
            printf("\nGreat!! They are matching! The hidden fruit was a ");
            printf(food_Name[game_Map[first_Card_X][first_Card_Y]]);
            printf("\n");
            //change value from 0 to 1 to show fruit in the game sheet.
            checkFood[first_Card_X][first_Card_Y] = 1;
            checkFood[second_Card_X][second_Card_Y] = 1;
        }
        else
        {   // if two cards are not matching, then show the player what he/she picked
            printf("two cards are not matching.\n");
            printf("You picked: \n");
            printf("First number %d : %s\n", select1, food_Name[game_Map[first_Card_X][first_Card_Y]]);
            printf("Second number %d : %s\n", select2, food_Name[game_Map[second_Card_X][second_Card_Y]]);
            printf("\n");
            //count number of wrong answer
            wrong_Answer_Count++;
        }
        // check whether there is hidden fruit in the game sheet or not
        if (find_All() == 1)
        {
            printf("\n********Congratulation. You found all fruits ********\n");
            printf("Number of times you missed in this game: %d \n", wrong_Answer_Count);
            break;
        }
    }
    printf("\n\n Thank you for playing DK's card fliping game.\n\n");
    return 0;
}


//set up basic game components
void settings()
{
    printf("\n\n***********************Welcome to Dk's flipping card game***********************\n\n");
    srand(time(NULL));
    set_Food();
    set_Food_Name();
    game_Set_Up();
}



void set_Food()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            game_Map[i][j] = -1;
        }
    }
}

void set_Food_Name()
{
    food_Name[0] = "Banana";
    food_Name[1] = "Peach";
    food_Name[2] = "Blueberry";
    food_Name[3] = "Pineapple";
    food_Name[4] = "Apple";
    food_Name[5] = "Orange";
    food_Name[6] = "Guava";
    food_Name[7] = "Cherry";
    food_Name[8] = "Strawberry";
    food_Name[9] = "Lemon";
    food_Name[10] = "Melon";
    food_Name[11] = "Plum";
    food_Name[12] = "Grape";
    food_Name[13] = "Mango";
    food_Name[14] = "Persimmon";
}


void game_Set_Up()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 2; j++)
        {   //shuffle pairs of number that represent fruits 
            int pos = get_Empty_Pos();
            int x = conv_Pos_X(pos);
            int y = conv_Pos_Y(pos);
            game_Map[x][y] = i;
        }
    }
}


int get_Empty_Pos()
{
    while (1)
    {   //if maps x row, y column is -1: yet changed, then we know this one is empty element.
        int randPos = rand() % 30;
        int x = conv_Pos_X(randPos);
        int y = conv_Pos_Y(randPos);
        if (game_Map[x][y] == -1)
        {
            return randPos;
        }
    }
    return 0;
}

//calculate row number
int conv_Pos_X(int x)
{
    return x / 6;
}

//calculate column number
int conv_Pos_Y(int y)
{
    return y % 6;
}


void print_Foods()
{   // answer sheet
    printf("\n******************************** Answer sheet. *********************************\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            printf("%12s", food_Name[game_Map[i][j]]);
        }
        printf("\n");
    }
    printf("********************************************************************************\n");
}


void print_Question()
{   //game sheet. Update the map if user finds matching cards.
    printf("\n********************************* Game sheet ***********************************\n");
    int seq = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (checkFood[i][j] != 0)
            {
                printf("%12s", food_Name[game_Map[i][j]]);
            }
            else {
                printf("%12d", seq);
            }
            seq++;
        }
        printf("\n");
    }
    printf("********************************************************************************\n");
}

//setting up the game base
void game_Settings()
{
    print_Foods(); // show answer sheet. 
    print_Question(); // this will automatically update the map if user get correct answers
    printf("\nPlease pick two numbers between 0 and 29\n");
}
int get_Select1()
{// get your first pick
    int select1 = 0;
    printf("\nFirst number: ");
    scanf_s("%d", &select1);
    return select1;
}
int get_Select2()
{// get your second pick
    int select2 = 0;
    printf("Second number: ");
    scanf_s("%d", &select2);
    return select2;
}


int find_All()
{   // if player found all matching fruits in the map, game is over
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (checkFood[i][j] == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}