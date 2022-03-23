int redPin = 10;
int greenPin = 9;
int bluePin = 11;

int xAxis = A0;
int yAxis = A1;

int lightSensor = A2;

String input;
char selector;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(xAxis, INPUT); //center is (504, 517), min X is 0, max X is 1023
  pinMode(yAxis, INPUT); // min Y is 0, max Y is 1023

  pinMode(lightSensor, INPUT); //0 to 1023, with 0 being dark and 1023 being bright
  //this sensor is broken
}

void loop() {
  
  
  if (Serial.available())
  {
    input = Serial.readString();
    selector = input[0];
    Serial.print("Received: ");
    Serial.println(input);
  }

  switch(selector)
  {
    case 'j':
      //joystick code
      joyStickFunction();
      break;
    case 'L':
      //lightsensor code
      lightSensorFunction();
      break;
    case 'r':
      //LED red
      LEDFunction('r', input[1]);
      break;
    case 'g': 
      //LED green
      LEDFunction('g', input[1]);
      break;
    case 'b':
      //LED blue
      LEDFunction('b', input[1]);
      break;
    default:
      break;
  }

  delay(1000);
}

void joyStickFunction()
{
  int xValue, yValue;
  
  xValue = analogRead(xAxis);
  yValue = analogRead(yAxis);

  
  if (xValue > 760)
  {
    if (yValue > 770)
    {
      Serial.println("UPPER-LEFT");
    }
    else if (yValue < 259)
    {
      Serial.println("LOWER-LEFT");
    }
    else
    {
      Serial.println("LEFT");
    }
  }
  else if (xValue < 252)
  {
    if (yValue > 770)
    {
      Serial.println("UPPER-RIGHT");
    }
    else if (yValue < 259)
    {
      Serial.println("LOWER-RIGHT");
    }
    else
    {
      Serial.println("RIGHT");
    }
  }
  else
  {
    if (yValue > 770)
    {
      Serial.println("UP");
    }
    else if (yValue < 259)
    {
      Serial.println("DOWN");
    }
    else
    {
      Serial.println("CENTER");
    }
  }
}

void lightSensorFunction()
{
  int lightValue;
  float value;
  lightValue = analogRead(lightSensor);
  value = (lightValue / 1023) * 100;
  // int result = (lightValue * 100)/ 1023; //Why does this not work
  Serial.print(value);
  Serial.println("%");
}

void LEDFunction(char color, char brightness)
{
  int analogLED;
  if (brightness == '1')
  {
    analogLED = 10;
  }
  else if (brightness == '2')
  {
    analogLED = 100;
  }
  else
  {
    analogLED = 255;
  }
  
  switch(color)
  {
    case 'r':
      delay(1000);
      analogWrite(redPin, analogLED);
      Serial.println("RED");
      delay(1000);
      analogWrite(redPin, LOW);
      break;
    case 'g':
      delay(1000);
      analogWrite(greenPin, analogLED);
      Serial.println("GREEN");
      delay(1000);
      analogWrite(greenPin, LOW);
      break;
    case 'b':
      delay(1000);
      analogWrite(bluePin, analogLED);
      Serial.println("BLUE");
      delay(1000);
      analogWrite(bluePin, LOW);
      break;
    default:
      delay(1000);
      analogWrite(redPin, analogLED);
      Serial.println("RED");
      delay(1000);
      analogWrite(redPin, LOW);
      break;
  }
}
