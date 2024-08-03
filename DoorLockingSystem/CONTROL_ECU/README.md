
# Door Locker Security System - Control_ECU

## Overview
The Control_ECU is a critical component in the Door Locker Security System, responsible for processing user inputs, managing door locking mechanisms, and handling password-related functions. It communicates with the HMI_ECU via UART to receive commands and send responses. The Control_ECU includes an EEPROM for secure password storage, a buzzer for alerts, and a DC motor for door operation.

## Responsibilities
- **Password Management:**
  - Compare entered passwords with the stored password in EEPROM.
  - Handle password changes upon user request.
- **Door Control:**
  - Unlock the door by rotating the DC motor in a clockwise direction.
  - Lock the door by rotating the DC motor in an anti-clockwise direction.
- **Error Handling:**
  - Activate the buzzer for 1 minute if the incorrect password is entered three times consecutively.
  - Ensure proper communication and status reporting to the HMI_ECU.

## Components
- **EEPROM:** Stores the system password securely.
- **Buzzer:** Provides an audible alert for incorrect password attempts.
- **DC Motor:** Controls the locking and unlocking of the door.

## Communication
- **UART:** Used for communication between the Control_ECU and HMI_ECU. The Control_ECU listens for commands from the HMI_ECU and sends responses based on the processed data.

## Functions

### 1. Password Creation and Verification
- **Function:** Compare entered password with the stored password.
- **Process:**
  - Receive password from HMI_ECU.
  - Check against the stored password in EEPROM.
  - Send verification result back to HMI_ECU.

### 2. Door Operation
- **Function:** Control the door's locking and unlocking mechanism.
- **Process:**
  - Rotate the DC motor clockwise for 15 seconds to unlock the door.
  - Hold the motor for 3 seconds to ensure the door is fully unlocked.
  - Rotate the DC motor anti-clockwise for 15 seconds to lock the door.

### 3. Password Change
- **Function:** Update the stored password in EEPROM.
- **Process:**
  - Receive new password from HMI_ECU.
  - Verify the current password before updating.
  - Save the new password in EEPROM if verification is successful.

### 4. Incorrect Password Handling
- **Function:** Handle scenarios where the password is entered incorrectly.
- **Process:**
  - After three consecutive incorrect attempts:
    - Activate the buzzer for 1 minute.
    - Display an error message on the LCD.
    - Lock the system temporarily to prevent further inputs.
    - Reset to the main options.

## Implementation Notes
- **UART Communication:** Ensure proper UART setup and handling to communicate effectively with the HMI_ECU.
- **Motor Control:** Implement precise timing for motor operations to ensure proper door movement.
- **EEPROM Handling:** Manage EEPROM read/write operations carefully to maintain password security.

## Code Structure
- **control_ecu.c:** Contains the main control loop and function calls for handling UART communication and controlling the door.
- **dc_motor.c:** Manages motor operations for door locking and unlocking.
- **external_eeprom.c:** Manages storage of password.
- **pwm_timer0.c:** Manages time rotation of dc motor using pwm.
- **uart.c:** Manages communication protocol with the other ecu.

## Future Enhancements
- Voice Commands
- Integration with Smart Home Systems
- Biometric Authentication

