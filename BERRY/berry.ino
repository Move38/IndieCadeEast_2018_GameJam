/*
   Assumed implementation for BeRrY

   designed by ViVi and Vanilla
   at IndieCade East 2018 Game Jam

   Blinks rotate color with button press.
   BLUE -> RED-> YELLOW -> BLUE...

   code by:
   Jonathan Bobrow
   2.23.2018

   Beginner mode: show the next color with a single pixel spinning every 2 seconds
   TODO: Sync the colors so they rotate the next color together
   TODO: Desync different colors so they happen in sequence

*/

Color colors[] = { BLUE, RED, YELLOW };
byte currentColorIndex = 0;
byte faceIndex = 0;
byte faceStartIndex = 0;

bool isWaiting = false;

#define FACE_DURATION 60
#define WAIT_DURATION 2000

Timer faceTimer;
Timer waitTimer;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  if ( buttonSingleClicked() ) {

    currentColorIndex++;

    if (currentColorIndex >= COUNT_OF(colors)) {
      currentColorIndex = 0;
    }

  }

  if ( waitTimer.isExpired() ) {
    if ( faceTimer.isExpired() ) {
      faceTimer.set( FACE_DURATION );
      faceIndex++;

      if (faceIndex >= 7) {
        faceIndex = 0;
        waitTimer.set( WAIT_DURATION );
        isWaiting = true;

        // shift the starting point
        faceStartIndex++;
        if(faceStartIndex >= 6) {
          faceStartIndex = 0;
        }
      }
      else {
        isWaiting  = false;
      }
    }
  }

  // display color
  setColor( colors[currentColorIndex] );

  // show next color
  if (!isWaiting) {
    byte nextColorIndex = (currentColorIndex + 1) % 3;
    byte face = (faceStartIndex + faceIndex - 1) % FACE_COUNT;
    setFaceColor( face, colors[nextColorIndex] );
  }
}
