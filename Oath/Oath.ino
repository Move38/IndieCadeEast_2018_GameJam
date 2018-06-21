/*  OATH V2
 *  John Bruneau
 *  Yuxin Gao
 *  Updated: 6-15-2018
 */

#define BUTTON_HOLDOFF_DURATION 80
#define SLOTLENGTH 8 //to be fair, this should be double the banner colors
int bannerLength;
Timer buttonHoldoffTimer;

//These are the colors of all the possible players
Color banners_ary[] = {RED, makeColorRGB(0,127,255), YELLOW, GREEN};
//our blue is a little cyan

int colorSlots_ary[SLOTLENGTH];
int slotIndex = 0;

int currentColor = 0;
Timer blinkTimer;
bool isBlinkOn = false;
Timer recieveTimer;

Timer pulseTimer;
bool pulseOn = false;

/**** GET BIGGEST NUMBER IN ARRAY FUNCTION ****/

int getIndexOfMaximumValue(int* a, int count){
  int maxIndex = 0; 
  int lastIndex = -1;
  int maxVal = a[0];
  
  for (int i=1; i<count; i++){
    if (maxVal<=a[i]){
      maxVal = a[i];
      lastIndex = maxIndex;
      maxIndex = i;
    }
  }
  if (lastIndex != -1) {
    if (a [maxIndex] == a [lastIndex]) {
      maxIndex = -1;
    }
  }
  return maxIndex;
}


/***** SETUP *******/
void setup() {
  slotIndex = 0;
  isBlinkOn = false;
  blinkTimer.set(500);
  recieveTimer.set(1500);
  pulseTimer.set(20);
  bannerLength = COUNT_OF(banners_ary);
  
  //fill the color slots with colors from the banners
  //each color goes in twice.
  int halfSlots = SLOTLENGTH/2;
  for(int i=0;i<halfSlots;i++){ 
    colorSlots_ary[i] = i;
    colorSlots_ary[i+halfSlots] = i;
  }
  setValueSentOnAllFaces(9); //needed to reset color sent
}


void loop() {
  
/***** SIGNAL PULSE TIMER *******/
  //For color received visuals Only
  if(pulseTimer.isExpired()) {
    pulseOn = !pulseOn;
    if(pulseOn){
      pulseTimer.set(30);
    }else{
      pulseTimer.set(20);
    }
  }
  

/***** BLINKING *******/
  if(blinkTimer.isExpired()) {
    isBlinkOn = !isBlinkOn;
    if(isBlinkOn){
      currentColor = colorSlots_ary[rand(SLOTLENGTH-1)];
      setColor(banners_ary[currentColor]);
      blinkTimer.set(900);// 1000
    } else{
      setColor(OFF);    
      blinkTimer.set(90); //100
    }
  }

  if(isBlinkOn) {
    
    /***** SEND COLOR *******/
    int colorCount[bannerLength];  
    for(int i=0;i<bannerLength;i++){ //is this necessary?
      colorCount[i] = 0;
    }
   
    for(int i=0;i<SLOTLENGTH;i++){
      for(int j = 0; j<bannerLength;j++){
        if(colorSlots_ary[i] == j){
          colorCount[j]++;
        }
      }
    }

    setValueSentOnAllFaces(9);
    for(int i=0;i<bannerLength;i++){
      if (colorCount[i] > SLOTLENGTH-2){
        setValueSentOnAllFaces(i+1);
      }
    }

    /***** BUTTON PRESS *******/
    if( buttonPressed() && buttonHoldoffTimer.isExpired() ){
      buttonHoldoffTimer.set( BUTTON_HOLDOFF_DURATION );
      blinkTimer.set(BUTTON_HOLDOFF_DURATION+10);
      
      for(int i=0;i<6;i+=2){ //number of faces;
        setFaceColor(i, WHITE);
        setFaceColor(i+1, banners_ary[currentColor]);
      }
      //setColor(WHITE);
      colorSlots_ary[slotIndex] = currentColor;
      slotIndex++;
      if(slotIndex > SLOTLENGTH-1){
        slotIndex = 0;
      }
    }
  }else{
    
    /***** SHOW COLOR RECEIVED *******/
    FOREACH_FACE(f) {
      if(!isValueReceivedOnFaceExpired(f)){
        if(getLastValueReceivedOnFace(f) > 0 && getLastValueReceivedOnFace(f) < bannerLength+1){
          if(pulseOn){
            //pulse the recived color on the side received
            setFaceColor(f, banners_ary[getLastValueReceivedOnFace(f)-1]); 
          }else{
            //pulse white on the side received
            setFaceColor(f, WHITE);
          }
        }
      }
    } 
  }

  /***** RECEIVE COLOR *******/
  if(recieveTimer.isExpired()){
    int receiveCount[bannerLength];
    for(int i=0;i<bannerLength;i++){
      receiveCount[i] = 0; //reset count
    }
    
    FOREACH_FACE(f) {
     if(!isValueReceivedOnFaceExpired(f)){ 
        for(int i=0;i<bannerLength;i++){
          if(getLastValueReceivedOnFace(f)-1==i){
            receiveCount[i]++;
          }
        }
      }
    }
  
    int recievedColor = getIndexOfMaximumValue(receiveCount,bannerLength);
  
    if(recievedColor > -1){
      colorSlots_ary[slotIndex] = recievedColor;
      slotIndex++;
      if(slotIndex > SLOTLENGTH-1){
        slotIndex = 0;
      }
    }
    recieveTimer.set(1500); //1500
  }

/***** RESET *******/
  if(buttonLongPressed()){
    setup();
  }
}

