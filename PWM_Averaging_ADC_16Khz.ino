/////////////////////////////////////////////////////Averaging & filtering using map function(ADC)/////////////////////////////////////////////////////////////////////
float  voltage=0;
unsigned long average_sensorValue=0;
unsigned int i=0, count=0, value=0;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);                               // initialising pin no.3 for PWM
  TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM20);  // 16Khz PWM initialization
  TCCR2B = _BV(WGM22) | _BV(CS21);
  OCR2A = 62;
  OCR2B = 31;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  int sensorValue = analogRead(A0);
  voltage = sensorValue * (5.0 / 1023.0);
  average_sensorValue += sensorValue;                   //Addition of 100 samples of ADC for averaging
  count++;                                              // Count for 100 samples

  if(count == 120)
  {
   count = 0;
   average_sensorValue = average_sensorValue/100;       //Averaging of 100 samples 
   value = map(average_sensorValue, 30, 1023, 20, 62);
  
   if (average_sensorValue <= 30)                       //turn off PWM below 1V
   {
    value=0;
   }
   OCR2B = value;                                       //duty cycle value
  
   /////////////////Print functions///////////////////////////////////////// 
   Serial.print(OCR2B);
   Serial.print(' ');
   Serial.print(voltage);
   Serial.print(' ');
   Serial.println(sensorValue); 
   /////////////////////////////////////////////////////////////////////////
  }
}

