//
// Created by Main on 2021-09-29.
//

#include "Card.h"

Card::Card(){
    cout << "No Type specified please try again" << endl;
};

Card::Card(string t) : cardType(t){
};

string Card::getType() const{
    return cardType;
};

Card::Card(Card *c) {
    string t = c->getType();
    cardType = t;
};

Deck::Deck(){

};

//creates a deck of cards in relation to the number of card (prof didnt specify the number of cards in a deck, can be modified as needed)
Deck::Deck(int numPlayers){
    for(int i = 0; i < numPlayers; i++)
    {
        cardsHeld.push_back(new Card( "Bomb"));
        cardsHeld.push_back(new Card( "Reinforcement"));
        cardsHeld.push_back(new Card( "Blockade"));
        cardsHeld.push_back(new Card( "Airlift"));
        cardsHeld.push_back(new Card( "Diplomacy"));
    }
};


//adds a card to a deck
//note: a hand of cards can be treated as a deck and that is what is done
void Deck::ReceiveCard(Card *c)
{
    cardsHeld.push_back(c);
};

//Will take a random card from the deck and add it to the specified hand
void Deck::Draw(Hand *playerHand)
{
    srand((unsigned) time(0));
    int deckPosition = rand() % this->cardsHeld.size();
    Card *dealtCard = new Card(*cardsHeld.at(deckPosition));
    playerHand->ReceiveCard(dealtCard);
    this->cardsHeld.erase(this->cardsHeld.begin() + deckPosition);
};

//loops through all the cards and displays their type
void Deck::showCards(Deck *showDeck)
{
    for(int i = 0; i < showDeck->cardsHeld.size(); i++)
    {
        cout << "Card " << (i+1) << " is of type " << showDeck->cardsHeld.at(i)->getType() << endl;
    }
    cout << "\n" << endl;
};

Hand::Hand()
{
};
//add card to hand
void Hand::ReceiveCard(Card *c) {
    cardsHeld.push_back(c);
};
//displays all cards in hand
void Hand::ShowHandCards(Hand *showHand)
{
    for(int i = 0; i < showHand->cardsHeld.size(); i++)
    {
        cout << "The Hand Card " << (i+1) << " is of type " << showHand->cardsHeld.at(i)->getType() << endl;
    }
    cout << "\n" << endl;
}
//displays all cards in the hand, user can then choose a card to play, the card is then returned to the deck
void Hand::Play(Deck *mainDeck) {
    ShowHandCards(this);
    cout << "Choose the card you wish to play (enter a in form of a number)";
    int chosenCard;
    cin >> chosenCard;
    chosenCard--;
    Card *playedCard = new Card(this->cardsHeld.at(chosenCard));
    mainDeck->ReceiveCard(playedCard);
    this->cardsHeld.erase(this->cardsHeld.begin() + chosenCard);
};

