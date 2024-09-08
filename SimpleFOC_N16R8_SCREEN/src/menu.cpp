#include "menu.h"
#include "item.h" 

void Menu::addItem(Item item) {
    //item.setPointerOut(this);
    items.push_back(item);
}

void Menu::setMenuName(std::string setmenuName){
    menuName = setmenuName;
}

std::string Menu::getMenuName(){
    return menuName;
}

void Menu::up() {
    if(!isAnimationRunning  && itemSelected > 0 ){
        reversed = true;
        isAnimationRunning = true;
        oldItemSelected = itemSelected;
        itemSelected--;
    }
}


void Menu::down() { 
    if(!isAnimationRunning && itemSelected < items.size()-1){
        reversed = false;
        isAnimationRunning = true;
        oldItemSelected = itemSelected;
        itemSelected++;
    }
}


void Menu::removeItem(Item item) {
    
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (*it == item) {
            items.erase(it);
            break; 
        }
    }
}

Item Menu::getItem(){
    return items[itemSelected];
}

float Menu::easeInOutQuad(float t, float b, float c, float d) {
    t /= d / 2;
    if (t < 1) return c / 2 * t * t + b;
    t--;
    return -c / 2 * (t * (t - 2) - 1) + b;
}

void Menu::setBoxColor(uint32_t newColor){
    boxColor = newColor ; 
}

void Menu::render(TFT_eSprite& sprite) { // render of the menu on the screen
    
    const int oneLetterSize = 15; // in pixels
    int direction = (reversed) ? -1 : 1;

    //RENDER BANDEROLE
    sprite.setTextSize(2);
    sprite.setCursor(80, 5);
    sprite.setTextColor(TFT_WHITE, TFT_BLACK);
    sprite.print(menuName.c_str());
    sprite.fillSmoothRoundRect(20,25,320-20-20,5,3,boxColor);
    //

    boxAnimValue = items[itemSelected].getName().size()*oneLetterSize;
    textAnimValue = SPACE;


    if (isAnimationRunning) {

        if (animationBegin == 0) {
            animationBegin = millis();
        }

        int elapsedTextAnimationTime = millis() - animationBegin;

        const int inBoxSize = items[oldItemSelected].getName().size() * oneLetterSize;
        const int outBoxSize = items[itemSelected].getName().size() * oneLetterSize;

        if (elapsedTextAnimationTime <= ANIMATION_DURATION) {
            boxAnimValue = easeInOutQuad(elapsedTextAnimationTime, inBoxSize, outBoxSize - inBoxSize, ANIMATION_DURATION);
            textAnimValue = easeInOutQuad(elapsedTextAnimationTime, 0, SPACE, ANIMATION_DURATION);
        } else {
            isAnimationRunning = false;
            animationBegin = 0;
        }
    }

    int numberOfItemsOnScreen = (HEIGHT - SPACE) / SPACE;
    


    // Centering Logic
    if (itemSelected - centerItem < -2) {
        centerItem = std::max(0, centerItem - 1);
        isAnimationRunning = true;
        textAnimOffset = true;
        offset++;
    }

    
    if (itemSelected - centerItem > 2) {
        centerItem = std::min(static_cast<int>(items.size()) - 1, centerItem + 1);
        isAnimationRunning = true;
        textAnimOffset = true;
        offset--;
    }

    // Box Drawing Logic
    int boxPlace = itemSelected + offset;
    int boxY = UP_OFFSET -15 + SPACE *boxPlace;

    
    if (isAnimationRunning && !textAnimOffset) {
        boxY =UP_OFFSET -15  + SPACE * (oldItemSelected+offset) + textAnimValue * direction;
    }
    sprite.fillSmoothRoundRect(SIDE_OFFSET - 5, SPACE / 4 + boxY, boxAnimValue, SPACE, 6, boxColor, TFT_BLACK);

    //text anim offset
    int y = UP_OFFSET;
    if(textAnimOffset){
        y -= textAnimValue*direction -SPACE*direction;
        textAnimOffset = isAnimationRunning;
    }

    for (int i = centerItem - numberOfItemsOnScreen / 2; i <= centerItem + numberOfItemsOnScreen / 2; i++) {
        if (i >= 0 && i < items.size()) {
            sprite.setCursor(SIDE_OFFSET, y);
            sprite.setTextColor(TFT_WHITE);
            sprite.setTextSize(2);
            //sprite.println("oo");
            sprite.println(items[i].getName().c_str());
            y += SPACE;
        }
    }
    //sprite.setCursor(250, 100);
    //sprite.println( items[itemSelected].getName().c_str() );
    
}


