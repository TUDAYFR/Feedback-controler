#include "realItem.h"
#include "feedback.h"

void Realitem::setItemType(ItemType itemType){
    _itemType = itemType ;
}

ItemType Realitem::getItemType(){
    return _itemType;
}


void  Realitem::render(TFT_eSprite& sprite){
        switch (_itemType)
        {
        case LED:
            //setup MotionControlType


            sprite.setCursor(80, 50);
            sprite.print("LUM");
            sprite.setCursor(125, 50);
            sprite.print(luminosity);
            sprite.fillSmoothRoundRect(20,25,320-20-20,5,3,TFT_DARKGREY);

            break;

        case LUMINISITY:
            
            break;
        default:
            break;
        }

        sprite.pushSprite(0,0);

}

void Realitem::up(boolean hold){
    switch (_itemType)
    {
    case LED:
        luminosity++;
        break;
    
    default:
        break;
    }

}

void Realitem::down(boolean hold){
    switch (_itemType)
    {
    case LED:
        luminosity--;
        break;
    
    default:
        break;
    }

}
