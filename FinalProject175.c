
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
// Functions needed: check card, addCard, DeleteCard, 
typedef struct card_s {
    char color[10];
    int value;
    char action[15];
    struct card_s* pt, * previous;
} card;

void swapCard(card deck []);
void addCard(card** h, card** t, card s);
void deleteCard(card** h, card** t, int cardChoice);
void printHand(card* h);

int main(void) {
    FILE* inp = fopen("CardDeck.txt", "r");
    card deck[108];
    int i, currentCardPosition = 0;
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
    //printf("%d", p1Head->value);
    return 0;
}
void printHand(card* h) {
    card* i = h;
    
    while (i != NULL) {
        printf("%s %d %s\n", i->color, i->value, i->action);
        i = i->pt;
    }
}
void addCard(card** h, card** t, card s) {
    card* temp;
    temp = (card*)malloc(sizeof(card));
    strcpy(temp->color, s.color);
    temp->value = s.value;
    strcpy(temp->action, s.action);

    if (*h == NULL) {
        *h = temp;
        *t = temp;
        temp->previous = NULL;
        temp->pt = NULL;
    }
    else {
        (*t)->pt = temp;
        temp->previous = *t;
        *t = temp;
        temp->pt = NULL;
    }
}
void deleteCard(card** h, card** t, int cardChoice) {
    card* p;
    int i;
    p = *h;

    for (i = 1; i < cardChoice; i++) {
        p = p->pt;
    }
    if (p == *h) {
        *h = p->pt;
    }
    else {
        p->previous->pt = p->pt;
    }

    if (p == *t) {
        *t = p->previous;
    }
    else {
        (p->pt)->previous = p->previous;
    }
    free(p);
}
void swapCard(card deck []){
    card temp;
    int i;
    int j;
    
    i = rand() % 108;
    j = rand() % 108;
    
    
    if (i != j) {
        strcpy(temp.color, deck[i].color);
        temp.value = deck[i].value;
        strcpy(temp.action, deck[i].action);
        strcpy(deck[i].color, deck[j].color);
        deck[i].value = deck[j].value;
        strcpy(deck[i].action, deck[j].action);
        strcpy(deck[j].color, temp.color);
        deck[j].value = temp.value;
        strcpy(deck[j].action, temp.action);
    }
}
