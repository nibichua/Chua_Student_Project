//Shawn Nehemiah Chua
//COMPE160 Section2
//817662151
//Student Project - Snakes and Ladders

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define BLOCKS 100
#define MAX_PLAYER 2

void print_sl();
void print_board(int array[], int player[]);
char* print_tile(int tile, int position []);
int change_position(int player);


int main()
{
    FILE *fp;
    char outfile[] = "snl_data.txt";//for the file I/O - out file
    fp = fopen(outfile,"w");
    if(fp == NULL) {
        fprintf(stderr,"Can't open file for writing");
        exit(1);
    }
    int max  = 0;
    int turn = 1;
    int winner = 0;
    int i=0;
    int j=0;
    int player[2] ={0,0};
    int board[BLOCKS] = {10,9,8,7,6,5,4,3,2,1,
                        11,12,13,14,15,16,17,18,19,20,
                        30,29,28,27,26,25,24,23,22,21,
                        31,32,33,34,35,36,37,38,39,40,
                        50,49,48,47,46,45,44,43,42,41,
                        51,52,53,54,55,56,57,58,59,60,
                        70,69,68,67,66,65,64,63,62,61,
                        71,72,73,74,75,76,77,78,79,80,
                        90,89,88,87,86,85,84,83,82,81,    //in this order to print
                        91,92,93,94,95,96,97,98,99,100,}; //like the board game

    int dice = 0;
    int roll = 0;
    char *rolling =(char*)malloc(BLOCKS * sizeof(char));
    char *maxp = (char*) malloc(BLOCKS * sizeof(char));

    print_sl();
    printf("\n");
    print_board(board, player);
    printf("\n");
    printf("\t\t SNAKES\t\t LADDERS\n");
    printf("\t\t--------\t---------\n");
    printf("\t\t99 to 5  \t10 to 94\n");
    printf("\t\t91 to 77 \t71 to 92\n");
    printf("\t\t96 to 55 \t59 to 84\n");
    printf("\t\t79 to 47 \t23 to 67\n");
    printf("\t\t56 to 14 \t43 to 58\n");
    printf("\t\t51 to 1  \t 6 to 41\n");
    printf("\t\t50 to 28 \t20 to 39\n");
    printf("\t\t36 to 15 \t13 to 34\n");
    printf("\t\t22 to 3  \t 8 to 19\n");
    printf("\t\t64 to 57 \t46 to 70\n");
    printf("\n");

    while( max < 1 || max > 2){
        printf(">How many players (1 or 2)?");
        fgets(maxp,BLOCKS,stdin);
        if(strcmp(maxp,"1\n") == 0)
            max = 1;
        else if(strcmp(maxp,"2\n") == 0)
            max = 2;
        else
            printf(">Invalid Input Number Of Players\n");
        for(i=0; i<strlen(maxp);i++){    //so the next maxp is new
            *(maxp+i) = NULL;
        }
    }

    do
    {
        srand((int)time(0));
        printf(">Press \"Enter\" to roll dice or \"q\" to quit.\n");
        fgets(rolling, BLOCKS, stdin);
        dice = 0;

        if (*rolling == '\n' )
        {
            dice =((rand()%6)+1);
            player[j] = player[j] + dice;     //to change the position
            printf(">Player %d rolled a %d\n", j+1, dice);
            player[j] = change_position( player[j]);
            if(player[j] < 100 || player[j] == 100){
                printf(">Player %d is now in position %d\n", j+1, player[j]);
                print_board(board, player);
            }
            else if (player[j] > 100){
                player[j]=100;
                printf(">Player %d is now in position %d\n", j+1, player[j]);
                print_board(board, player);
            }
            printf("\n");
        }

        //if player wants to quit
        else if(strcmp(rolling,"q\n") == 0 || strcmp(rolling,"Q\n") == 0){
            printf(">GAME OVER!\n");
            break;
        }

        //so only enter and q is allowed
        else{
            printf(">Invalid input. Enter \"q\" to quit or just \"Enter\" to continue the game\n");
        }

        for(i=0; i<strlen(rolling);i++){    //so the next rolling is new
            *(rolling+i) = NULL;
        }
        if(max == 2 && player[j] < 100){
            if(j == 0)
                printf(">Next player is Player 2\n");
            else
                printf(">Next player is Player 1\n");
        }
        if((j+1) == max){
            j = 0;
            turn++;
        }
        else
            j++;

    }while(player[0] < 100 && player[1] < 100);   //once player is over 100 done

    j=0;
    if (player[0] >= 100)
    {
        printf("Player 1 WON!!!\n");
        player[0] = 100;
        print_board(board,player);
        winner = 1;
    }
    else if (player[1] >= 100)
    {
        printf("Player 2 WON!!!\n");
        player[1] = 100;
        print_board(board,player);
        winner = 2;
    }

    fprintf(fp, "\t SNAKES AND LADDERS\n\n");
    fprintf(fp, "    The game finish in %d turns\n\n", turn);
    if(winner == 1){
        fprintf(fp, " ______                __    __       _____                        \n");
        fprintf(fp, "|   __ ¯\". |          \\  \\  /  /____ |   __¯'.        /¯¯|      \n");
        fprintf(fp, "|  |  '.  )|           \\  \\/  /  ___||  |  '. )      //| |       \n");
        fprintf(fp, "|  |__'  ; |   .'¯¯¯¯/¯|\\    /| |___ |  |__.' )        | |        \n");
        fprintf(fp, "|   __ ./  |  (  .'¯'  | |  | |  ___||   __  <         | |         \n");
        fprintf(fp, "|  |    |  |__(  \"._|  | |  | | |___ |  |  '. \\        | |       \n");
        fprintf(fp, "|__     |_______| ___|_| |__| |_____||__|   |__|       |_|         \n");
        fprintf(fp, "\n");
        fprintf(fp, "\t|¯¯|    |¯¯|                      ______ |¯¯¯¯¯¯'.     |¯¯||¯¯|       \n");
        fprintf(fp, "\t|  |    |  |   |¯¯\\  |¯||¯¯\\  |¯||  ____||  |¯¯'. )    |  ||  |     \n");
        fprintf(fp, "\t |  |  |  | |¯|| \\ \\ | || \\ \\ | || |____ |  |__.' )    |  ||  |   \n");
        fprintf(fp, "\t |  |/\\|  | | || |\\ \\| || |\\ \\| ||  ____||   __  <     |__||__|  \n");
        fprintf(fp, "\t  |      |  | || | \\ \\ || | \\ \\ || |____ |  |  '. \\     __  __   \n");
        fprintf(fp, "\t  |__/\\__|  |_||_|  \\__||_|  \\__||______||__|   |__|   |__||__|    \n");

    }
    else if(winner ==2){
        fprintf(fp, " ______                __    __       _____                 __       \n");
        fprintf(fp, "|   __ ¯\". |          \\  \\  /  /____ |   __¯'.           .'¯  ¯'. \n");
        fprintf(fp, "|  |  '.  )|           \\  \\/  /  ___||  |  '. )         (        ) \n");
        fprintf(fp, "|  |__'  ; |   .'¯¯¯¯/¯|\\    /| |___ |  |__.' )         (___()   )  \n");
        fprintf(fp, "|   __ ./  |  (  .'¯'  | |  | |  ___||   __  <             .'  .'    \n");
        fprintf(fp, "|  |    |  |__(  \"._|  | |  | | |___ |  |  '. \\           /   /__  \n");
        fprintf(fp, "|__     |_______| ___|_| |__| |_____||__|   |__|         |_______|   \n");
        fprintf(fp, "\n");
        fprintf(fp, "\t|¯¯|    |¯¯|                      ______ |¯¯¯¯¯¯'.     |¯¯||¯¯|       \n");
        fprintf(fp, "\t|  |    |  |   |¯¯\\  |¯||¯¯\\  |¯||  ____||  |¯¯'. )    |  ||  |     \n");
        fprintf(fp, "\t |  |  |  | |¯|| \\ \\ | || \\ \\ | || |____ |  |__.' )    |  ||  |   \n");
        fprintf(fp, "\t |  |/\\|  | | || |\\ \\| || |\\ \\| ||  ____||   __  <     |__||__|  \n");
        fprintf(fp, "\t  |      |  | || | \\ \\ || | \\ \\ || |____ |  |  '. \\     __  __   \n");
        fprintf(fp, "\t  |__/\\__|  |_||_|  \\__||_|  \\__||______||__|   |__|   |__||__|    \n");
    }

    free(rolling);
    free(maxp);
    fclose(fp);
    return 0;
}

