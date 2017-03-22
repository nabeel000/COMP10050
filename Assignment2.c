//
//  Assignment2.c
//  Software Engineering Assignment by Nabeel Mirza and Simon Garland
//
//  Created by Nabeel Mirza on 7/03/2017.
//  Copyright © 2017 Nabeel Mirza. All rights reserved.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct players   //struct to store the information of each player
{
    char name[20];
    char class[20];
    int type;
    int lifepoints;
    int smartness;
    int magic_skills;
    int strength;
    int dexterity;
    int luck;
    int position;
};

typedef struct   //struct to store the information of each slot
{
    int Num;
    char Type[13];

}defSlot;

char Ground[] = {"Level Ground"};
char Hill[] = {"Hill"};
char City[] = {"City"};
int numslots;

int main(void)
{
    struct players player[6];   //array declaration for the amount of players/structs
    int n=0, i=0, type;

    printf("\nPlease enter the number of players wanted (1-6): \n");
    scanf("%d", &n);

    while (n < 2  || n > 6){
        printf("Please enter the number of players between 2-6. \n"); //checks if there are a valid amount of players and loops until a correct amount is entered
        scanf("%d", &n);
    }

    while (i < n){
        printf("Please enter the players name: \n");
        scanf("%s", &player[i].name);
        printf("Please enter player type, 1 for Human, 2 for Ogre, 3 for Elf and 4 for Wizard: \n");
        scanf("%d", &type);

        while (type < 1 || type > 4){
            printf("Please enter a valid type between 1-4: \n");
            scanf("%d", &type);
        }
        player[i].type = type;i++;
    }

    srand ( time(NULL));
    for(i=0;i<n;i++)
    {
        if (player[i].type == 1)
        {
            strcpy(player[i].class, "Human");
            while((player[i].dexterity + player[i].magic_skills + player[i].smartness + player[i].strength + player[i].luck) < 300)   //while loop to make sure the sum of all capabilities isn't over 300
            {
                player[i].luck = (rand() %100 +1);
                player[i].smartness = (rand() %100 +1);
                player[i].strength = (rand() %100 +1);         //assigning Humans capabilities randomly
                player[i].dexterity = (rand() %100 +1);
                player[i].magic_skills = (rand() %100 +1);
                player[i].lifepoints = 100;
            }
        }
        else if (player[i].type == 2)
        {
            strcpy(player[i].class, "Ogre");
            while ((player[i].luck + player[i].smartness) <= 50)   //while loop to make sure the sum luck and smartness is <= 50
            {
                player[i].smartness = (rand() %20 +1);
                player[i].strength = (rand() %21 +80);
                player[i].dexterity = (rand() %21 +80);     //assigning Ogres capabilities randomly
                player[i].luck = (rand() %50 +1);
                player[i].lifepoints = 100;
                player[i].magic_skills = 0;
            }
        }
        else if (player[i].type == 3)
        {
            strcpy(player[i].class, "Elf");

            player[i].luck = (rand() %41 +60);
            player[i].smartness = (rand() %31 +70);
            player[i].strength = (rand() %51 +1);         //assigning Elfs capabilities randomly
            player[i].dexterity = (rand() %99 +1);
            player[i].magic_skills = (rand() %29 +51);
            player[i].lifepoints = 100;
        }

        else if (player[i].type == 4)
        {
            strcpy(player[i].class, "Wizard");

            player[i].smartness = (rand() %11 +90);
            player[i].dexterity = (rand() %100 +1);
            player[i].strength = (rand() %20+1);      //assigning Wizards capabilities randomly
            player[i].luck = (rand() %51 +50);
            player[i].magic_skills = (rand() %21 +80);
            player[i].lifepoints = 100;
        }

        else {}

        printf("\nPlayer %d\n",(i+1));
        printf("name: %s\n", player[i].name);
        printf("class: %s\n",player[i].class);
        printf("lifepoints: %d\n",player[i].lifepoints);
        printf("smartness = %d\n",player[i].smartness);                    //printing out all player details
        printf("magic_skills = %d\n",player[i].magic_skills);
        printf("strength = %d\n",player[i].strength);
        printf("dexterity = %d\n",player[i].dexterity);
        printf("luck = %d\n",player[i].luck);
    }

    printf("\nPlease enter a number of slots (max 20): \n");
    do{
        scanf("%d", &numslots);
        if(numslots>20 || numslots<n)
        {
            printf("Please enter a valid number of slots: \n");
        }
    }while(numslots>20 || numslots<n);

    defSlot *Slot;
    Slot = (int*)malloc(numslots * sizeof(defSlot));  //assigning the size to the slot array by the users input
    i = 0;

    while(i < numslots){
        Slot[i].Num = -1;   //initialise to -1 making it easy to mark the position of each player
        int x = 1+ rand()%3;   //assigning a type to the slot randomly
        if(x == 1)
        {
            strcpy(Slot[i].Type , Ground);
        }
        else if(x == 2)
        {
            strcpy(Slot[i].Type , Hill);
        }
        else
        {
            strcpy(Slot[i].Type , City);
        }
        i++;
    }

    int markArr[20];   //new array is defined with the max size of slots to ensure only one player can be assigned to a slot
    for(i=0; i<20; i++){
        markArr[i] = 1;
    }

    for(i=0; i< n; i++){
        int x = rand()%numslots;
        if(markArr[x] != 0){
            player[i].position = x;   //assigning players to slots randomly
            Slot[x].Num = i;
            markArr[x] = 0;
        }
        else{
            i--;
        }
    }

    i = 0;

    while(i<n){

        int pos = player[i].position;
        C:printf("Player %d's action: \nA. Move to previous slot\n" "B. Move to next slot\nC. Attack Player\n",i+1);
        getchar();
        char x;
        x = getchar();

        if(x == 'A' || x == 'a'){
            if(pos-1<0 || Slot[pos-1].Num != -1){
                printf("You can't move to this slot.");   //if the previous slot does not exist or there is a player in that slot
                goto x;
            }
            else
            {
                player[i].position = pos-1;
                Slot[pos-1].Num = i;      //marks that player i is on this slot.
                if(strcmp(Hill , Slot[pos-1].Type) == 0){
                    if(player[i].dexterity < 50){			//capabilities for hill slot
                        player[i].strength -= 10;
                    }
                    else if(player[i].dexterity <= 60){
                        player[i].strength += 10;
                    }
                }
                else if(strcmp(City , Slot[pos-1].Type) == 0){
                    if(player[i].smartness > 60){				//capabilities for city slot
                        player[i].magic_skills += 10;
                    }
                    else if(player[i].smartness <= 50){
                        player[i].dexterity -= 10;
                    }
                }
            }
        }

        else if(x =='B'|| x =='b'){
            if(pos+1 > numslots || Slot[pos+1].Num != -1){
                printf("You can't move to this slot.");
                goto x;
            }
            else{
                player[i].position = pos+1;
                Slot[pos+1].Num = i;

                if(strcmp(Hill , Slot[pos+1].Type) == 0){
                    if(player[i].dexterity < 50){
                        player[i].strength -= 10;
                    }
                    else if(player[i].dexterity <= 60){
                        player[i].strength += 10;
                    }
                }
                else if(strcmp(City , Slot[pos+1].Type) == 0){
                    if(player[i].smartness > 60){
                        player[i].magic_skills += 10;
                    }
                    else if(player[i].smartness <= 50){
                        player[i].dexterity -= 10;
                    }
                }
            }
        }

        else if(x == 'C' || x == 'c'){
            unsigned int *spaceArr;
            spaceArr = (int*)malloc(n * sizeof(int));

            for(int j=0; j<n; j++){
                spaceArr[j] = player[j].position - player[i].position;
	           }
            for(int j=0; j<n-1; j++){

                for(int k=j+1; k<n; k++){
                    int y;
                    if(spaceArr[k] < spaceArr[j]){
                        y = spaceArr[k];
                        spaceArr[k] = spaceArr[j];
                        spaceArr[j] = y;
                    }
                }
            }

            int nearestplayer = spaceArr[1];
            unsigned int n;
            int counter = 0;
            int mark[2];
            int *ptr = mark;

            for(int j=0;j<n;j++) //checks to see how many players are close

	       {
                n = player[j].position - player[i].position;
                if(n == nearestplayer)

		   {
                     *ptr++ = j;
                     counter += 1;
                  }
               }

            if(counter == 1) //1 player is the closest
		      {

                if(player[mark[0]].strength <= 70)			//capabilities for attacking
		           {
                      player[mark[0]].lifepoints -= (0.5*player[mark[0]].strength);
                     }

                else
		           {
                      player[i].lifepoints -= (0.3*player[mark[0]].strength);
                   }
               }

            else if(counter == 2) //2 players are the closest
	     {

                printf("Two players are close, which do you want to attack?\n"	//ask who to attack
                       "A.Player%d Name:%s Type:%s\nor B.Player%d Name:%s Type:%s\n"
                       , mark[0]+1, player[mark[0]].name, player[mark[0]].type
                       , mark[1]+1, player[mark[1]].name, player[mark[1]].type);
                char X;
                X = getchar();

                if(X == 'A' || X == 'a')
	            {
                    if(player[mark[0]].strength <= 70)

			           {
                          player[mark[0]].lifepoints -= (0.5*player[mark[0]].strength);
                       }
                else
			           {
                          player[i].lifepoints -= (0.3*player[mark[0]].strength);
                       }
                }

                else if(X == 'B' || X == 'b')

		        {
                    if(player[mark[1]].strength <= 70)
			           {
                         player[mark[1]].lifepoints -= (0.5*player[mark[1]].strength);
                       }

                else
                        {
                          player[i].lifepoints -= (0.3*player[mark[1]].strength);
                        }
                }
            }
        }

      i++;
    }

    for(i=0;i<n;i++)    //prints out player name, type and lifepoints

	    {
           printf("%s (%s, %.2f)\n", player[i].name, player[i].type, player[i].lifepoints);
        }

    return 0;
}
