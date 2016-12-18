# Digital-Lock-System
Project of Carl and Alex

Topic 14.4 from "Programmable Microcontrollers With Applications" by Unsalan and Gurhan
<p>The following Link showcases our project in a video: https://youtu.be/zNbsNregsBI
<p>In this application, we will design a digital lock system with a keypad, an LCD, and a
solenoid. Initially, Enter Your Password is written on the first line of the LCD, and the
system must wait in a suitable low-power mode. When there is an entry from the keypad,
the system exits from the low-power mode and writes * on the second line of the LCD.
Each * sign represents an entered number. If the * button on the keypad is pressed, the
system erases the last entry. If the entered password is wrong, an Access Denied string is
written to the second line of the LCD and the red LED is turned on. Also, the buzzer
connected to the same pin with the red LED starts to beep. After 2 s, the system returns to
the initial condition by turning off the red LED and stopping the buzzer. If the entered
password is correct, an Access Granted string is written to the second line of the LCD.
The solenoid is opened, and the green LED is turned on to indicate that the door is opened.
Also, the second buzzer beeps for 2 s. After the door is opened, the user has two choices.
First, the door can be closed by using the push button. Then the system returns to the
initial condition by turning off the green LED and closing the solenoid again. Second, the
password can be changed after pressing the # button on the keypad. Then a Change
Password string is written to the first line of the LCD and after this process is completed.
Meanwhile, the Change Password string will be changed to a Password Changed string.
After this step, the system can return to the initial condition by pressing the push button.
