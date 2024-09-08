#ifndef ITEM_H
#define ITEM_H

#include <string> 
#include "realItem.h"

class Menu; // Forward declaration

class Item {
    public:
        void setItemIn(std::string name, Realitem* realItem, Menu* setMenuIn);
        void setItemOut(std::string name, Realitem* realItem, Menu* setMenuOut);
        void setItemInAndOut(std::string name, Realitem* realItem, Menu* setMenuOut, Menu* setMenuIn);

        void setName(std::string name); // Use std::string
        std::string getName() const;
        bool operator==(const Item& other) const {
            // Compare les attributs pertinents pour déterminer l'égalité
            return (_name == other._name /* Comparaison d'autres attributs si nécessaire */);
        }
        Menu* getPointerIn();
        void setPointerIn(Menu* setMenuIn);

        Menu* getPointerOut();
        void setPointerOut(Menu* setMenuOut);

        Realitem* getRealItem();
        void setRealItem(Realitem* realItem);

    private:
        std::string _name; // Use std::string
        Menu* pointerIn;
        Menu* pointerOut;

        Realitem* realItem; //real item like a led ... or a switch

};

#endif