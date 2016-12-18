/*...........Digital Lock System Project................................................................*/
/*...........Purpose: To create a system that simulates an electronic door lock.........................*/
/*...........School: Florida Altantic University........................................................*/
/*...........Names and Major: Carl Jules (Computer Engineer) & Alex Rodriguez (Electrical Engineer).....*/
/*...........Professor: Dr. Ravi Shankar................................................................*/
/*...........Date: December 17, 2016....................................................................*/


#include <LiquidCrystal.h>
#include <msp430.h> // Use this library for the delay cycles in this library.

LiquidCrystal lcd(P1_6, P1_7, P2_0, P2_1, P2_2, P2_3); // Pins for the LCD Screen
const int COL[] ={P2_5,P2_6,P2_7}; // Pins for columns
const int ROW[] = {P1_4,P1_5,P1_0,P2_4};  // Pins for Rows
char keys[4][3] = {
  {'1','2','3'},			// For this project we had a
  {'4','5','6'},			// 4x3 keypad, this can be changed to any size
  {'7','8','9'},			// keypad, provided the microprocessor has enough
  {'*','0','#'}				// pins for connection.
};
char password[] = {'0', '1', '2', '3'}; // Hard coded password, the programmer creates.
int lcd_column=0;
int lcd_row=0;
int flag =0;		// This check if password is correct (flag=0) or incorrect (flag=1)
int granted =0;		// If access is granted (granted=1) if not (granted =0)
int choice =0;		// Once access has been granted the user has 2 options, if
					// (choice=1) then user can lock the system, if (choice=2)
					// user can change the password.

