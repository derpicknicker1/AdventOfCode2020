/*

*/
#include "advent.h"
#define DEBUG 0
typedef struct card{
	int val;
	struct card *prev;
	struct card *next;
} Card;

typedef struct game{
	int cnt1;
	int cnt2;
	Card *p1;
	Card *p2;
	Card *t1;
	Card *t2;
} Game;

Game startGame;
static int gameCnt = 0;

static void freeGame(Game *g) {
	Card *ptr = NULL;
	if(g->p1 != NULL) {
		do {
			ptr = g->p1->next;
			free(g->p1);
			g->p1 = ptr;
		} while(ptr != NULL);
	}

	if(g->p2 != NULL) {
		do {
			ptr = g->p2->next;
			free(g->p2);
			g->p2 = ptr;
		} while(ptr != NULL);
	}
	
}

static void evalWin(Card** tail, Card** winner, Card** looser) {
	(*tail)->next = (*winner);
	(*winner)->prev = (*tail);
	(*tail) = (*winner);
	(*winner) = (*winner)->next;
	(*winner)->prev = NULL;
	(*tail)->next = (*looser);
	(*looser)->prev = (*tail);
	(*tail) = (*looser);
	(*looser) = (*looser)->next;
	if((*looser) != NULL)
		(*looser)->prev = NULL;
	(*tail) -> next = NULL;
}

static void addCard(Card** player, Card** tail, char* line) {
	if((*player) == NULL) {
		(*player) = malloc(sizeof(Card));
		(*player)->val = toI(line);
		(*player)->next = NULL;
		(*player)->prev = NULL;
		(*tail) = (*player);
	}
	else {
		(*tail)->next = malloc(sizeof(Card));
		(*tail)->next->prev = (*tail);
		(*tail) = (*tail)->next;
		(*tail)->val = toI(line);
		(*tail)->next = NULL;
	}
}

/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
	size_t l;
	startGame.t1 = NULL;
	startGame.t2 = NULL;
	startGame.p1 = NULL;
	startGame.p2 = NULL;
	startGame.cnt1 = 0;
	startGame.cnt2 = 0;
	gameCnt = 0;
	int p1 = true;

	FILE *file = fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}

	while( getline(&line, &l, file) != -1) {
		line = trim(line);
		if(line[0] == 'P')
			continue;
		else if(strcmp(line,"") == 0)
			p1 = false;
		else if (p1) {
			startGame.cnt1++;
			addCard(&startGame.p1, &startGame.t1, line);
		}
		else {
			startGame.cnt2++;
			addCard(&startGame.p2, &startGame.t2, line);
		}
	}

	free(line);
	fclose(file);
	return 1;
}

static unsigned long  hash(const char *s) {
    unsigned long  h;
    unsigned const char *us;
    us = (unsigned const char *) s;
    h = 0;
    while(*us != '\0') {
        h = h * 37 + *us;
        us++;
    } 

    return h;
}

static unsigned long  getHash(Card** t1, Card** t2, Card** p2) {
	int i;
	char values[100] = {};
	(*p2)->prev = (*t1);
	Card *iter = (*t2);
	for(i = 0; iter != NULL; iter = iter->prev, i++ )
		values[i] = iter->val;
	(*p2)->prev = NULL;
	unsigned long ret = hash(values);
	free(values);
	return ret;
}

static Card* copyCards(Card* cards, int cnt) {	
	if (cards == NULL) return NULL;

	Card *newHead = malloc(sizeof(Card));
	newHead->val = cards->val;
	newHead->prev = NULL;

	int count = 1;
	Card *p = newHead;
	cards = cards->next;
	while(cards != NULL && count++ < cnt) {
		p->next = malloc(sizeof(Card));
		p->next->prev = p;
		p=p->next;
		p->val = cards->val;
		cards = cards->next;
	}
	p->next = NULL;  // terminate last element.
	return newHead;
}

