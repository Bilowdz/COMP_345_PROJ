//
// Created by Main on 2021-10-05.
//
#include "Hand.h"

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