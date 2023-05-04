#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
// Functions needed: check card, addCard, DeleteCard, 
typedef struct card_s {
    char color[10];
    int value;
    char action[15];
    struct card_s* pt, *previous;
} card;

void shuffleDeck(card deck[]);
void addCard(card** h, card** t, card s);
void deleteCard(card** h, card** t, int cardChoice);
void printHand(card* h);
void turn(card **centerHead, card **playerHead, card *centerTail, card *playerTail, int *turns, int *singleMatches, int *doubleMatches);
void swapCard(card deck[]);
bool checkWith1Card(card* center, card* player);
bool checkWith2Cards(card* center, card* player1, card* player2);
int addToCenterRow(card* centerh);
bool checkColorwithOneCard(card p, card c);
bool checkColorwithTwoCards(card p1, card p2, card c);
void playerToCenterCard(card** centerh, card** playerh, card** centert, card** playert, int times);
int pointCounter(card** h, card** p, int hand);

int main(void) {
    FILE* inp = fopen("CardDeck.txt", "r");
    card deck[108];
    int i,a, currentCardPosition = 0, checkShuffle;
    int points1 = 0, points2 = 0, turns = 0, numSingleColorMatches = 0, numDoubleColorMatches = 0;
    //int* points1Pointer = &points1, * points2Pointer = &points2;
    card *p1Head = NULL, *p1Tail = NULL, *p2Head = NULL, *p2Tail = NULL, *centerHead = NULL, *centerTail = NULL;
    while (!feof(inp)) {
        for (i = 0; i < 108;i++) {
            fscanf(inp, " %s", deck[i].color);
            fscanf(inp, " %d", &deck[i].value);
            fscanf(inp, " %s", deck[i].action);

        }
    }
    printf("Enter 1 to shuffle deck, 2 to test");
    scanf("%d", &checkShuffle);
    if (checkShuffle == 1) {
        for (int shuffle = 0; shuffle < 1000; shuffle++) {
            shuffleDeck(deck);
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
    //deleteCard(&centerHead, &centerTail, 2);
    while(p1Head != NULL || p2Head != NULL || currentCardPosition < 108){
        //P1 Turn
        printf("Player 1's Hand: ");
        printHand(p1Head);
        printHand(centerHead); 
        turn(&centerHead, &p1Head, centerTail, p1Tail, &turns, &numSingleColorMatches, &numDoubleColorMatches);
        printf("turns = %d\n", turns);
        printHand(p1Head);
        if (turns == 0) {
            addCard(&p1Head, &p1Tail, deck[currentCardPosition]);
            currentCardPosition++;
            printf("Player 1's Hand: ");
            printHand(p1Head);
            printHand(centerHead);
            turn(&centerHead, &p1Head, centerTail, p1Tail, &turns, &numSingleColorMatches, &numDoubleColorMatches);
        }
        playerToCenterCard(&centerHead, &p1Head, &centerTail, &p1Tail, numSingleColorMatches);
        for (a = 0; a < numDoubleColorMatches;a++) {
            addCard(&p2Head, &p2Tail, deck[currentCardPosition]);
            currentCardPosition++;
            points1 += 40;
        }
        points1 += numSingleColorMatches * 20;
        for (a = 0; a < addToCenterRow(centerHead); a++) {
            addCard(&centerHead, &centerTail, deck[currentCardPosition]);
            currentCardPosition++;
        }
        printf("here\n");
        turns = 0;
        numSingleColorMatches = 0;
        numDoubleColorMatches = 0;
        
        //P2 turn begins
        printf("Player 2's Hand: ");
        printHand(p2Head);
        printHand(centerHead);
        turn(&centerHead, &p2Head, centerTail, p2Tail, &turns, &numSingleColorMatches, &numDoubleColorMatches);
        printf("turns = %d", turns);
        if (turns == 0) {
            addCard(&p2Head, &p2Tail, deck[currentCardPosition]);
            currentCardPosition++;
            printf("Player 2's Hand: ");
            printHand(p2Head);
            printHand(centerHead);
            turn(&centerHead, &p2Head, centerTail, p2Tail, &turns, &numSingleColorMatches, &numDoubleColorMatches);
        }
        playerToCenterCard(&centerHead, &p2Head, &centerTail, &p2Tail, numSingleColorMatches);
        for (a = 0; a < numDoubleColorMatches;a++) {
            addCard(&p1Head, &p1Tail, deck[currentCardPosition]);
            currentCardPosition++;
            points2 += 40;
        }
        points2 += numSingleColorMatches * 20;
        for (a = 0; a < addToCenterRow(centerHead, centerTail); a++) {
            addCard(&centerHead, &centerTail, deck[currentCardPosition]);
            currentCardPosition++;
        }
        turns = 0;
        numSingleColorMatches = 0;
        numDoubleColorMatches = 0;
    // if a player cannot make a match they draw a card and if they still cannot play a card, they add one to the center
    // play one card onto hashtags
    }
    if (p1Head == NULL) {
        printf("Player 1 wins with %d points", points1);
    }
    if (p2Head == NULL) {
        printf("Player 2 wins with %d points", points2);
    }
    else {
        printf("no winner ran out of cards");
    }
    return 0;
}
void printHand(card* h) {
    card* i = h;
    
    while (i != NULL) {
        printf("%s %d ", i->color, i->value);
        
        i = i->pt;
    }
    printf("\n");
}
void addCard(card** h, card** t, card s) {
    card* temp;
    temp = (card*)malloc(sizeof(card));
    strcpy(temp->color, s.color);
    temp->value = s.value;
    strcpy(temp->action, s.action);

    if (*h == NULL) {
        temp->previous = NULL;
        temp->pt = NULL;
        *h = temp;
        *t = temp;
    }
    else {
        temp->pt = NULL;
        (*t)->pt = temp;
        temp->previous = *t;
        *t = temp;
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
        (p->previous)->pt = p->pt;
    }

    if (p == *t) {
        *t = p->previous;
    }
    else {
        (p->pt)->previous = p->previous;
    }
    free(p);
}
void turn(card **centerHead, card **playerHead, card *centerTail, card *playerTail, int *turns, int *singleMatches, int *doubleMatches) {// color matches with 2 card; player gets to put a card in thecenter and all other players must draw from the pile. 1 color match player just gets to play in the middle
    int numberCardsToPlay, cardPosition,i,j,k,centerCardPosition = 1, cardPosition2 = 1, centerToPlay = 1;
    card* tempCenter = *centerHead;
    card* tempPlayer;
    card* tempPlayer2;
   
    bool enterLoop;
    while (centerToPlay != 0) {
        tempPlayer = *playerHead;//fix these pointers
        tempPlayer2 = *playerHead;
        tempCenter = *centerHead;
        enterLoop = true;
        cardPosition2 = 1;
        cardPosition = 1;
        printHand(*centerHead);
        printf("Which center card do you want to play? ");
        scanf("%d", &centerToPlay);
        printf("%d", centerToPlay);
        if (centerToPlay == 0) {
            break;
        }
        for (i = 1; i < centerToPlay;i++) {
            tempCenter = tempCenter->pt;
        }
        printf("How many cards will u play on %d %s ", tempCenter->value, tempCenter->color);
        scanf("%d", &numberCardsToPlay);
        printf("%d", numberCardsToPlay);
        if (numberCardsToPlay == 1) {
            while (enterLoop) {
                printf("Which card do you want to play ");
                scanf("%d", &cardPosition);
                for (i = 1; i < cardPosition;i++) {
                    tempPlayer = tempPlayer->pt;
                }
               
                printf("%d\n", tempPlayer->value);
                if (checkWith1Card(tempCenter, tempPlayer) || tempCenter->value == 11) {
                    if (checkColorwithOneCard(*tempPlayer,*tempCenter)) {
                        *singleMatches = *singleMatches + 1;
                    }
                    deleteCard(playerHead, &playerTail, cardPosition);
                    deleteCard(centerHead, &centerTail, centerCardPosition);
                    centerCardPosition--;
                    //printHand(*centerHead);
                }
                enterLoop = !checkWith1Card(tempCenter, tempPlayer);
            }
            *turns = *turns + 1;
        }
        else if(numberCardsToPlay == 2){
            while (enterLoop){
                
                printf("Select the position of both cards seperated by a comma ");
                scanf("%d,%d", &cardPosition, &cardPosition2);
                printf("%d %d", cardPosition, cardPosition2);
                for (k = 1; k < cardPosition;k++) {
                    tempPlayer = tempPlayer->pt;
                }
                for (j = 1; j < cardPosition2;j++) {
                    tempPlayer2 = tempPlayer2->pt;
                }
                if (checkWith2Cards(tempCenter, tempPlayer, tempPlayer2)) {
                    if (checkColorwithTwoCards(*tempPlayer, *tempPlayer2, *tempCenter)) {
                        *doubleMatches = *doubleMatches + 1;
                    }
                    deleteCard(playerHead, &playerTail, cardPosition);
                    deleteCard(playerHead, &playerTail, cardPosition2 - 1);
                    deleteCard(centerHead, &centerTail, centerCardPosition);
                    centerCardPosition--;
                    //printHand(*playerHead);
                }
                enterLoop = checkWith2Cards(tempCenter, tempPlayer, tempPlayer2);
            }
            *turns = *turns +1;
        }
    }
    //printHand(*centerHead);
}
/*
void swapCard(card deck[]) {
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
*/
bool checkWith1Card(card* center, card* player) {
    if (center->value == player->value) {
        return true;
    }
    return false;
}
bool checkWith2Cards(card* center, card* player1, card* player2) {
    if (player1->value == 11) {
        if (player2->value < center->value) {
            return true;
        }
    }
    if (player2->value == 11) {
        if (player1->value < center->value) {
            return true;
        }
    }
    if ((player1->value + player2->value) == center->value) {
        return true;
    }
    return false;
}
int addToCenterRow(card* centerh) {
    int numCards = 2;
    card* temp = centerh;
    while (temp != NULL) {
        numCards--;
        temp = temp->pt;
    }
    if (numCards < 0) {
        numCards = 0;
    }
    return numCards;
}
bool checkColorwithOneCard(card p, card c) {
    if (strcmp(p.color, c.color) == 0) {
        return true;
    }
    else {
        return false;
    }
}
bool checkColorwithTwoCards(card p1, card p2, card c) {
    if ((strcmp(p1.color, c.color) == 0) && (strcmp(p2.color, c.color) == 0)) {
        return true;
    }
    else {
        return false;
    }
}
void playerToCenterCard(card** centerh, card** playerh, card** centert, card** playert, int times) {
    int cardPos,i,j;
    card* temp;
    temp = *playerh;
    for (i = 0;i < times;i++) {
        printf("Which card would u like to add to the center?");
        printHand(*playerh);
        scanf("%d", &cardPos);
        for (j = 1; j < cardPos;j++) {
            temp = temp->pt;
        }
        printf("%d\n", temp->value);
        addCard(centerh, centert, *temp);
        deleteCard(playerh, playert, cardPos);
    }
}
int pointCounter(card** h, card** p, int hand) {
    card* temp;
    int cardValue;
    int total = 0;
    temp = *h;
    for (int i = 0; i < hand; i++) {
        cardValue = (*h)->value;
        if (cardValue != 2 || cardValue != 11) {
            cardValue = cardValue + cardValue;
        }
        if (cardValue == 2 || cardValue == 11) {
            if (cardValue == 2) {
                cardValue = cardValue + 20;
            }
            if (cardValue == 11) {
                cardValue = cardValue + 40;
            }
        }
        temp = temp->pt;
        total = total + cardValue;
    }
    return total;
}
void shuffleDeck(card deck[]){
    card temp;
    int i,j;
    srand(time(NULL));

  for (i = 107; i > 0; i--) {
    
    j = rand() % (i + 1);

      if (i != j){
          temp = deck[i];
          deck[i] = deck[j];
          deck[j] = temp;
      }
    
  }
}


