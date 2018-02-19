byte value = millis() & 0b111;
byte counter = 0;
byte active = true;
Timer xx;
byte circle = 0;
byte steptimer = 100;
byte master = 0;
byte shield = 5;

void resetvariables() {
  value = millis() & 0b111;
  counter = 0;
  active = true;
  Timer xx;
  circle = 0;
  steptimer = 100;
  master = 0;
  shield = 5;
}

void setup() {
  // put your setup code here, to run once:
  setColor(OFF);
  active = true;
  xx.set(steptimer);
  resetvariables();
}

void loop() {
  // put your main code here, to run repeatedly:

  //Button press for center tile
  if (buttonPressed()) {
    if (active == true && master == 1) {
      counter = counter + 1;
      steptimer =  steptimer - 5;
      xx.set(steptimer);
    }
  }
  //Reset to neutral state
  if (buttonLongPressed()) {
    resetvariables();
  }

  //All double click checks
  if (buttonDoubleClicked()) {
    if (master == 0) {
      master = 1;
    }
    if (master == 1 && active == false) {
      counter = 0;
      setColor(GREEN);
      value = millis() & 0b111;
      active = true;
      steptimer = 100;
    }
  }

  //Active explode check

  if (active == false && isValueReceivedOnFaceExpired(circle) && master == 1) {
    explode();
  }

  //Neutral state, glowing blue waiting for input
  if (master == 0) {
    setValueSentOnAllFaces(0);
    setColor(BLUE);
    FOREACH_FACE( f ) {
      if (!isValueReceivedOnFaceExpired(f)) {
        byte neighbor = getLastValueReceivedOnFace(f);
        if (neighbor == 1) {
          master = 2;
        }
      }
    }
  }
  //Center tile state, waiting for neighbors
  else if (master == 1) {
    setValueSentOnAllFaces(1);
    setFaceColor (circle, GREEN);


    //Rotate green dot around LED circle

    if (active == true && xx.isExpired()) {
      xx.set(steptimer);
      circle++;
      setFaceColor (circle - 1, OFF);
    }
    if (circle > 5) {
      circle = 0;
    }
    if ( counter >= value ) {

      counter = 0;
      setColor(RED);
      active = false;
      setValueSentOnFace(2, circle);
    }
  }

  if (master == 2) {
    setValueSentOnAllFaces(0);

    //Shield state change check

    byte shot = 0;

    FOREACH_FACE( f ) {

      if (!isValueReceivedOnFaceExpired(f)) {
        shot = getLastValueReceivedOnFace(f);

        if (shot == 2 && shield == 2) {
          shield = 1;
        }
        else if (shot == 2 && shield == 3) {
          shield = 2;
        }
        else if (shot == 2 && shield == 4) {
          shield = 3;
        }
        else if (shot == 2 && shield == 5) {
          shield = 4;
        }
      }
    }


    //Set color based on shield health
    if (shield == 5) {
      setColor(GREEN);
    }
    if (shield == 4) {
      setColor(YELLOW);
    }
    if (shield == 3) {
      setColor(ORANGE);
    }
    if (shield == 2) {
      setColor(RED);
    }
    if (shield == 1) {
      explode();
    }
    if (shield < 1) {
      shield = 5;
    }
  }

}

void explode() {
  setFaceColor(rand(5), makeColorHSB( rand(255), 255 , rand(255) ));
  setFaceColor(rand(5), makeColorHSB( rand(255), 255 , rand(255) ));
  setFaceColor(rand(5), makeColorHSB( rand(255), 255 , rand(255) ));
  setFaceColor(rand(5), makeColorHSB( rand(255), 255 , rand(255) ));
  setFaceColor(rand(5), makeColorHSB( rand(255), 255 , rand(255) ));
  setFaceColor(rand(5), makeColorHSB( rand(255), 255 , rand(255) ));
  setFaceColor(rand(5), makeColorHSB( rand(255), 255 , rand(255) ));
  setFaceColor(rand(5), makeColorRGB( rand(255), rand(255) , rand(255) ));
  setFaceColor(rand(5), makeColorRGB( rand(255), rand(255) , rand(255) ));
  setFaceColor(rand(5), makeColorRGB( rand(255), rand(255) , rand(255) ));
  setFaceColor(rand(5), makeColorRGB( rand(255), rand(255) , rand(255) ));
  setFaceColor(rand(5), makeColorRGB( rand(255), rand(255) , rand(255) ));
  setFaceColor(rand(5), makeColorRGB( rand(255), rand(255) , rand(255) ));
  setFaceColor(rand(5), makeColorRGB( rand(255), rand(255) , rand(255) ));
  setFaceColor(rand(5), makeColorRGB( rand(255), rand(255) , rand(255) ));
}

