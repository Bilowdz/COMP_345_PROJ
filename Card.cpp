//
// Created by Main on 2021-09-29.
//

#include "Card.h"
//creating card constructors
Card::Card(){
    cout << "No Type specified please try again" << endl;
};

//basic constructor
Card::Card(string t) : cardType(t){
};

//copy constructor
Card::Card(Card const  &copyCard) {
    cardType = copyCard.cardType;
}

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

//copy constructor
Deck::Deck(const Deck &copyDeck) {
    cardsHeld = copyDeck.cardsHeld;
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

//destructor for the deck
Deck::~Deck() {
    for(int i = 0; i < cardsHeld.size(); i++)
        delete cardsHeld.at(i);
};

//adds a card to a deck
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
Hand::Hand() = default;

Hand::Hand(vector<Card*> cardsHeld) {
    this->cardsHeld = cardsHeld;
}

//copy constructor
Hand::Hand(const Hand &copyHand) {
    cardsHeld = copyHand.cardsHeld;
};

//destructor for the deck
Hand::~Hand() {
    for(int i = 0; i < cardsHeld.size(); i++)
        delete cardsHeld.at(i);
}

//add card to hand
void Hand::ReceiveCard(Card *c) {
    this->cardsHeld.push_back(c);
};

bool Hand::isCardOwned(string playerCardType) {

    for (int i = 0; i < this->cardsHeld.size(); ++i) {
        if (this->cardsHeld.at(i)->cardType.compare(playerCardType) == 0) {
            return true;
        }
    }
    return false;
}

//displays all cards in the hand, user can then choose a card to play, the card is then returned to the deck
OrdersList Hand::Play(Deck *mainDeck, OrdersList *o) {
    cout << *this << endl;
    cout << "Choose the card you wish to play (enter in the form of a number)";
    int chosenCard;
    cin >> chosenCard;
    chosenCard--;
    Card *playedCard = new Card(*this->cardsHeld.at(chosenCard));
    mainDeck->ReceiveCard(playedCard);
    this->cardsHeld.erase(this->cardsHeld.begin() + chosenCard);
    //Orders newOrder;

    if(this->cardsHeld.at(chosenCard)->cardType.compare("Bomb")){
        o->addBomb(new Bomb());
    } else if(this->cardsHeld.at(chosenCard)->cardType.compare("Reinforcement")){
        o->addAdvance(new Advance());
    } else if(this->cardsHeld.at(chosenCard)->cardType.compare("Blockade")){
        o->addBlockade(new Blockade());
    } else if(this->cardsHeld.at(chosenCard)->cardType.compare("Airlift")){
        o->addAirlift(new Airlift());
    } else if(this->cardsHeld.at(chosenCard)->cardType.compare("Diplomacy")){
        o->addNegotiate(new Negotiate());
    }
    return *o;
};

//string insertion operator
std::ostream &operator<<(std::ostream &out, const Hand &showHand) {
    cout << "The hand has " << endl;
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

