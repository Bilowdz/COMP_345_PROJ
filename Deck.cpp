//
// Created by Main on 2021-09-29.
//

#include "Deck.h"

Deck::Deck(){

};

//creates a deck of cards in relation to the number of card (prof didnt specify the number of cards in a deck, can be modified as needed)
Deck::Deck(int numPlayers){
    for(int i = 0; i < numPlayers; i++)
    {
        cardsHeld.push_back(new Card((string *) "Bomb"));
        cardsHeld.push_back(new Card((string *) "Reinforcement"));
        cardsHeld.push_back(new Card((string *) "Blockade"));
        cardsHeld.push_back(new Card((string *) "Airlift"));
        cardsHeld.push_back(new Card((string *) "Diplomacy"));
    }
};


//adds a card to a deck
//note: a hand of cards can be treated as a deck and that is what is done
void Deck::ReceiveCard(Card *c)
{
    cardsHeld.push_back(c);
}

//for each member in the "otherdeck" array a vector item from the main deck is chosen at random, that card is copied to one deck in "otherdeck" and then that item is deleted from the main deck
void Deck::Deal(Deck *otherDeck[])
{
    for(int j = 0; j < 3; j++)
    {
        for (int i = 0; i < sizeof(&otherDeck); i++) {
            srand((unsigned) time(0));
            int deckPosition = rand() % this->cardsHeld.size();
            string ct = cardsHeld.at(deckPosition)->getType();
            string *card = &ct;
            Card *dealtCard = new Card(card);
            otherDeck[i]->ReceiveCard(dealtCard);
            this->cardsHeld.erase(this->cardsHeld.begin() + deckPosition);
        }
    }
}
//loops through all the cards and displays their type
void Deck::showCards()
{
    for(int i = 0; i < this->cardsHeld.size(); i++)
    {
        cout << "Card " << (i+1) << "is of type" << cardsHeld.at(i)->getType() << endl;
    }
}