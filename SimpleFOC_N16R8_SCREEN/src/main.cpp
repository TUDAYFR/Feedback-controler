#include <SimpleFOC.h>
#include <NeoPixelBus.h>
#include "feedback.h"
#include "item.h"
#include "menu.h"
#include "Affichage.h"
#include "realItem.h"

#include "SPI.h"
#include "TFT_eSPI.h"

TFT_eSPI tft = TFT_eSPI();

TFT_eSprite menuSprite = TFT_eSprite(&tft);
TFT_eSprite sequenceSprite = TFT_eSprite(&tft);
TFT_eSprite FpsSprite = TFT_eSprite(&tft);

Feedback feedback;

Item wifiItem;
Item lumItem;
Item ledItem;

Menu menu;

int buttonPin1 = 11;
int buttonPin2 = 12;
int buttonPin3 = 19;
int buttonPin4 = 20;

int oldValueButton1;
int oldValueButton2;
int oldValueButton3;
int oldValueButton4;

int feedbackOldValue;

//MENU VARIABLE 

//setRealItem
Realitem LedItem;

Menu mainMenu;

//mainMenu
Item lumiere;
Item parametre;
Item wifi;

Menu subMenuLumiere;
//Lumière
Item ledChambre;
Item ledCuisine;
Item ledSalon;

Menu subMenuParametre;
//Paramètre
Item luminosite;
Item miseEnVeille;

Menu subMenuWifi;
//Wifi
Item ssid;
Item passWord;

Affichage affichage;

//END MENU VARIABLE

int counter = 0;

int oldTime =0;

//LED ON THE BOARD CONFIG
const uint16_t PixelCount = 1; 
const uint8_t PixelPin = 48;  
NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> strip(PixelCount, PixelPin);

SemaphoreHandle_t tftSemaphore = NULL;

TaskHandle_t screenTask;

void screenTaskFunc(void *pvParameters) {
  tftSemaphore = xSemaphoreCreateMutex();
  if (tftSemaphore != NULL) {

    while (true) {
      if (xSemaphoreTake(tftSemaphore, portMAX_DELAY) == pdTRUE) {
        //do task
        menuSprite.fillSprite(TFT_BLACK);
        sequenceSprite.fillSprite(TFT_BLACK);
        affichage.render(menuSprite,sequenceSprite);

        xSemaphoreGive(tftSemaphore);
      }
      vTaskDelay(pdMS_TO_TICKS(1)); // Adjust delay as needed
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin1,INPUT_PULLUP);
  pinMode(buttonPin2,INPUT_PULLUP);
  pinMode(buttonPin3,INPUT_PULLUP);
  pinMode(buttonPin4,INPUT_PULLUP);

  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(1);

  strip.Begin();
  strip.Show();

  
  
  feedback.init();  
  
  feedback.setConfig({5, 0, true,FeedbackMode::STEP});
  feedback.setFeedbackMode();

  Serial.begin(115200);

  xTaskCreatePinnedToCore(
  screenTaskFunc,     // Function to implement the task
  "ScreenTask",       // Name of the task
  8192,               // Stack size (words, not bytes)
  NULL,               // Task input parameter
  1,                  // Priority of the task
  &screenTask,        // Task handle
  1                   // Core to run the task (0 or 1)
  );


  //set Item
  LedItem.setItemType(LED);

  //set menuname 
  mainMenu.setMenuName("Menu générale");
  subMenuLumiere.setMenuName("Menu Lumière");
  subMenuWifi.setMenuName("Menu Wifi");
  subMenuParametre.setMenuName("Menu Paramètre");

  //mainMenu
  lumiere.setName("Lumiere");
  parametre.setName("Parametre");
  wifi.setName("Wifi");

  //Lumière
  ledChambre.setItemOut("LedChambre",&LedItem,&mainMenu);
  ledChambre.setRealItem(&LedItem);
  ledCuisine.setName("LedCuisine");
  ledSalon.setName("LedSalon");

  //Paramètre
  luminosite.setName("luminosité");
  miseEnVeille.setName("miseEnVeille");

  //Wifi item in Wifi menu
  ssid.setName("ssid");
  passWord.setName("passWord");

  lumiere.setPointerIn(&subMenuLumiere);
  parametre.setPointerIn(&subMenuParametre);
  wifi.setPointerIn(&subMenuWifi);

  
  ledCuisine.setPointerOut(&mainMenu);
  ledSalon.setPointerOut(&mainMenu);
  luminosite.setPointerOut(&mainMenu);
  miseEnVeille.setPointerOut(&mainMenu);
  ssid.setPointerOut(&mainMenu);
  passWord.setPointerOut(&mainMenu);

  mainMenu.addItem(lumiere);
  mainMenu.addItem(parametre);
  mainMenu.addItem(wifi);

  subMenuLumiere.addItem(ledChambre);
  subMenuLumiere.addItem(ledCuisine);
  subMenuLumiere.addItem(ledSalon);

  subMenuParametre.addItem(luminosite);
  subMenuParametre.addItem(miseEnVeille);

  subMenuWifi.addItem(ssid);
  subMenuWifi.addItem(passWord);

  mainMenu.setBoxColor(TFT_MAGENTA);

  subMenuLumiere.setBoxColor(TFT_RED);
  subMenuParametre.setBoxColor(TFT_GREEN);
  subMenuWifi.setBoxColor(TFT_BLUE);

  affichage.setMainMenu(&mainMenu);

  _delay(100);
}


void loop() {

  int valueButton1 = digitalRead(buttonPin1);
  RgbColor InterpelerColor(255, 255, 0);

  if(valueButton1 != oldValueButton1 ){
    feedback.click(valueButton1,5);

    if(valueButton1 == false){
      //ENTER
      affichage.enter(feedback);
    }
  }
  oldValueButton1 = valueButton1;

  int valueButton2 = digitalRead(buttonPin2);

  if(valueButton2 != oldValueButton2){
    feedback.click(valueButton2,5);

    if(valueButton2 == false){
      //BACK
      affichage.back();
      /*counter--;
      strip.SetPixelColor(0, InterpelerColor);
      Serial.println("CounterMoins :" + String(counter));*/
      
    }
  }
  oldValueButton2 = valueButton2;

  int valueButton3 = digitalRead(buttonPin3);
  if(valueButton3 != oldValueButton3){
    if(valueButton3 == false){
      //code for btn 3 :
      Serial.println("backTry");
      
    }
  }
  oldValueButton3 = valueButton3;

  int valueButton4 = digitalRead(buttonPin4);
  if(valueButton4 != oldValueButton4){
    if(valueButton4 == false){
      //code for btn 4 :
      
    }
  }
  oldValueButton4 = valueButton4;

  feedback.loop();
  float sensor_error = abs(feedback._motor.shaft_angle-feedback._motor.target)*20;
  RgbColor errorColor(feedback._stepValue*2 , 0, 0);
  //RgbColor errorColor(sensor_error, 0, 0);
  strip.SetPixelColor(0, errorColor);
  
  

  if(feedbackOldValue != feedback._stepValue){
    if(feedbackOldValue>feedback._stepValue){
      affichage.down();
    }else{
      affichage.up();
    }
  }
  feedbackOldValue = feedback._stepValue ;

  //Serial.println(feedback._stepValue);
  strip.Show();
}