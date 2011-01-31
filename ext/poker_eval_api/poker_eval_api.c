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


void enumResultPrint(enum_result_t *result, StdDeck_CardMask pockets[],
                StdDeck_CardMask board) {
  int i;
  enum_gameparams_t *gp;
  int width;

  gp = enumGameParams(result->game);
  if (gp == NULL) {
    printf("enumResultPrint: invalid game type\n");
    return;
  }
  width = gp->maxpocket * 3 - 1;
  printf("%s: %d %s %s%s", gp->name, result->nsamples,
         (result->sampleType == ENUM_SAMPLE) ? "sampled" : "enumerated",
         (gp->maxboard > 0) ? "board" : "outcome",
         (result->nsamples == 1 ? "" : "s"));
  if (!StdDeck_CardMask_IS_EMPTY(board))
    printf(" containing %s", DmaskString(StdDeck, board));
  printf("\n");

  if (gp->haslopot && gp->hashipot) {
    printf("%*s %7s   %7s %7s %7s   %7s %7s %7s   %5s\n",
           -width, "cards", "scoop",
           "HIwin", "HIlos", "HItie",
           "LOwin", "LOlos", "LOtie",
           "EV");
    for (i=0; i<result->nplayers; i++) {
      printf("%*s %7d   %7d %7d %7d   %7d %7d %7d   %5.3f\n",
             -width, DmaskString(StdDeck, pockets[i]), result->nscoop[i],
             result->nwinhi[i], result->nlosehi[i], result->ntiehi[i],
             result->nwinlo[i], result->nloselo[i], result->ntielo[i],
             result->ev[i] / result->nsamples);
    }
  } else {
    printf("%*s %7s %6s   %7s %6s   %7s %6s     %5s\n",
           -width, "cards", "win", "%win", "lose", "%lose", "tie", "%tie", "EV");
    if (gp->haslopot) {
      for (i=0; i<result->nplayers; i++) {
        printf("%*s %7d %6.2f   %7d %6.2f   %7d %6.2f     %5.3f\n",
               -width, DmaskString(StdDeck, pockets[i]),
               result->nwinlo[i], 100.0 * result->nwinlo[i] / result->nsamples,
               result->nloselo[i], 100.0 * result->nloselo[i] / result->nsamples,
               result->ntielo[i], 100.0 * result->ntielo[i] / result->nsamples,
               result->ev[i] / result->nsamples);
      }
    } else if (gp->hashipot) {
      for (i=0; i<result->nplayers; i++) {
        printf("%*s %7d %6.2f   %7d %6.2f   %7d %6.2f     %5.3f\n",
               -width, DmaskString(StdDeck, pockets[i]),
               result->nwinhi[i], 100.0 * result->nwinhi[i] / result->nsamples,
               result->nlosehi[i], 100.0 * result->nlosehi[i] / result->nsamples,
               result->ntiehi[i], 100.0 * result->ntiehi[i] / result->nsamples,
               result->ev[i] / result->nsamples);
      }
    }
  }

  if (result->ordering != NULL)
    enumResultPrintOrdering(result, 0);
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

