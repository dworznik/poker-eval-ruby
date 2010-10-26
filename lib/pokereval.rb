require 'extpokereval'

class PokerEval
  self.extend ExtPokerEval

  def self.holdem(pockets, board)
	self.eval_holdem(pockets, board)
  end
end
