#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "menu.h"  
#include "realItem.h"
#include "feedback.h"

#include <FreeRTOS.h>
#include <queue>

#define ANIMATION_DURATION_MENU 250
#define WIDTH 320

class Affichage {
public:
    void render(TFT_eSprite& sprite, TFT_eSprite& sequenceSprite);
    void enter(Feedback feedback);
    void back();
    void up();
    void down();
    void setMainMenu(Menu* mainMenu);
    float easeInOutQuad(float t, float b, float c, float d);
    

private:
    Menu* selectedMenu;    //Menu selectionée à afficher
    Menu* oldSelectedMenu;
    //Menu* nextMenu;

    boolean isAnimationRunning; //When in a annimation between two menu 
    boolean isInAction; //Action to make when you click on a item with a ItemType

    //boolean oldAnimationRunning;
    boolean reversed;

    int oldTime;

    int animationTimerBegin;
    int elapsedAnimationTime; 

    Item* actionItem; //Choosen item to print the action

    Realitem* realItem; //real item like a led ... or a switch

 
};

#endif