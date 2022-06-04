/*
    Author: Earvin Paras
    Date:   May 14th, 2022
    Purpose:  Go Fish! Card Game
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;
using std::vector; 
using std::string; 

enum Rank { ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACES};
enum Suit { SPADES, HEARTS, DIAMONDS, CLUBS};

struct Card {
    Rank rank;
    Suit suit; 
    int num_suits = 4;
    int num_ranks = 13; 
};

struct Deck {
    vector<Card> cards;
    string card_back;
    int max_deck_size = 52;
};

void initialize(Deck&);
void print_deck(const Deck&);
void print_card(const Card&);
void shuffle(Deck&);
bool deal_cards(Deck&, vector<Card>&, vector<Card>&, int);
void print_hand(const vector<Card>&);

int main()
{
    Deck my_deck;
    initialize(my_deck);
    // print_deck(my_deck);
    std::cout << '\n'; 
    shuffle(my_deck);
    // print_deck(my_deck);

    vector<Card> hand_1;
    vector<Card> hand_2;
    deal_cards(my_deck, hand_1, hand_2, 7);
    print_hand(hand_1);
    std::cout << '\n';
    print_hand(hand_2);
    std::cout << '\n';
    print_deck(my_deck);

}

void initialize(Deck& deck)
{
    Card card; 
    for(int suit = 0; suit < card.num_suits; suit++)
    {
        for(int rank = 0; rank < card.num_ranks; rank++)
        {
            card.suit = Suit(suit);
            card.rank = Rank(rank); 
            deck.cards.push_back(card);
        }
    }
}

void print_deck(const Deck& deck)
{
    for(Card c : deck.cards)
    {
        print_card(c);

    }
}

void print_card(const Card& card)
{
    std::cout << "Rank = " << card.rank << "  " << "Suit = " << card.suit << '\n';
}

void shuffle(Deck& deck) 
{
    Deck shuffled;
    while (!deck.cards.empty())
    {
        size_t rand_index = rand() % deck.cards.size();
        shuffled.cards.push_back(deck.cards[rand_index]);
        deck.cards.erase(deck.cards.begin() + rand_index);
    }

    deck = shuffled;
} 

bool deal_cards(Deck& deck, vector<Card>& hand_1, vector<Card>& hand_2, int num_cards)
{
    if (deck.cards.size() < 2 * num_cards)
    {
        return false;
    }

    for (int card = 0; card < num_cards; ++card)
    {
        hand_1.push_back(deck.cards[0]);
        deck.cards.erase(deck.cards.begin());
        hand_2.push_back(deck.cards[0]);
        deck.cards.erase(deck.cards.begin());
    }

    return true;
}

void print_hand(const vector<Card>& hand)
{
    for (Card c : hand)
    {
        print_card(c);
    }
}
