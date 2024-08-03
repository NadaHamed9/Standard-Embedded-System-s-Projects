# Door Locker Security System

## Project Overview
This project implements a Door Locker Security System to unlock a door using a password. The system uses two ATmega32 Microcontrollers with a frequency of 8MHz. It is designed and implemented based on a layered architecture model.

## Specifications
1. **Microcontrollers:** 
   - 2 x ATmega32 Microcontrollers (8MHz)

2. **Layered Architecture Model:**
   - **MC1:** HMI_ECU (Human Machine Interface)
     - Components: 2x16 LCD and 4x4 keypad
   - **MC2:** Control_ECU
     - Components: EEPROM, Buzzer, and DC-Motor

3. **Responsibilities:**
   - **HMI_ECU:** Interaction with the user through the keypad and LCD.
   - **Control_ECU:** Processing and decisions such as password checking, door control, and alarm activation.

## System Sequence
### Step 1: Create a System Password
- Press the enter button (choose any button on the keypad as the enter button).
- Ask the user to re-enter the same password for confirmation by displaying the message: “Please re-enter the same Pass”.
- Enter a password consisting of 5 numbers. Display `*` on the screen for each number.
- Press the enter button.
- HMI_ECU sends the two passwords to the Control_ECU through UART.
  - If the passwords match, save the password in the EEPROM and proceed to Step 2.
  - If the passwords do not match, repeat Step 1.

### Step 2: Main Options
- The LCD displays the main system options.
  
### Step 3: Open Door
- The LCD displays “Please Enter Password”.
- Enter the password and press the enter button.
- HMI_ECU sends the password to the Control_ECU for comparison with the one saved in the EEPROM.
  - If the passwords match:
    - Rotate the motor for 15 seconds CW and display “Door is Unlocking”.
    - Hold the motor for 3 seconds.
    - Rotate the motor for 15 seconds A-CW and display “Door is Locking”.
  
### Step 4: Change Password
- HMI_ECU sends the password to the Control_ECU for comparison with the one saved in the EEPROM.
  - If the passwords match, repeat Step 1.

### Step 5: Incorrect Password Handling
- If the passwords do not match in Step 3 or Step 4:
  - Ask the user to re-enter the password and press the enter button.
  - HMI_ECU sends the password to the Control_ECU for comparison with the one saved in the EEPROM.
    - If the passwords match, proceed with the respective actions in Steps 3 and 4.
    - If the passwords do not match again, ask the user one last time for the password.
      - If the passwords match, proceed with the respective actions in Steps 3 and 4.
      - If the passwords do not match for the third consecutive time:
        - Activate the buzzer for 1 minute.
        - Display an error message on the LCD for 1 minute.
        - Lock the system (no inputs from the keypad will be accepted during this period).
        - Return to Step 2 (main options).
        
## Components
- **MC1 (HMI_ECU):**
  - 2x16 LCD
  - 4x4 Keypad
- **MC2 (Control_ECU):**
  - EEPROM
  - Buzzer
  - DC-Motor

## Communication
- **UART:** Used for communication between HMI_ECU and Control_ECU.

## Notes
- The enter button can be any button on the keypad chosen by the user.
- Password consists of 5 numbers and is masked with `*` on the LCD.
- The motor rotation times are 15 seconds for both CW and A-CW directions.
- The buzzer activation and error message display time is 1 minute if the password is entered incorrectly three consecutive times.

