#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h"


SSD1306  display(0x3c, 4, 5);
#include "Sprite.h"
#include "Chym.h"
#include "Bar.h"

Chym player;
Bar bar; Bar bar2;
int gameScore = 0;

int KNOCK_PIN = 0;
int LED_PIN = 16;

boolean clicked = false;

void loop() {
  getInput();
  player.update();
  bar.update(); bar2.update();
  drawLCD();
}

void resetGame() {
  player.respawn();
  bar.setPos(0, 20);
  bar2.setPos(50, 30);
  gameScore = 0;
}

void setup() {
  display.init();

  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.display();

  digitalWrite(LED_PIN, HIGH);

  pinMode(KNOCK_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
//  display.flipScreenVertically();
  resetGame();
  Serial.begin(115200);
  
}


bool shortPress()
{
  static int lastPress = 0;
  if (millis() - lastPress > 5 && digitalRead(KNOCK_PIN) == 0) {
    return true;
  } else if(digitalRead(KNOCK_PIN) == 1){
    lastPress = millis();
  }
  return false;
}
void getInput() {
  if (shortPress()) { // push down
    clicked = true;
  }
  else {
    clicked = false;
  }
}

void drawLCD() {
  display.clear();

  if (!player.isDead()) {
    int ht1 = bar.hitTest(player.getX(), player.getY());
    int ht2 = bar2.hitTest(player.getX(), player.getY());
    int die = ht1 + ht2;
    if (die == 1) {
      // game over
      player.die();
    }

    if (clicked) {
      player.flyUp();
    }
    else {
      player.cancelJump();
    }
    player.render();

    bar.render(); bar2.render();
  }
  else {
    display.drawString(0, 0, "Game   Over!!!");
    
    if (clicked) {
      resetGame();
    }
  }

  display.display();
}

