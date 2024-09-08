#include "Affichage.h"
//#include "font/FiraCodeRegular28.h"

void Affichage::render(TFT_eSprite& sprite, TFT_eSprite& sequenceSprite) {
    //In All case we calculate and print FPS
    
    sprite.setColorDepth(16);
    sprite.createSprite(320, 172);
    //sprite.loadFont(FiraCodeRegular28);

    //FPS
    int FPS = 1000/(millis() - oldTime + 1);
    oldTime = millis();
    sprite.setCursor(250, 5);
    sprite.println(String(FPS) + " FPS");
    //

    //Serial.print("isAnimationRunning :");
    //Serial.println(isAnimationRunning);

    if(elapsedAnimationTime == !NULL){
        Serial.println(elapsedAnimationTime);
    }
    

    if(!isInAction){

        

        if(isAnimationRunning){
            
            sequenceSprite.setColorDepth(16);
            sequenceSprite.createSprite(320, 172);

            int direction = (reversed) ? -1 : 1;

            elapsedAnimationTime = millis() - animationTimerBegin;

            int deltaX = easeInOutQuad(elapsedAnimationTime, 0, WIDTH, ANIMATION_DURATION_MENU);

            oldSelectedMenu->render(sequenceSprite);
            selectedMenu->render(sprite);

            Serial.print("Sprite :");
            Serial.println(deltaX*direction + 320*reversed);

            Serial.print("sequenceSprite :");
            Serial.println(deltaX*direction - 320*!reversed);
            if(!reversed){
                sequenceSprite.pushSprite(-deltaX*direction - 320*reversed, 0);
                sprite.pushSprite(-deltaX*direction + 320*!reversed, 0);
            }else{
                sprite.pushSprite(-deltaX*direction - 320*reversed, 0);
                sequenceSprite.pushSprite(-deltaX*direction + 320*!reversed, 0);
            }
            
            
        }else{
            selectedMenu->render(sprite);
            sprite.pushSprite(0, 0);
        }
        if(elapsedAnimationTime>ANIMATION_DURATION_MENU){
            //oldAnimationRunning = isAnimationRunning;
            isAnimationRunning = false;

        }
    }else{
        sprite.setTextSize(2);
        sprite.setCursor(80, 5);
        sprite.setTextColor(TFT_WHITE, TFT_BLACK);
        sprite.print(selectedMenu->getItem().getName().c_str());
        //realItem->render(sprite);
    }

}

void Affichage::enter(Feedback feedback) {
    if(!isInAction){
        Menu* nextMenu = selectedMenu->getItem().getPointerIn();
        
        if (nextMenu == nullptr) {// Handle error: The pointer is null
            Serial.print("\033[31m");
            Serial.print("Error no enter pointer found for: ");
            Serial.print("\033[0m");
            Serial.println(selectedMenu->getItem().getName().c_str());

            Realitem* newRealItem = selectedMenu->getItem().getRealItem();
            if(newRealItem == nullptr){
                Serial.println("No realItem found in the item");
            }
            else{
                realItem = newRealItem;
                Serial.println("Succesfully stored realItem from screen item");
                //feedback.setConfig();
                
                feedback.setConfig(realItem->configs[1]);
                isInAction = true; 
            }
            
        } else {
            Serial.println("Enter animation begin");
            isAnimationRunning = true;
            reversed = false;
            animationTimerBegin = millis();
            oldSelectedMenu = selectedMenu;
            selectedMenu = nextMenu;
            elapsedAnimationTime = millis() - animationTimerBegin;

            Serial.print("isAnimationRunning :");
            Serial.println(isAnimationRunning);

        }
    }
}

void Affichage::back() {
    if(!isInAction){
        Menu* nextMenu = selectedMenu->getItem().getPointerOut();

        if (nextMenu == nullptr) {// Handle error: The pointer is null
            Serial.print("\033[31m");
            Serial.print("Error no back pointer found for: ");
            Serial.print("\033[0m");
            Serial.println(selectedMenu->getItem().getName().c_str());

        } else {
            Serial.println("Back animation begin");
            isAnimationRunning = true;
            reversed = true;
            animationTimerBegin = millis();
            animationTimerBegin = millis();
            oldSelectedMenu = selectedMenu;
            selectedMenu = nextMenu;
            elapsedAnimationTime = millis() - animationTimerBegin;

            Serial.print("isAnimationRunning :");
            Serial.println(isAnimationRunning);

        }
    }else{
        isInAction = false;
    }

}

void Affichage::up() {
    if(!isInAction){
        selectedMenu->up();
    }else{
        realItem->up(true);
    }
    
}

void Affichage::down() {
    if(!isInAction){
        selectedMenu->down();
    }else{
        realItem->down(true);
    }
}

void Affichage::setMainMenu(Menu* mainMenu){
    selectedMenu = mainMenu;
}


float Affichage::easeInOutQuad(float t, float b, float c, float d) {

    float val = (1 - (1 / exp(0.03 * t))) * c;
    return val + b;
}


