#include <TimerOne.h>

int redPin = 10;
int greenPin = 9;
int bluePin = 11;

//int lightSensorPin = A2;

int addingCounter = 0;
int sortingCounter = 0;
int printingCounter = 0;

int timeBetweenFunctions = 100000; //from 1 to 8388480, or 1 mircosecond to 8.3 seconds

String possibleFunctions[] = {"Adding Numbers", "Sorting", "Printing"};
//char possibleFunctions[][] = {"Adding Numbers", "Sorting", "Printing"};

volatile unsigned int functionToStart = 0;
unsigned int functionController = 0;

int numArray[700];

int arraySize = sizeof(numArray) / sizeof(numArray[0]); 

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);

  Timer1.initialize(timeBetweenFunctions);
  Timer1.attachInterrupt(changeFunction);
}

void loop() 
{
  noInterrupts();
  //time sensitive:

  functionController = functionToStart;

  if(functionController >= 3)
  {
    functionToStart = 0;
  }

  Serial.print("Current Function Is = ");
  Serial.println(possibleFunctions[functionController]);

  switch(functionController)
  {
    case 0: addToArray(); break;
    case 1: sortArray(); break;
    case 2: printArray(); break;
  }

  interrupts();
  //not time sensitive:
}

void changeFunction()
{
  Serial.println("Time To Switch!");
  functionToStart++;
}


void addToArray()
{
   digitalWrite(redPin, HIGH);

   addingCounter++;
   if(addingCounter > arraySize)
   {
     addingCounter = 0;
   }
   
   if (addingCounter == 0 && sortingCounter != 0)
   {
    Serial.println("Waiting For Sort To Finish");
    Serial.println();
    return
   }
   
   int num = random(0, 1001);
   numArray[addingCounter] = num;  
   
   digitalWrite(redPin, LOW);
}

void sortArray()
{
  // blue LED
  digitalWrite(bluePin, HIGH);


  
  digitalWrite(bluePin, LOW);
}

void partition()
{
  
}

void printArray()
{
  digitalWrite(greenPin, HIGH);
  
  printingCounter++;
  if (printingCounter > arraySize)
  {
    printingCounter = 0;
  }

  Serial.print("Number at ");
  Serial.print(printingCounter);
  Serial.print(" is: ");
  Serial.println(numArray[printingCounter]);
  Serial.println();
  
  delay(300);
  digitalWrite(greenPin, LOW);
}
