#include <stdio.h>
#include <conio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>    
#define MAX 100

typedef	struct bag {
	char name[10];
	char desc[20];
	int qty;
	int usage;
} item;
typedef struct ninja {
	item inventory[MAX];
	int invCount;
	char name[10];
	int hp;
	int attack;
}character;
typedef struct node {
	character hero;
	struct node *link;
}nodetype, *LIST;
void delay(unsigned int milliseconds);
void initPLayer(LIST *L);
void initItem(LIST *L);
void insertFirstHero(LIST *L, character C);
void displayPlayerStats(LIST L);
void UseAnddisplayItem(character C);
void pvp(LIST *L);
void pve(LIST *L);
void insertHero(LIST *L, character C);

void UseAnddisplayItem(LIST *L);

void insertItem(LIST *L , int i, item I);

int main(){
	int x;
	
	
	int i;
	LIST L;
	initPLayer(&L);
	initItem(&L);
	
	printf("Enter 1 for PVP || 2 for PVE: ");
	scanf("%d", &x);
	
	if(x==1){
		 printf("\nYou can only use 3 move at a time\n ");
		 printf("\nHINT: You have 3 potions and 1 booster in your backpack. Using inventory when you dont have items left in your bag will make your move useless. So use it wisely \n");
	
		
		character c1 = {{ {"Potion", "Heals 500 hp", 3, 500},{"Booster", "Damage boost 250", 1, 250} }, 2,"Garfield", 5000, 500};
		character c2 = {{ {"Potion", "Heals 500 hp", 3, 500},{"Booster", "Damage boost 250", 1, 250} }, 2,"DOGO", 5000, 500};
		
	
	//	insertFirstHero(&L, c2);
	//	insertFirstHero(&L, c1);
//		UseAnddisplayItem(c1);
	
		insertHero(&L, c1);
		insertHero(&L, c2);
		
		displayPlayerStats(L);

//		UseAnddisplayItem(c1);
	    pvp(&L);
	}else if(x==2){
		 printf("\nYou can only use 3 move at a time\n");
    	 printf("Adventure mode up to 5 rounds, 50 percent drops healing and potion if you win a round. Monsters get stronger each round\n You only have 1 potion in your bag, earn other items by killing the monsters.");
     
       	
   		character c1 = { {"Potion", "Heals 500 hp", 1, 500}, 1,"Garfield", 5000, 500};

   		insertHero(&L, c1);
	//	UseAnddisplayItem(&L, 0);
      	pve(&L);
       	
	}
	
}
void delay(unsigned int milliseconds) {    
    clock_t start = clock();    
    while ((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);    
}    
void initPLayer(LIST *L){
	*L=NULL;
}
void initItem(LIST *L){
	LIST *temp;
	for(temp=L; *temp!=NULL; temp=&(*temp)->link){
		(*temp)->hero.invCount=0;
	}
}

void insertItem(LIST *L,int i , item I){
	
	LIST *temp;
	
	int x;
	for(temp=L, x=0; *temp!=NULL && x != i; x++, temp=&(*temp)->link){ }
		
		if((*temp)->hero.invCount<MAX){
		(*temp)->hero.inventory[(*temp)->hero.invCount]=I;
		(*temp)->hero.invCount++;
		}
		
}

void insertFirstHero(LIST *L, character C){
	LIST *p,temp;
	//insertFirst

	temp=(LIST)malloc(sizeof(struct node));
	if(temp!=NULL){
		temp->hero=C;
		temp->link=*L;
		*L=temp;
	}
}

void insertHero(LIST *L, character C){	
	LIST *temp, x;
	//insertLast
	
	for( temp=L; *temp != NULL; temp=&(*temp)->link){}
	
	x=(LIST)malloc(sizeof(struct node));
	
	if(temp!=NULL){
	x->hero=C;
	x->link=NULL;
	*temp=x;
	}	
			
}

void displayPlayerStats(LIST L){
	
		LIST trav;
		for(trav=L; trav!=NULL; trav=trav->link){
			printf("\n\n");
			printf("player name: %s\n", trav->hero.name );
			printf("player HP: %d\n", trav->hero.hp);
			printf("player attack power: %d\n", trav->hero.attack);	
		}
}


void UseAnddisplayItem(LIST *L, int i){
	
	int y,x,choice;
	printf("%-10s %-15s %20s %20s \n", "Name", "Desc", "Quantity", "Usage");
	
	LIST *trav;
	for(trav=L, y=0; *trav!=NULL && y != i; y++, trav=&(*trav)->link){ }

	for(x=0; x< (*trav)->hero.invCount; x++){
		printf("#%d ", x);
		printf("%-10s", (*trav)->hero.inventory[x].name);
		printf("%-15s", (*trav)->hero.inventory[x].desc);
		printf("%20d", (*trav)->hero.inventory[x].qty);
		printf("%20d", (*trav)->hero.inventory[x].usage);
		printf("\n");
	}
	
	printf("\n Enter The # of the item you want to use. \n");
	scanf("%d", &choice);

	for(x=0; x<(*trav)->hero.invCount; x++){
	if((*trav)->hero.invCount > 0){
		
	
		if(choice == x){
			if(strcmp((*trav)->hero.inventory[x].name, "Potion")==0 ){
				(*trav)->hero.hp += (*trav)->hero.inventory[x].usage;
				(*trav)->hero.inventory[x].qty--;
		
			if((*trav)->hero.inventory[x].qty <=0 ){
				for(y=x; y < (*trav)->hero.invCount; ++y){
					(*trav)->hero.inventory[y] = 	(*trav)->hero.inventory[y+1];
				}
				(*trav)->hero.invCount--;
			}
			
		}else if(strcmp((*trav)->hero.inventory[x].name, "Booster")==0 ){
				(*trav)->hero.attack += (*trav)->hero.inventory[x].usage;
				(*trav)->hero.inventory[x].qty--;
			if((*trav)->hero.inventory[x].qty <=0 ){
				for(y=x; y < (*trav)->hero.invCount; ++y){
					(*trav)->hero.inventory[y] = (*trav)->hero.inventory[y+1];
				}
			(*trav)->hero.invCount--;
			}
		}
	}
	
	}else if((*trav)->hero.invCount <= 0){
		printf("\n You have no more items left\n ");
	}
	
	}
	
	
}



void pvp(LIST *L){
	int i,x, pl;
	int ret, c1Turn, c2Turn, choice1[3], choice2[3];
	int WR=0,rounds=1, win;
	int hero1=0, hero2=1;
	
	LIST *trav=L;
	
	printf("\nwelcome to pvp press any key to start \n ");
	getch();
	system("cls");
	

	for(x=0; WR != 1; x++){
		
			for(c1Turn=3; c1Turn > 0; c1Turn--){
				if((*trav)->hero.hp > 0){
					printf("Player 1 turn MOve: %d \n", c1Turn);
					printf("1 - Attack enemy \n");
					printf("2 - Harden, +200 hp \n");
					printf("3 - Inventory\n");
					printf("Choose only the number: ");

					scanf("%d", &choice1[c1Turn]);
				
			
					system("cls");
			}
			
		}
		
		
			for(c2Turn=3; c2Turn>0; c2Turn--){	
				if((*trav)->link->hero.hp > 0){
					printf("Player 2 turn MOve: %d \n", c2Turn);
					printf("1 - Attack enemy \n");
					printf("2 - Harden, +200 hp \n");
					printf("3 - Inventory\n");
					printf("Choose only the number: ");
					scanf("%d", &choice2[c2Turn]);
				
				
					system("cls");
			}
			
		}
		
		
	
		
		//ATTACKING PHASE
		

		if((*trav)->hero.hp >0 && (*trav)->link->hero.hp >0){
			printf("\n BATTLEMODE ROUND %d: \n ", rounds);
			
				
			
			for(c1Turn=3; c1Turn>0; c1Turn--){
					if(choice1[c1Turn] == 1 ){
						printf("LOG: Player 1 Attacks player 2\n ");
						
						delay(1000);
						(*trav)->link->hero.hp -= (*trav)->hero.attack;
						if((*trav)->link->hero.hp  < 0){
							WR = 1;
						}
					}else if(choice1[c1Turn] == 2 ){
						printf("LOG: Player 1 Uses Harden\n");
						delay(1000);


						(*trav)->hero.hp += 200;
					}else if(choice1[c1Turn] == 3 ){
					printf("LOG: Player 1 Uses Bag\n");
						delay(1000);


						//uses item
						UseAnddisplayItem(trav, 0);
					}
			}
			
				
			
			
			for(c2Turn=3; c2Turn>0; c2Turn--){
						if(choice2[c2Turn] == 1 ){
						printf("LOG: Player 2 Attacks player 1\n ");
						delay(1000);

						(*trav)->hero.hp -= (*trav)->link->hero.attack;
						if((*trav)->hero.hp  < 0){
							WR = 1;
						}
						
					}else if(choice2[c2Turn] == 2 ){
						printf("LOG: Player 2 Uses Harden\n");
						delay(1000);
		
						(*trav)->link->hero.hp += 200;
					}else if(choice2[c2Turn] == 3 ){
					printf("LOG: Player 2 Uses Bag\n");
						//uses item
						delay(1000);

						UseAnddisplayItem(trav, 1);
					}
				
			}
		
		
			 displayPlayerStats(*L);
			 rounds++;
			 
			 if((*trav)->link->hero.hp  < 0 && (*trav)->link->hero.hp < (*trav)->hero.hp){
			 	printf("\n PLAYER 1 WIN!!! \n");
			 }else if((*trav)->hero.hp  < 0 && (*trav)->hero.hp < (*trav)->link->hero.hp ){
			 	printf("\n PLAYER 2 WIN!!! \n");
			 }
				 printf("\n press any key: \n ");
				 getch();

			 system("cls");
						
			}
		
	}
	
}


void pve(LIST *L){
	
	time_t t;
	srand((unsigned) time(&t));
	int i,x;
	int ret, c1Turn, c2Turn, choice1[3], choice2[3];
	int WR=0,rounds=1, win,WW=0,ct=0;
	int hero1=0, monster=1, bonus;
	LIST *trav=L;

	printf("\nwelcome to ADVENTURE press any key to start \n ");
	getch();
	system("cls");
	
		character m = { {}, 0,"Monster", 5000, 500};

   		insertHero(L, m);
//	 displayPlayerStats(*L);

		

	for(x=0; WR != 1 && ct!= 5; x++){
		printf("Monster: %d \n", ct);
			for(c1Turn=3; c1Turn > 0; c1Turn--){
				if((*trav)->hero.hp > 0){
					printf("Player 1 turn MOve: %d \n", c1Turn);
					printf("1 - Attack enemy \n");
					printf("2 - Harden, +200 hp \n");
					printf("3 - Inventory\n");
					printf("Choose only the number: ");

					scanf("%d", &choice1[c1Turn]);
				
			
					system("cls");
			}
			
		}
		
		
			for(c2Turn=3; c2Turn>0; c2Turn--){	
				if((*trav)->link->hero.hp > 0){
				 choice2[c2Turn]=rand() % 2;
				
				
				
			}
			
		}
		
		
	
		
		//ATTACKING PHASE
		

		if((*trav)->hero.hp >0 && (*trav)->link->hero.hp >0){
			printf("\n BATTLEMODE ROUND %d: \n ", rounds);		
		
			for(c1Turn=3; c1Turn>0; c1Turn--){
					if(choice1[c1Turn] == 1 ){
						printf("LOG: Player 1 Attacks player 2\n ");
						
						delay(1000);
						(*trav)->link->hero.hp -= (*trav)->hero.attack;
						if((*trav)->link->hero.hp  < 0){
							WW++;
						}
					}else if(choice1[c1Turn] == 2 ){
						printf("LOG: Player 1 Uses Harden\n");
						delay(1000);


						(*trav)->hero.hp += 200;
					}else if(choice1[c1Turn] == 3 ){
					printf("LOG: Player 1 Uses Bag\n");
						delay(1000);


						//uses item
						UseAnddisplayItem(trav, 0);
					}
			}
			
				
			
			
			for(c2Turn=3; c2Turn>0; c2Turn--){
						if(choice2[c2Turn] == 0 ){
						printf("\nLOG: Monster Attacks player 1\n ");
						delay(1000);

						(*trav)->hero.hp -= (*trav)->link->hero.attack;
						if((*trav)->hero.hp  < 0){
							WR = 1;
						}
						
					}else if(choice2[c2Turn] == 1 ){
						printf("LOG: Monster Uses Harden\n");
						delay(1000);
		
						(*trav)->link->hero.hp += 200;
					}
				
			}
		
		
			 displayPlayerStats(*L);
			 rounds++;
			 
			 
			 if(ct < WW ){
			 	printf("\nRefreshing hero and monster...");
			 	delay(1000);
				 ct = WW;
			 
			 	
			 	(*trav)->hero.hp=5000;
			 	(*trav)->link->hero.hp=5000;

			    
			 		(*trav)->link->hero.attack =(*trav)->link->hero.attack + (ct*100);
			 	
			 	
			 (*trav)->link->hero.hp = (*trav)->link->hero.hp + (ct*150);

				 bonus=rand() % 100;

				 printf("\nBonus droprate percentage: %d\n", bonus);
				 if(bonus >= 50){
				 	printf("\nCONGRATULATIONS YOU HAVE FOUND AN ITEM\n");
				 	item I =  {"Potion", "Heals 500 hp", 1, 500};
				 	item E = {"Booster", "Damage boost 250", 1, 250};
				
				 	insertItem( trav, 0,E);
			 		insertItem( trav, 0,I);
				 	
				 	
				 }
				 
			 }
			 
			 
			 
			 if((*trav)->link->hero.hp  < 0 && (*trav)->link->hero.hp < (*trav)->hero.hp){
			 	printf("\n PLAYER 1 WIN!!! get ready for  monster %d..\n", WW);
			 }else if((*trav)->hero.hp  < 0 && (*trav)->hero.hp < (*trav)->link->hero.hp ){
			 	printf("\n GAMEOVER MONSTER WIN!!! \n");
			 }else if(ct == 5){
			 	printf("YOU ARE THE ChAMPION!");
			 }
			 
			 
			 
				 printf("\n press any key: \n ");
				 getch();

			 system("cls");
						
			}
		
	}
	
}
