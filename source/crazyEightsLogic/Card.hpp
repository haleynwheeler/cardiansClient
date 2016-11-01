/*
 * Card Class
 *
 * -David Browning, Ligia Frangello & Katie Sweet
 *
 * The purpose of this file is to allow others to build a card object.
 * Cards contain a suit and a value.
 * Suit is an enum {HEARTS}
 *
 * The constuctor accepts the suit enum and one integer.
 *
 * The suit enum (HEARTS, SPADES, CLUBS, DIAMONDS, UNDEFINED) determines the
 * suit. The reason for the UNDEFINED suit type is that in the Player Class,
 * there is a function called requestMove() that returns a vector of Cards.
 * In the game Crazy Eight's, a move can consist of drawing a card from the
 * deck. We need an UNDEFINED type to alert the Crazy Eight's game logic that
 * they chose the draw pile instead of playing a card.
 *
 * The integer (2-14) determines the value. We have established Ace to be 14
 * instead of 1. This makes sorting easier since Ace is high in our Hearts and
 * Spades.
 *
 */
#ifndef CARD_HPP
#define CARD_HPP

#include <vector>

enum Suit
{
  HEARTS,
  SPADES,
  CLUBS,
  DIAMONDS,
  UNDEFINED
};

enum Value
{
  TWO = 2,
  THREE = 3,
  FOUR = 4,
  FIVE = 5,
  SIX = 6,
  SEVEN = 7,
  EIGHT = 8,
  NINE = 9,
  TEN = 10,
  JACK = 11,
  QUEEN = 12,
  KING = 13,
  ACE = 14
};

class Card
{
private:
  Suit suit;
  Value value;

public:
  Card(Suit su);
  Card(Suit su, Value val);
  Suit getSuit() const;
  Value getValue() const;
};

bool operator<(const Card&, const Card&);
bool operator==(const Card&, const Card&);
std::vector<Card> initializeDeck();

#endif
