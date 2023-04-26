#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
// Functions needed: check card, addCard, DeleteCard, 
typedef struct card_s {
	char color[10];
	int value;
	char action[15];
	struct card_s* pt;//pt is the equivalent of next, goes from head to tail of linked list
} card;
void printHand(card **h, card **t);
int main(void) {
	FILE* inp = fopen("CardDeck.txt","r");
	card deck[108];
	int i,currentCardPosition = 0;
	card *p1Head = NULL, *p1Tail = NULL, *p2Head = NULL, *p2Tail = NULL, *centerHead = NULL, *centerTail = NULL;
	while (!feof(inp)) {
		for (i = 0; i < 108;i++) {
			fscanf(inp, " %s", deck[i].color);
			fscanf(inp, " %d", &deck[i].value);
			fscanf(inp, " %s", deck[i].action);
			
		}
	}
	for (int k = 0;k < 7;k++) {
		addCard(&p1Head, &p1Tail, deck[currentCardPosition]);
		currentCardPosition++;
		addCard(&p2Head, &p2Tail, deck[currentCardPosition]);
		currentCardPosition++;
	}
	addCard(&centerHead, &centerTail, deck[currentCardPosition]);
	currentCardPosition++;
	addCard(&centerHead, &centerTail, deck[currentCardPosition]);
	currentCardPosition++;
	printHand(p1Head);
	return 0;
}
void printHand(card *h) {
	card* i = h;
	while (i != NULL) {
		printf("%s %d %s\n", i->color, i->value, i->action);
		i = i->pt;
	}
}
