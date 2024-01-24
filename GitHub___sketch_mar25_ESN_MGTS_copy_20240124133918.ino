/*
A sample code demonstrating how the Arduino board 
was employed in the experimental reservoir computing setup
that exploits solitary-like wave in the flowing liquid films.

For details see: Maksymov, I.S. Physical Reservoir Computing Enabled by Solitary
Waves and Biologically-Inspired Nonlinear Transformation of Input Data.
Preprints 2024, 2024010412. https://doi.org/10.20944/preprints202401.0412.v1

The code is supplied as is and it is indended for use by researchers 
familiar with the principles of programming Arduino microcontrollers.
 */
int F = 2;//frequency of the generated signal in Hz, can be in the range from 0.5 Hz to 1O Hz
const int Ns = 64;//number of samples
float t;//time
int sampling_interval;
byte samples[Ns];
const float no_flow_int = 1.5;//amplitude of pumping in no flow
const float pi = 3.1415926;

const int buttonPin = 2;  // the number of the pushbutton pin

// the setup routine runs once when you press reset:
void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // the signal will be output to pin 10
  pinMode(pinOut, OUTPUT);//sets the digital pin 10 as output

  for (int n = 0; n < Ns; n++)
  {
    t = (float) n / Ns;
    samples[n] = (byte) (127.0*0.5 * sin(2.0 * pi * t) + 127.0*1.5);
  }

  sampling_interval = 1000000 / (F * Ns);//in microseconds
}

// the loop routine runs over and over again forever:
void loop()
{
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH)
  {
    //sine waves
    for (int k = 0; k < 20; k++)//20 periods of modulation
    {
      for (int j = 0; j < Ns; j++)
      {
        ard_time = millis();   Serial.print(ard_time);   Serial.print(" ");    
        analogWrite(pinOut, samples[j]);//send the generated signal to the pin
        Serial.print((float) samples[j] / 254.0);   Serial.print(" ");

        delayMicroseconds(sampling_interval);
      }
    }  
  }
  else
  {
    // NO flow modulation
    for (int k = 0; k < 20; k++)//20 periods of NO modulation
    {
      for (int j = 0; j < Ns; j++)
      {
        ard_time = millis();   Serial.print(ard_time);   Serial.print(" ");    
        analogWrite(pinOut, 127.0*1.5);//send the generated signal to the pin
        Serial.print(127.0*no_flow_int / 254.0);   Serial.print(" ");

        delayMicroseconds(sampling_interval);
      }
    }          
  }//if...else

}

