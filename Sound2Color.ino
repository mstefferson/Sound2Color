// Sound2Light

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to
const int analogOutRedPin = 11;
const int analogOutGreenPin = 10;
const int analogOutBluePin = 9;
   
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int index = 0;              // Looping index
double sensorVals[6];       // Array of sensor values 
double scalingFactor = 1;

// initialize functions
void advanceStrobe();
void resetChip();
void updateColor( int colorPin, double scalingFactor, double val1, double val2 );
void setColorPwm( int colorPin, double pwm );

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

// Loop over color bins
void loop() {
  //Serial.print(index);
  // read analog
  sensorValue = analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  //store mapped value
  sensorVals[index] = outputValue;
  // Based on value update different colors
  switch(index){
    case 0: // Nothing
    case 1: 
    case 2: updateColor( analogOutRedPin, scalingFactor, sensorVals[1], sensorVals[2] );
    case 3: 
    case 4: updateColor( analogOutGreenPin, scalingFactor, sensorVals[3], sensorVals[4] );
    case 5: 
    case 6: updateColor( analogOutBluePin, scalingFactor, sensorVals[5], sensorVals[6] );
  }
  // Advance the strobe
  advanceStrobe();
  // Advance the index
  index++;
   // Reset index 
  if ( index == 7 ){
    Serial.print( " Resetting index and printing vals " );
    resetChip();
    index = 0;
      Serial.print( " [ " );
    for( int ii = 0; ii < 7; ii++ ){
      //Serial.print( " bin ");
      //Serial.print( ii );
      //Serial.print( " = " );
      Serial.print( sensorVals[ii] );
      if( ii != 6 ){
        Serial.print(", ");
      }
    }
    Serial.print( " ]" );
    Serial.print("\n \n" );
  }
}

void advanceStrobe(){
  // Set strobe to 0 and delay
  int strobe = 0; 
  delay(1);
  // Set to one and delay
  strobe = 1;
  delay(1);
  // Make sure you are not overlapping bins
  delay(3);
}

void resetChip(){
  // Set reset to 0 and delay
  int reset = 1; 
  delay(1);
  // Set to one and delay
  reset = 0;
  delay(1);
}


// update Color
void updateColor( int colorPin, double scalingFactor, double val1, double val2 ){
// pulse width modulation
double pwm = val1 + val2;
// scale it
pwm *= scalingFactor;
// set red pulse width
setColorPwm( colorPin, pwm );
}


void setColorPwm( int colorPin, double pwm ){
 analogWrite(colorPin, pwm);
}


//// update red
//void updateRed( int redPin, double scalingFactor, double val1, double val2 ){
//// pulse width modulation
//double pwm = val1 + val2;
//// scale it
//pwm *= scalingFactor;
//// set red pulse width
//setRedPwm( redPin, pwm );
//}
//
//
//// update blue
//void updateBlue( double val1, double val2 ){
//// pulse width modulation
//double pwm = val1 + val2;
//// scaling factor for pwm
//double scalingFactor = 1;
//// scale it
//pwm *= scalingFactor;
//// set red pulse width
//setBluePwm( pwm );
//}
//
//
//// update red
//void updateGreen( double val1, double val2 ){
//// pulse width modulation
//double pwm = val1 + val2;
//// scaling factor for pwm
//double scalingFactor = 1;
//// scale it
//pwm *= scalingFactor;
//// set red pulse width
//setGreenPwm( pwm );
//}
//
//void setRedPwm( double pwm ){
// const int analogOutRedPin = 8;
// analogWrite(analogOutRedPin, pwm);
//}
//
//
//void setBluePwm( double pwm )
// const int analogOutBluePin = 9;
// analogWrite(analogOutBluePin, pwm);
//}
// 
//void setGreenPwm( double pwm )
// const int analogOutGreenPin = 10;
// analogWrite(analogOutGreenPin, pwm);
//}

