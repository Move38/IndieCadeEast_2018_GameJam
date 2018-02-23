#include "Serial.h"
ServicePortSerial sp;


int colorLoop = 10;
//Color colors[10]; //is colorLoop
int intColors[10];
Color currentColor;
int currentIntColor;

int colorLength;
//int count = 0;

Timer recieveTimer;
Timer blinkTimer;
bool isBlinkOn;

void setup() {
  sp.begin();

  colorLength = 3;
  blinkTimer.set(500);
  recieveTimer.set(1500);
  isBlinkOn = false;

  for(int i=0;i<colorLoop;i++){
    //colors[i] = WHITE;
    intColors[i] = -1;
  }
  //colors[0] = RED;
  //colors[1] = BLUE;
  //colors[2] = YELLOW;

  intColors[0]=0;
  intColors[1]=1;
  intColors[2]=2;

  setValueSentOnAllFaces(0);
}

void loop() {
  if(recieveTimer.isExpired()){
    int redCount = 0;
    int blueCount = 0;
    int yellowCount = 0;
    for(int i=0;i<colorLoop;i++){
      if(intColors[i] == 0){
        redCount++;
      }
      if(intColors[i] == 1){
        blueCount++;
      }
      if(intColors[i] == 2){
        yellowCount++;
      }
      /*
      if(colors[i] == RED){
        redCount++;
      }
      if(colors[i] == BLUE){
        blueCount++;
      }
      if(colors[i] == YELLOW){
        yellowCount++;
      }
      */
    }
    
    if (redCount >= colorLoop-1){
      setValueSentOnAllFaces(1); //r
    }

    if (blueCount >= colorLoop-1){
      setValueSentOnAllFaces(2); //b
    }
    if (yellowCount >= colorLoop-1){
      setValueSentOnAllFaces(3); //y
    }


      
    //sending  
    redCount = 0;
    blueCount = 0;
    yellowCount = 0;
    
    FOREACH_FACE(f) {
     
     if(!isValueReceivedOnFaceExpired(f)){
        if(getLastValueReceivedOnFace(f)==1){
          redCount++;
        }
      }
     
      if(!isValueReceivedOnFaceExpired(f)){
        if(getLastValueReceivedOnFace(f)==2){
          blueCount++;
          sp.print("Blue Count" + blueCount);
        }
      }
      
      if(!isValueReceivedOnFaceExpired(f)){
        if(getLastValueReceivedOnFace(f)==3){
          yellowCount++;
        }
      }
    }
    
   // Color recieveColor;
    //bool gotColor = false;
    int recieveIntColor = -1;

    if(redCount > blueCount && redCount > yellowCount){
      //recieveColor = RED;
      //gotColor = true;
      recieveIntColor = 0;
    }
    
    if(blueCount > redCount && blueCount > yellowCount){
      //recieveColor = BLUE;
      //gotColor = true;
      recieveIntColor = 1;
    }
    
    if(yellowCount > blueCount && yellowCount > redCount){
      //recieveColor = YELLOW;
     // gotColor = true;
     recieveIntColor = 2;
    }


    
    if(recieveIntColor > -1){
      if (colorLength < colorLoop){
        //colors[colorLength] = recieveColor;
         intColors[colorLength] = recieveIntColor;
      }
      else{
        //colors[colorLength%colorLoop] = recieveColor; //make index var
        intColors[colorLength%colorLoop] = recieveIntColor;
      }
      colorLength++;
    }
    recieveTimer.set(1500);
  }
  
  if(blinkTimer.isExpired()) {
    isBlinkOn = !isBlinkOn;
    if(isBlinkOn){
      if (colorLength < colorLoop){
        //currentColor = colors[rand(colorLength-1)];
        currentIntColor = intColors[rand(colorLength-1)];
      }else{
        //currentColor = colors[rand(colorLoop-1)];
        currentIntColor = intColors[rand(colorLoop-1)];
      }
      
      /*currentColor = colors[count];
      count++;
      if(count == colorLoop){
        count = 0;
      }*/
      
      blinkTimer.set(1000); //500
    } else{
      blinkTimer.set(100);
    }  
  }

  
  
  if(isBlinkOn) {
    //setColor(currentColor);
      if(currentIntColor==0){
        setColor(RED);
      }
      if(currentIntColor==1){
        setColor(BLUE);
      }
      if(currentIntColor==2){
        setColor(YELLOW);
      }
    
    if(buttonSingleClicked()||buttonDoubleClicked()||buttonMultiClicked()){
      if (colorLength < colorLoop){
        //colors[colorLength] = currentColor;
        intColors[colorLength] = currentIntColor;
      }
      else{
        //colors[colorLength%colorLoop] = currentColor;
        intColors[colorLength%colorLoop] = currentIntColor;
      }
      colorLength++;
      blinkTimer.set(1500);
    }
  }else {
    setColor(OFF);
  }
  
  if(buttonLongPressed()){
    setup();
  }
}
