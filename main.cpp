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

struct Player {
    vector<Card> hand; 
    string name;
    int score;
};

struct Game {
    vector<Player> players;
    Deck deck;
    int num_players = 2;
    int num_cards_per_hand = 7;
};

void initialize(Deck&);
void print_deck(const Deck&);
void print_card(const Card&);
void shuffle(Deck&);
bool deal_cards(Game&);
void print_hand(const vector<Card>&);
void initialize(Game&);
void add_players(Game&);
void print_game(const Game&);

int main()
{
    Game game;
    initialize(game);
    deal_cards(game);
    print_game(game);
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

bool deal_cards(Game& game)
{
    if (game.deck.cards.size() < game.num_players * game.num_cards_per_hand)
    {
        return false;
    }

    for (int card = 0; card < game.num_cards_per_hand; ++card)
    {
        for(int player = 0; player < game.num_players; player++)
        {
            game.players[player].hand.push_back(game.deck.cards[0]);
            game.deck.cards.erase(game.deck.cards.begin());
        }
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

void initialize(Game& game)
{
    intialize(game.deck);
    shuffle(game.deck);
    add_players(game);
}

void add_players(Game& game)
{
    for(int player = 0; player < game.num)_players; player++)
    {
        Player new_player;
        game.players.push_back(new_player);
    }
}

void print_game(const Game& game)
{
    for (int player = 0; player < game.num_players; player++)
    {
        print_hand(game.players[player].hand);
        std::cout << '\n'; 
    }

    print_deck(game.deck);
}