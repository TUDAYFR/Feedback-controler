#ifndef MENU_H
#define MENU_H

#include <vector> 
#include "item.h"
#include "TFT_eSPI.h"

#define SPACE 30
#define ANIMATION_DURATION 250
#define HEIGHT 172
#define WITH 320
#define SIDE_OFFSET 30
#define UP_OFFSET 50


class Menu {
public:
    void addItem(Item item);
    void removeItem(Item item);
    void render(TFT_eSprite& sprite);
    void up();
    void down();
    void setBoxColor(uint32_t newColor);
    std::string getMenuName();
    void setMenuName(std::string setmenuName);
    Item getItem();

private:
    std::vector<Item> items; 
    std::vector<Item> oldItems;
    std::string menuName;
    
    uint32_t boxColor;
    int itemSelected = 0;
    int oldItemSelected;
    int centerItem = 2;
    int offset = 0 ;
    int animationBegin; 

    float textAnimValue;
    float boxAnimValue;
    float interpolateNonLinear(int inValue, int maxIn, int maxOut, float power);
    float easeInOutQuad(float t, float b, float c, float d);

    boolean isAnimationRunning;
    boolean reversed;
    boolean textAnimOffset;
};

#endif