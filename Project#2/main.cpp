/*
    Author: Earvin Paras
    Date:   June 4th, 2022
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
    int num_ranks = 13;
    int num_suits = 4; 
};

struct Deck {
    vector<Card> cards;
    string card_back;
};

struct Player {
    vector<Card> hand; 
    int score = 0;
};

struct Game {
    int num_players = 2;
    vector<Player> players;
    Deck deck;
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
void play(Game&);
void display_state(const Game&, size_t);
Rank get_rank(const vector<Card>&);
bool is_match(const vector<Card>&, Rank);
void take_card(Game&, size_t, Rank);
void draw_card(Game&, size_t);
void check_for_score(Player&);


int main()
{
    Game game;
    play(game);
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

    for (int card = 0; card < game.num_cards_per_hand; card++)
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
    for(Card c : hand)
    {
        print_card(c);
    }
}

void initialize(Game& game)
{
    initialize(game.deck);
    shuffle(game.deck);
    add_players(game);
}

void add_players(Game& game)
{
    for(int player = 0; player < game.num_players; player++)
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

Rank get_rank(const vector<Card>& hand)
{
    bool valid = false; 
    int rank;
    while(!valid)
    {
        std::cout << "Please enter a rank: ";
        std::cin >> rank; 
        for(Card c : hand)
        {
            if(c.rank == Rank(rank))
            {
                valid = true;
            }
        }
    }

    return Rank(rank);
}

void display_state(const Game& game, size_t player)
{
    std::cout << "Your hand: \n";
    print_hand(game.players[player].hand);
    std::cout << "Your score = " << game.players[player].score << '\n';
    std::cout << "Opponent's hand: \n";
    size_t opponent = (player + 1) % game.num_players;
    print_hand(game.players[opponent].hand);
    std::cout << "Opponent's score: " << game.players[opponent].score << '\n';
    std::cout << '\n';
}

bool is_match(const vector<Card>& hand, Rank chosen_rank)
{
    bool match = false; 
    for(Card c : hand)
    {
        if(c.rank == chosen_rank)
        {
            match = true;
        }
    }

    return match;
}

void take_card(Game& game, size_t current_player, Rank chosen_rank)
{
    size_t next_player = (current_player + 1) % game.num_players;
    bool card_taken = false;
    size_t card_index = 0;
    while(!card_taken)
    {
        Card current_card = game.players[next_player].hand[card_index];
        if(current_card.rank == chosen_rank)
        {
            game.players[current_player].hand.push_back(current_card);
            game.players[next_player].hand.erase(game.players[next_player].hand.begin() + card_index);
            card_taken = true;
        }
        
        card_index++;
    }
}

void draw_card(Game& game, size_t player)
{
    if(game.deck.cards.empty())
    {
        return;
    }
    else
    {
        game.players[player].hand.push_back(game.deck.cards[0]);
        game.deck.cards.erase(game.deck.cards.begin());
    }
}

void check_for_score(Player& player)
{
    vector<bool> marked(player.hand.size(), false);
    for(size_t i = 0; i < player.hand.size() - 1; i++)
    {
        for(size_t j = i + 1; j < player.hand.size(); j++)
        {
            if(!marked[i] && !marked[j] && player.hand[i].rank == player.hand[j].rank)
            {
                marked[i] = true;
                marked[j] = true;
                player.score++;
            }
        }      
    }

    size_t card = 0;
    while(!player.hand.empty() && card < marked.size())
    {
        if(marked[card])
        {
            player.hand.erase(player.hand.begin() + card);
            marked.erase(marked.begin() + card);
        }
        else
        {
            card++;
        }
    }
}

void play(Game& game)
{
    initialize(game);
    deal_cards(game);

    bool game_over = false;
    size_t player = 0;
    while(!game_over)
    {
        display_state(game, player);

        Rank rank = get_rank(game.players[player].hand);

        size_t next_player = (player + 1) % game.num_players;

        if(is_match(game.players[next_player].hand, rank))
        {
            take_card(game, player, rank);
        }
        else
        {
            std::cout << "Go Fish.";
            draw_card(game, player);
        }

        check_for_score(game.players[player]);

        if(game.players[player].hand.empty())
        {
            game_over = true;
        }

        player = next_player;
    }

    std::cout << "Game is over.";
    for(size_t player = 0; player < game.players.size(); player++)
    {
        std::cout << "Player " << player << "'s score is " << game.players[player].score << '\n';
    }


}