char* print_tile(int tile, int position [])
{

    char* tmp = (char*)malloc(sizeof(char)*5);
    if(tile == position[0] && tile == position[1])
        return "XY";
    if(tile == position [0])
        return "X";
    if(tile == position [1])
        return "Y";
    return itoa(tile,tmp,10); //make int to char
}


void print_board(int array[], int player[])
{

    int i = 0;
    int j = 0;

    printf(" =========================================================================\n ");
    for(i=99; i >= 0; i--)
    {
        if(i%10 == 0){
            printf(" | %3s  |\n", print_tile(array[i],player));
            printf(" =========================================================================\n ");
        }
        else{

            printf(" | %3s ", print_tile(array[i],player));
        }
    }

}

int change_position(int player)
{
    if(player == 99)
    {
        player = 5;
        printf(">Aww... You land on a snake.\n");
    }
    if(player == 91)
    {
        player = 77;
        printf(">Aww... You land on a snake.\n");
    }
    if(player == 96)
    {
        player = 55;
        printf(">Aww... You land on a snake.\n");
    }
    if(player == 79)
    {
        player = 47;
        printf(">Aww... You land on a snake.\n");
    }
    if(player == 56)
    {
        player = 14;
        printf(">Aww... You land on a snake.\n");
    }
    if(player == 51)
    {
        player = 1;
        printf(">Aww... You land on a snake.\n");
    }
    if(player == 50)
    {
        player = 28;
        printf(">Aww... You land on a snake.\n");
    }
    if(player == 36)
    {
        player = 15;
        printf(">Aww... You land on a snake.\n");
    }
    if(player == 22)
    {
        player = 3;
        printf(">Aww... You land on a snake.\n");
    }
    if(player == 64)
    {
        player = 57;
        printf(">Aww... You land on a snake.\n");
    }
    if(player == 99)
    {
        player = 5;
        printf(">YAY!!!! You land on a ladder!!.\n");
    }
    if(player == 99)
    {
        player = 5;
        printf(">YAY!!!! You land on a ladder!!.\n");
    }
    if(player == 10)
    {
        player = 94;
        printf(">YAY!!!! You land on a ladder!!.\n");
    }
    if(player == 71)
    {
        player = 92;
        printf(">YAY!!!! You land on a ladder!!.\n");
    }
    if(player == 59)
    {
        player =84;
        printf(">YAY!!!! You land on a ladder!!.\n");
    }
    if(player == 23)
    {
        player = 67;
        printf(">YAY!!!! You land on a ladder!!.\n");
    }
    if(player == 43)
    {
        player = 58;
        printf(">YAY!!!! You land on a ladder!!.\n");
    }
    if(player == 6)
    {
        player = 41;
        printf(">YAY!!!! You land on a ladder!!.\n");
    }
    if(player == 20)
    {
        player = 39;
        printf(">YAY!!!! You land on a ladder!!.\n");
    }
    if(player == 13)
    {
        player = 24;
        printf(">YAY!!!! You land on a ladder!!.\n");
    }
    if(player == 8)
    {
        player = 19;
        printf(">YAY!!!! You land on a ladder!!.\n");
    }
    if(player == 46)
    {
        player = 70;
        printf(">YAY!!!! You land on a ladder!!.\n");
    }

    return player;

}

