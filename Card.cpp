//
// Created by Main on 2021-09-29.
//

#include "Card.h"
//creating card constructors
Card::Card(){
    cout << "No Type specified please try again" << endl;
};

Card::Card(string t) : cardType(t){
};

Card::Card(Card *c) {
    string t = c->getType();
    cardType = t;
};
//returns the card's type
string Card::getType() const{
    return cardType;
};

//string insertion operators
std::ostream &operator<<(std::ostream &out, const Card &c) {
    out << "{ Card Type: " << c.cardType << "}" << std::endl;
    return out;
}

//assignment operator
Card& Card::operator =(const Card &c) {
    this->cardType = c.cardType;

    return *this;
}
//creating deck constructors
Deck::Deck(){

};

Deck::Deck(Deck *d) {
    vector <Card *> t = d->cardsHeld;
    cardsHeld = t;
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

//string insertion operator
std::ostream &operator<<(std::ostream &out, const Deck &showDeck) {
    out << "The deck has" << endl;
    for(int i = 0; i < showDeck.cardsHeld.size(); i++)
    {
        out << "Card " << (i+1) << " is of type " << showDeck.cardsHeld.at(i)->getType() << endl;
    }
    return out;
}
//assignment operator
Deck& Deck::operator =(const Deck &d) {
    this->cardsHeld = d.cardsHeld;

    return *this;
}
//creating Hand constructors
Hand::Hand()
{
};

Hand::Hand(Hand *h) {
    vector <Card *> t = h->cardsHeld;
    cardsHeld = t;
};

//add card to hand
void Hand::ReceiveCard(Card *c) {
    cardsHeld.push_back(c);
};

//displays all cards in the hand, user can then choose a card to play, the card is then returned to the deck
void Hand::Play(Deck *mainDeck) {
    cout << *this << endl;
    cout << "Choose the card you wish to play (enter a in form of a number)";
    int chosenCard;
    cin >> chosenCard;
    chosenCard--;
    Card *playedCard = new Card(*this->cardsHeld.at(chosenCard));
    mainDeck->ReceiveCard(playedCard);
    this->cardsHeld.erase(this->cardsHeld.begin() + chosenCard);
};

//string insertion operator
std::ostream &operator<<(std::ostream &out, const Hand &showHand) {
    cout << "The hand has has" << endl;
    for(int i = 0; i < showHand.cardsHeld.size(); i++)
    {
        cout << "Card " << (i+1) << " is of type " << showHand.cardsHeld.at(i)->getType() << endl;
    }
    return out;
}

//assignment operator
Hand& Hand::operator =(const Hand &h) {
    this->cardsHeld = h.cardsHeld;

    return *this;
}