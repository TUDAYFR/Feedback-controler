#include "item.h"
#include "menu.h"

void Item::setName(std::string name) { // Use std::string
    _name = name;
}

std::string Item::getName() const {
    return _name;
}

Menu* Item::getPointerIn(){
    Serial.println("GetPointer");
    return pointerIn;
}

void Item::setPointerIn(Menu* setMenuIn){
    Serial.println("Pointer in is set");
    pointerIn = setMenuIn;
}

Menu* Item::getPointerOut(){
    return pointerOut;
}

void Item::setPointerOut(Menu* setMenuOut){
    Serial.println("Pointer out is set");
    pointerOut = setMenuOut;
}


Realitem* Item::getRealItem(){
    return realItem;
}

void Item::setRealItem(Realitem* setrealItem){
    realItem = setrealItem;
}


void Item::setItemIn(std::string name, Realitem* realItem, Menu* setMenuIn){
    setName(name);
    setRealItem(realItem);
    setPointerIn(setMenuIn);
}


void Item::setItemOut(std::string name, Realitem* realItem, Menu* setMenuOut){
    setName(name);
    setRealItem(realItem);
    setPointerOut(setMenuOut);
}

void Item::setItemInAndOut(std::string name, Realitem* realItem, Menu* setMenuOut, Menu* setMenuIn){
    setName(name);
    setRealItem(realItem);
    setPointerOut(setMenuOut);
    setPointerIn(setMenuIn);
}