print_sl()
{
    printf("         |                                            |               \n");
    printf("     __./|                     .    .'/           __./|               \n");
    printf("  ,'     |                    / |  / /         ,'     |               \n");
    printf(" ;   __  |       /|          /  | / /  _____.';   __  |               \n");
    printf(" | .'   \\| .-.  /,|  .--.'\\ /,| |, /  |  ___.|| .'   \\|            \n");
    printf(" |  '.     |  \\  ||.'     '\\  |  <'  <  |_.   |  '.                 \n");
    printf("  `.  '.   | | \\ || \\ ';  |   | |\\ \\  |  _ >   `.  '.             \n");
    printf("    `.  \\  | |\\ |\|| / .,  |   | | \\ `.| |___.'   `.  \\           \n");
    printf("     |   |\\  | \\ '|' '.; ||  /  |  \\_.'  ___ >    |   |            \n");
    printf(" |\\_;   ,/ \\ |  '-| \\   ,'|,'\\  |     |/    ' |\\_;   ,/          \n");
    printf(" |  __.'    '|       '.' | /  ',.             |  __.'                 \n");
    printf(" | /                     '/    /|             | /                     \n");
    printf(" |'              .--.'\\  .-.  /,|  .'.        |'                     \n");
    printf(" |             .'     '\\ |  \\  ||<' . `.      |                     \n");
    printf("                \\ ';  |  | | \\ || | |\\  \\                         \n");
    printf("       /|       / .,  |  | |\\ \\|| | | ', \\                         \n");
    printf("      / |      ' '.; || \\  | \\ '| | |_;  ;                       |  \n");
    printf("     /  |       \\   ,'|,'\\ |  '-|<  __ .'                    __./|  \n");
    printf("    /   |        '.' | /  '|      '                       ,'     |    \n");
    printf("   / .  |   .--.'\\   '/                 _____.' |`----.  ;   __  |   \n");
    printf("  /.'|  | .'     '\\   .'.      .'.     |  ___.|<  .-.  `,| .'   \\|  \n");
    printf("     |  |  \\ ';  |  <' . `.  <' . `.  <  |_.    | |  \\  ;|  '.      \n");
    printf("     |  |  / .,  |   | |\\  \\  | |\\  \\  |  _ >   |  `'  .' `.  '.  \n");
    printf("     |  | ' '.; ||   | | ', \\ | | ', \\ | |___.' | |\\ <      `.  \\ \n");
    printf("     |  |  \\   ,'|,' | |_;  ; | |_;  ;<  ____ ><  | \\ \\      |   | \n");
    printf("     |  |   '.' | / <  __ .' <  __ .'  |/    '  | |  \\ \\ |\\_;   ,/ \n");
    printf("     |  |_______'/___.'        '                |/    '.\\|  __.'     \n");
    printf("     |               \\                                   | /         \n");
    printf("    <  _____________  >                                  |'           \n");
    printf("     '              `/                                   |            \n");
}

