//
// Created by Ryan on 2021-10-05.
//

#ifndef COMP_345_PROJ_HAND_H
#define COMP_345_PROJ_HAND_H


class Hand {

public:
    Hand();
    std::vector<Card*> cardsHeld;
    //void ReceiveCard(Card *c);
    static void ShowHandCards(Hand *showHand);

};


#endif //COMP_345_PROJ_HAND_H
