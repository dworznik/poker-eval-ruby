// Include the Ruby headers and goodies
#include "ruby.h"
#include "poker_defs.h"
#include "enumdefs.h"

// Defining a space for information and references about the module to be stored internally
VALUE ExtPokerEval = Qnil;

// Prototype for the initialization method - Ruby calls this, not you
void Init_extpokereval();

VALUE method_holdem(VALUE self, VALUE pockets, VALUE board);


// The initialization method for this module
void Init_extpokereval() {
	ExtPokerEval = rb_define_module("ExtPokerEval");
	rb_define_protected_method(ExtPokerEval, "eval_holdem", method_holdem, 2);
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


int to_string_array(char* dest[], VALUE orig_arr) {
  int i;
  int len;
  VALUE *arr;
  VALUE orig_str;
  char *str;
  arr = RARRAY_PTR(orig_arr);
  len = RARRAY_LEN(orig_arr);
  for(i=0; i<len; i++) {
    orig_str = arr[i];
    dest[i] = RSTRING_PTR(orig_str);
  }
  return len;
}


VALUE method_holdem(VALUE self, VALUE r_pockets, VALUE r_board) {
	int i;
	char* str_pockets[ENUM_MAXPLAYERS];
	char* str_board;
	enum_game_t game = game_holdem;

	int niter = 0, npockets, nboard, err, terse, orderflag = 0;
	enum_sample_t enumType;
	StdDeck_CardMask pockets[ENUM_MAXPLAYERS];
	StdDeck_CardMask board;
	StdDeck_CardMask dead;
	enum_result_t result;
	
	StdDeck_CardMask_RESET(board);
	StdDeck_CardMask_RESET(dead);
	
	str_board = RSTRING_PTR(r_board);
	npockets = to_string_array(str_pockets, r_pockets);
	printf("npockets=%d\n", npockets);
	nboard = RSTRING_LEN(r_board)/2;

	for(i = 0; i < npockets; i++) {
		pockets[i] = TextToPokerEval(str_pockets[i]);
	}
	board = TextToPokerEval(str_board);

	err = enumExhaustive(game, pockets,				   
				   board, dead,
				   npockets, nboard, orderflag,
				   &result);
	printf("poker source:\n\n");
	enumResultPrint(&result, pockets, board);	
	return NULL;
}


