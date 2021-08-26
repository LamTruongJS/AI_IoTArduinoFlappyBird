class Bar {

private:
  int x; 
  int y;
  int delayFrame;
  int moveSpeed;
public:   
  Bar() {
    delayFrame = 0;
    x = 0; y = 24;
    moveSpeed = 2;
  }
  
  void setPos(int sx, int sy) {
    x = sx; y = sy;
  }
  
  void render() {
    display.drawXbm(x, y - 30, 8, 20, bar_top); 
    display.drawXbm(x, y + 20, 8, 20, bar_bottom); 
  }

  void update() {
    delayFrame++;
    if (delayFrame == DELAY_FRAME) {
      
      x -= moveSpeed;
      if (x < -10) x = 95;
      
      delayFrame = 0;
    }
  }
  
  int hitTest(int tx, int ty) {
    int hitX = ((tx >= x - 20) && (tx <= x))?1:0;
    int hitY = ((ty <= (y - 19)) || (ty + 12 >= y + 10))?1:0;
    if (hitX != 0) {
      return hitY;
    }
    return 0;
  }

};