static int playGame(int recursive, Game *g) {
	int round = 0;
	unsigned long hashes[600] = {};
	int hashCnt = 0;
	gameCnt++;
	int localGame = gameCnt;

	if(DEBUG) printf("=== Game %d ===\n",localGame);

	while(g->p1 != NULL && g->p2 != NULL) {
		int winner = (g->p1->val > g->p2->val) ? 0 : 1;
		round++;
		if(DEBUG)printf("\n-- Round %d (Game %d) --\nPlayer 1's deck: ",round,localGame);
		for(Card *iter = g->p1; iter !=0; iter = iter->next)
			if(DEBUG)printf("%d, ",iter->val);
		if(DEBUG)printf("\nPlayer 2's deck: ");
		for(Card *iter = g->p2; iter !=0; iter = iter->next)
			if(DEBUG)printf("%d, ",iter->val);
		if(DEBUG)printf("\nPlayer 1 plays: %d\n",g->p1->val);
		if(DEBUG)printf("Player 2 plays: %d\n",g->p2->val);

		if(recursive) {
			
			unsigned long  myHash = getHash(&g->t1, &g->t2, &g->p2);
			int found = false;

			//search hash
			for(int i = 0; i < hashCnt; i++)
				if(hashes[i] == myHash)
					found = true;

			// hash found?
			if(!found){
				//hashes = realloc(hashes, ++hashCnt * sizeof(int));
				hashes[hashCnt++] = myHash;
			}
			else {
				if(DEBUG)printf("\n############################\nHash found! %d\n############################\n\n",myHash);
				free(hashes);
				return 0; // pl1 wins
			}

			// start Sub-Game
			if(g->p1->val <= g->cnt1-1 && g->p2->val <= g->cnt2-1){
				if(DEBUG)printf("Playing a sub-game to determine the winner...\n\n",round);
				Game newGame;
				newGame.p1 = copyCards(g->p1->next, g->p1->val);
				newGame.p2 = copyCards(g->p2->next, g->p2->val);
				newGame.t1 = newGame.p1;
				while(newGame.t1->next != NULL)
					newGame.t1 = newGame.t1->next;
				newGame.t2 = newGame.p2;
				while(newGame.t2->next != NULL)
					newGame.t2 = newGame.t2->next;
				newGame.cnt1 = g->p1->val;
				newGame.cnt2 = g->p2->val;

				winner = playGame(true,&newGame);

				freeGame(&newGame);
				if(DEBUG)printf("...anyway, back to game %d.\n",localGame);
			}
		}
		//play normal game
		if(!winner){
			evalWin(&g->t1, &g->p1, &g->p2);
			g->cnt1++;
			g->cnt2--;
			if(DEBUG)printf("Player 1 wins round %d of game %d!\n",round,localGame);
		}
		else {
			evalWin(&g->t2, &g->p2, &g->p1);
			g->cnt1--;
			g->cnt2++;
			if(DEBUG)printf("Player 2 wins round %d of game %d!\n",round,localGame);
		}
	}
	if(g->p1 == NULL)
		if(DEBUG)printf("The winner of game %d is player 2!\n\n",localGame);
	else
		if(DEBUG)printf("The winner of game %d is player 1!\n\n",localGame);
	free(hashes);
	//if(hashCnt>500)
	printf("%d\n",hashCnt);
	return (g->p1 == NULL) ? 1 : 0;
}


/*##########################
# Function to solve part A #
##########################*/
void get22a(char * f) {
	if(!getInput(f))
		return;
	
	int i, result = 0;

	Card *iter = (playGame(false,&startGame)) ? startGame.t2 : startGame.t1;

	for(i = 1; iter != NULL; iter = iter->prev, i++ )
		result += (i * iter->val);
	
	printf("22a: %d\n", result);
	freeGame(&startGame);
}

/*##########################
# Function to solve part B #
##########################*/
void get22b(char *f) {
	if(!getInput(f))
		return;

	int i, result = 0,win;

	win = playGame(true, &startGame);

	Card *iter = (win) ? startGame.t2 : startGame.t1;

	for(i = 1; iter != NULL; iter = iter->prev, i++ )
		result += (i * iter->val);

	printf("22b: %d %d\n\n", result,win);
	//32033 low
	//34746 low
	freeGame(&startGame);
}
