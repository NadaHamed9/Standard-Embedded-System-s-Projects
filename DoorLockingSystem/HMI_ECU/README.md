
# Door Locker Security System - HMI_ECU

## Overview
The HMI_ECU (Human Machine Interface Electronic Control Unit) serves as the interface between the user and the Door Locker Security System. It handles user input via the keypad and displays information on the LCD. The HMI_ECU communicates with the Control_ECU via UART to send user commands and receive system responses.

## Responsibilities
- **User Interaction:**
  - Manage user input through the 4x4 keypad.
  - Display prompts and system messages on the 2x16 LCD.
- **Password Management:**
  - Facilitate the creation and verification of passwords.
  - Send password data to the Control_ECU for processing.
- **System Navigation:**
  - Provide options for unlocking the door, changing the password, and handling incorrect password attempts.

## Components
- **2x16 LCD:** Displays user prompts, system messages, and feedback.
- **4x4 Keypad:** Allows user input for password entry and system navigation.

## Communication
- **UART:** Used for communication with the Control_ECU. The HMI_ECU sends commands and passwords and receives responses to update the user interface.

## Functions

### 1. User Interaction
- **Function:** Manage user input and display information.
- **Process:**
  - Display prompts for password entry and system options on the LCD.
  - Capture user input from the 4x4 keypad.
  - Provide visual feedback (e.g., `*` for password characters).

### 2. Password Creation and Verification
- **Function:** Facilitate the creation of a new password and verify it.
- **Process:**
  - Prompt the user to enter and confirm a new password.
  - Send the entered password to the Control_ECU for storage if confirmed.

### 3. Door Operation
- **Function:** Handle door unlocking based on user input.
- **Process:**
  - Prompt the user to enter the password to unlock the door.
  - Send the entered password to the Control_ECU for verification.
  - Display the status of the door (e.g., "Door is Unlocking").

### 4. Password Change
- **Function:** Allow the user to change the existing password.
- **Process:**
  - Prompt the user to enter the current and new password.
  - Send the new password to the Control_ECU if the current password is verified.

### 5. Incorrect Password Handling
- **Function:** Manage cases of incorrect password entry.
- **Process:**
  - Allow the user up to three attempts to enter the correct password.
  - Display error messages and prompt for re-entry if needed.
  - Inform the user if the system is locked after three failed attempts.

## Implementation Notes
- **Keypad Handling:** Ensure reliable detection of key presses and debouncing.
- **LCD Display:** Properly format and update the display to reflect current status and prompts.
- **UART Communication:** Implement robust UART handling to ensure accurate data exchange with the Control_ECU.

## Code Structure
- **hmi_ecu.c:** Manages the main control loop and handles interactions with the keypad and LCD.
- **uart.c:** Handles communication protocol with the other ecu.
- **lcd.c:** Manages LCD display updates and formatting.
- **keypad.c:** Manages keypad input and processing.

## Future Enhancements
- Consider adding support for multiple languages in the user interface.
- Implement additional user feedback mechanisms, such as sound alerts for actions.

