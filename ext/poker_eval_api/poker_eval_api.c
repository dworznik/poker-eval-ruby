#include "poker_defs.h"
#include "enumdefs.h"

void* create_enum_result() {
    return malloc(sizeof(enum_result_t));
}

void  free_enum_result(enum_result_t* ptr) {
    if(ptr->ordering != NULL) {
        free(ptr->ordering->hist);
        free(ptr->ordering);
    }
    free(ptr);
}

StdDeck_CardMask TextToPokerEval(const char* strHand)
{
    StdDeck_CardMask theHand, theCard;
    StdDeck_CardMask_RESET(theHand);

    if (strHand && strlen(strHand))
    {
        int cardIndex = -1;
        char* curCard = strHand;
        while (*curCard)
        {
            // Take the card text and convert it to an index (0..51)
            StdDeck_stringToCard(curCard, &cardIndex);
            // Convert the card index to a mask
            theCard = StdDeck_MASK(cardIndex);
            // Add the card (mask) to the hand
            StdDeck_CardMask_OR(theHand, theHand, theCard);
            // Advance to the next card (if any)
            curCard += 2;
        }
    }
    return theHand;
}


int  eval_holdem(char* str_pockets[], int npockets, char* str_board, int nboard, enum_result_t* result) {
    int i, niter = 0, err, terse, orderflag = 0;

    enum_game_t game = game_holdem;
    StdDeck_CardMask pockets[ENUM_MAXPLAYERS];
    StdDeck_CardMask board;
    StdDeck_CardMask dead;

    StdDeck_CardMask_RESET(board);
    StdDeck_CardMask_RESET(dead);

    for(i = 0; i < npockets; i++) {
        pockets[i] = TextToPokerEval(str_pockets[i]);
    }

    board = TextToPokerEval(str_board);

    err = enumExhaustive(game, pockets, board, dead, npockets, nboard, orderflag, result);
    printf("poker source:\n\n");
    enumResultPrint(result, pockets, board);
    return err;
}

