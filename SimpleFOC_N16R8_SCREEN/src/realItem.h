#ifndef REALITEM_H
#define REALITEM_H

#include "TFT_eSPI.h"
#include "feedback.h"

enum ItemType {
    LED,LUMINISITY,
};


class Realitem{
    public:
        void setItemType(ItemType itemType);
        void render(TFT_eSprite& sprite);
        ItemType getItemType();
        void up(boolean hold);
        void down(boolean hold);
        

        int luminosity=0;

        MotorConfig configs[1] = {
            {10, 10, false,FeedbackMode::STEP} 
        };

    private:
        ItemType _itemType;
        


};

#endif