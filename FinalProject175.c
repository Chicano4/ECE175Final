#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
// Functions needed: check card, addCard, DeleteCard, 
typedef struct card_s {
	char color[10];
	int value;
	char action[15];
	struct card_s* pt;
} card;
int main(void) {
	FILE* inp = fopen("CardDeck.txt","r");
	card deck[108];
	int i,j;
	while (!feof(inp)) {
		for (i = 0; i < 108;i++) {
			fscanf(inp, " %s", deck[i].color);
			fscanf(inp, " %d", &deck[i].value);
			fscanf(inp, " %s", deck[i].action);
			
		}
	}
	
	return 0;
}
