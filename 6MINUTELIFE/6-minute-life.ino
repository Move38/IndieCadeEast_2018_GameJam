int level = 0;

void setup() {
  // put your setup code here, to run once:
  level = 0;
}

Color colors[] = {  
  RED,            // 1 neighbors
  ORANGE,
  YELLOW,         // 2 neighbors
  GREEN,          // 3 neighbors
  CYAN,           // 4 neighbors
  BLUE,           // 5 neighbors
  MAGENTA,        // 6 neighbors
}; 

bool longFlag = false;
int hue = 0;
int HUE_FACTOR = 3;


void loop() {
  // put your main code here, to run repeatedly:
  if (buttonDoubleClicked()) {
    if (level < FACE_COUNT) {
      level++;
    }
    
    for (int i = 0; i < level; i++) {
      setFaceColor(i, colors[i]); 
    }
    
    return;
  }

  if (buttonSingleClicked()) {
     setColor(OFF);
     
     if (level > -1) {
      level--;
    }
    
    for (int i = 0; i < level; i++) {
      setFaceColor(i, colors[i]); 
    }
    
    
    return;
  } 

  if (buttonLongPressed() && !longFlag) {
    longFlag = true;
    level = 0;
    return;
  }

  if (longFlag) {
    cycle();
  }

  if (longFlag && buttonReleased()) {
//    for (int i = 0; i < level; i++) {
//      setFaceColor(i, colors[i]); 
//    }
    setColor(OFF);
    longFlag = false;
  }
  
  } // loop()

  void cycle() {
    setColor(makeColorHSB(hue / HUE_FACTOR, 255, 255));
    hue += 1;  
    
    if (hue > 255 * HUE_FACTOR) {
       hue = 0;
    }
    
//      counter++;
//      if (counter > FACE_COUNT) {
//        counter = 0;
//      }
//    
//    for (int i = 0; i < level; i++) {
//      setFaceColor((i + counter) % FACE_COUNT, colors[i]); 
//    }
  }
