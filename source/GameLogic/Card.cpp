/*
* This file includes the function definitions for the card class.
*
* Above each function is a short description of what each function does. If
* there are any questions, please do not hesitate to contact Katie Sweet or
* Ligia Frangello.
*
* -Ligia Frangello, Katie Sweet
*/

#include "Card.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>

Card::Card() : suit(UNDEFINED), value(TWO) {}

// Constructor for a UNDEFINED card. Needed for if the client chooses to draw
// from the deck in Crazy Eight's.
Card::Card(Suit su) : suit(su), value(TWO) {
  if (suit != UNDEFINED) {
    std::string error = "Error. Cannot instantiate a card without a value.";
    throw std::invalid_argument(error);
  }
}

// Constructor for a card in a standard 52 card deck.
// Values are from 2 to 14 corrosponding from 2 - Ace.
Card::Card(Suit su, Value val) : suit(su), value(val) {
  if (val < 2 || val > 14) {
    std::string error = "Error: Tried to instantiate a card of undefined value";
    throw std::invalid_argument(error);
  }
}

// Returns the suit of a card.
Suit Card::getSuit() const { return suit; }

// Returns a value of a card.
Value Card::getValue() const { return value; }

std::string Card::printCard() const {
  std::string card = std::to_string(value) + " of ";
  if (suit == HEARTS) {
    card += "Hearts";
  } else if (suit == SPADES) {
    card += "Spades";
  } else if (suit == CLUBS) {
    card += "Clubs";
  } else {
    card += "Diamonds";
  }
  return card;
}

// Allows for the '<' comparison of two Card objects.
// Will potentially be used to sort the hand.
bool operator<(const Card &a, const Card &b) {
  if (a.getSuit() < b.getSuit()) {
    return true;
  } else if (a.getSuit() == b.getSuit()) {
    return a.getValue() < b.getValue();
  } else {
    return false;
  }
}

// Allows for the '==' comparison of two Card objects.
bool operator==(const Card &a, const Card &b) {
  if (a.getSuit() == b.getSuit() && a.getValue() == b.getValue()) {
    return true;
  } else {
    return false;
  }
}
