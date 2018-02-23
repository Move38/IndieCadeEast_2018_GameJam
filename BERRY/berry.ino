/*
   Assumed implementation for BeRrY

   designed by ViVi and Vanilla
   at IndieCade East 2018 Game Jam

   Blinks rotate color with button press.
   BLUE -> RED-> YELLOW -> BLUE...

*/

Color colors[] = { BLUE, RED, YELLOW };
byte currentColorIndex = 0;
byte faceIndex = 0;

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

  // display color
  setColor( colors[currentColorIndex] );

  // show next color
  byte nextColorIndex = (currentColorIndex + 1) % 3;
  setFaceColor( f, colors[nextColorIndex] );
}