void setup() 
{
	// This function sets up the lcd display. The display is a 2x16 display
	// which has 2 rows and 16 coumns.
	P1OUT |= 0xFF;
	P1DIR &= ~BIT3;
    for (int v=0;v<3;v++)
  {
  pinMode(COL[v], INPUT);
  }
  for (int j=0;j<4;j++)
  {
    pinMode(ROW[j],OUTPUT);
   digitalWrite(ROW[j],LOW);
  }
lcd.begin(16, 2);

}
void loop()
{
	lcd.setCursor(0,0);				// Use the setCursor function to set the initial
									// position where you want the message to start.
									// The lcd.setCursor(columns,rows).

// In this part of the code the user will input the password that the
// programmer has provided, then if the access is granted the bit for the
// solenoid will turn high, meaning the system has unlock.


if(granted == 0)
{
  lcd.print("Enter Password: ");
  lcd.setCursor(0,1);



   for(int w=0;w<4;w++)				// Reading the keypad's rows
    {  digitalWrite(ROW[w],HIGH);

      for(int x=0;x<3;x++)			// Reading the keypad's columns
      {  if(digitalRead(COL[x])==HIGH)
            {
    	  	  delay(500);			// This delay helps reduce the sensitivity of the keypad
    	  	  	  	  	  	  	  	// This is a built in function within the LiquidCrystal.h library.
              lcd.setCursor(lcd_column++,1);
              lcd.print('*');		// Instead of printing the number, print a star.

              // If password is incorrect then the flag will go to 1 which means the password is incorrect.
              if (password[lcd_column -1] != keys [w][x])
                                  {flag++;}

              // We made a 4 digit password, however the programmer can change it to any length it wants.
              if((lcd_column==4))
              {
                lcd_column=0;
                __delay_cycles(10000000);
                	lcd.clear();
                // This code is for when the password is wrong
                if (flag != 0)
                {

                	lcd.setCursor(0,0);
                	lcd.clear();
                	// This variable 'time' will tell the programmer how many times
                	// the message and the buzzers will be on for.
                	for(int time = 0; time < 12; time ++)

                	{
                	// In this step we went with a little bit more style
                	// we created a lop that makes the buzzers and the message
                	// to be displayed in intervals to simulate an alarm.
                	lcd.print("Access Denied!!");
                	P1DIR |= BIT1;           // Bit for the buzzer 1 go high.
                	P1DIR |= BIT2;			 // Bit for the buzzer 2 go high.
                	__delay_cycles(5000000); // Delay to make the buzz in intervals
                	lcd.clear();
                	P1DIR &= ~BIT1;			// Buzzer 1 and 2 go off.
                	P1DIR &= ~BIT2;
                	__delay_cycles(1000000); // These delays can be change by the preferance
                							 // of the user.
                	}
                	granted = 0;		// Flag and granted variables go back to zero
                	flag =0;			// to make the user to retry new password.

                }
                else
                {
                	// If flag is equal zero, then the password is correct and the
                	// user can input
                	lcd.setCursor(0,0);
                	lcd.clear();

                	lcd.print("Access Granted");
                	P1DIR |= BIT3; // Bit for solenoid goes high.
                	for(int time = 0; time < 4; time ++) // Shorter time interval for buzzer 1 to go off.
                	{
                	P1DIR |= BIT1;  // Bit for buzzer 1 goes high.
                	__delay_cycles(1000000); // Delay for buzzer 1 to go on.
                	P1DIR &= ~BIT1;
                	__delay_cycles(1000000);
                	}
                	__delay_cycles(20000000); // Delay cycle for message
                	granted = 1;
                	flag = 0;
                }

              }
     }
      }
       digitalWrite(ROW[w],LOW);
       __delay_cycles(150000);
    }
 }
// This is the code when granted is = 1 which means that the user inputted the password right.
if(granted == 1)
{
	// We introduce a new variable which is 'choice' , this will allow the user to
	// either change the password when they press '#' or lock the system when they
	// press '*'.
	if(choice == 0)
	{
	lcd.setCursor(0,0);
	lcd.print("Lock System: *");
	lcd.setCursor(0,1);
	lcd.print("Change Pass: #");
	// This is the same code used before to read the keypad
	// and we will use it to verify which keys the user press
	// notice that user can input any keys , even by mistake, the system will only
	// go on if the user innputs either the '#' or '*'.
	for(int w=0;w<4;w++)
	    {  digitalWrite(ROW[w],HIGH);

	      for(int x=0;x<3;x++)
	      {  if(digitalRead(COL[x])==HIGH)
	            {
	    	  	  delay(500);
	              if ('*'== keys [w][x]) // Checks to see if user inputs '*'.
	                  {choice=1;		 // Sets choice = 1 to go on into the 'locking system' loop.
	                  lcd.clear();}
	              if ('#'== keys [w][x]) // Checks to see if user inputs '#'.
	              {choice=2;			 // Sets Choice =2  to go on into the 'changing password' loop.
	              lcd.clear();}
	            }
	      }

	       digitalWrite(ROW[w],LOW);
	       __delay_cycles(150000);
	    }
	}
		if (choice==1)
		{
			// This just locks the system and sends the user to input the password.
			// Variables are set back to zero to rest them.
			granted=0;
			P1DIR &= ~BIT3; // Solenoid is locked
			choice=0;
		}
		if (choice==2)
		{
			// This is the loop for allowing the user to change the password.
			lcd.setCursor(0,0);
			lcd.print("Change Password: ");
			lcd.setCursor(0,1);


			// Readings the keypad using the same code we use before.
			// User inputs the password  he/she desires.
     for(int w=0;w<4;w++)
      {  digitalWrite(ROW[w],HIGH);

        for( int x=0;x<3;x++)
        {  if(digitalRead(COL[x])==HIGH)
              {
      	  	  delay(500);
                lcd.setCursor(lcd_column++,1);
                lcd.print(keys [w][x]);

                password[lcd_column -1] = keys [w][x]; // Password gets stored.


                // Password Message displays.
                if((lcd_column==4))
                {
                  lcd_column = 0;
                  __delay_cycles(5000000);
                  lcd.clear();
                  lcd.setCursor(0,0);
                  lcd.print("Password Changed");
                  __delay_cycles(50000000);
                  granted = 0;
                  P1DIR &= ~BIT3; // Solenoid Locks and resets everything.


                  choice=0;
                  }

                }
       }

         digitalWrite(ROW[w],LOW);
         __delay_cycles(150000);
      	  }
		}
     }

}


