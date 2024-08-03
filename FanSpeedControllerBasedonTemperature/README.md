
# Fan Controller System

## Overview

This project aims to design a temperature-controlled fan using the ATmega32 microcontroller. The fan is automatically turned ON or OFF based on the temperature readings from the LM35 temperature sensor. The system includes ADC conversion, LCD display, and DC motor control using PWM.

## System Requirements

1. **Microcontroller**: ATmega32 with a frequency of 1 MHz.
2. **Temperature Sensor**: LM35 providing continuous analog output, connected to ADC channel 2.
3. **LCD Display**: To display temperature readings and fan status.
4. **DC Motor**: Controlled via PWM for speed regulation based on temperature.
5. **Fan Control Logic**:
   - **< 30°C**: Turn off the fan.
   - **≥ 30°C**: Turn on the fan at 25% speed.
   - **≥ 60°C**: Turn on the fan at 50% speed.
   - **≥ 90°C**: Turn on the fan at 75% speed.
   - **≥ 120°C**: Turn on the fan at 100% speed.
6. **PWM Signal**: Generated from Timer0 to control the DC motor speed.

## Project Structure

The project is designed based on a layered architecture model with the following components:

- **ADC Driver**: Configured with internal reference voltage (2.56V) and prescaler (F_CPU/8).
  - `void ADC_init(const ADC_ConfigType * Config_Ptr)`
  - `typedef struct { ADC_ReferenceVoltage ref_volt; ADC_Prescaler prescaler; } ADC_ConfigType;`

- **GPIO Driver**: Use the GPIO driver implemented in the course.

- **LCD Driver**: Uses 8-bit data mode with the following connections:
  - RS → PD0
  - RW → GND
  - E → PD2
  - Data Bus → PORTC

- **Temperature Sensor Driver**: Use the temperature sensor driver from the course.

- **DC Motor Driver**:
  - `void DcMotor_Init(void)`
    - Sets up motor pins and stops the motor.
  - `void DcMotor_Rotate(DcMotor_State state, uint8 speed)`
    - Controls motor rotation direction and speed.
    - `DcMotor_State` is defined as an enum or uint8.

- **PWM Driver**: Utilize the Timer0 PWM function from the course.
  - `void PWM_Timer0_Start(uint8 duty_cycle)`
    - Sets up PWM mode with a 500Hz frequency and non-inverting output.

## Getting Started

1. **Setup Environment**: Ensure you have the necessary tools and libraries for ATmega32 development.
2. **Hardware Connections**:
   - Connect LM35 to ADC channel 2.
   - Connect the LCD as specified.
   - Connect the DC motor to appropriate GPIO pins.
3. **Configuration**:
   - Initialize ADC, GPIO, LCD, and DC motor drivers.
   - Configure PWM settings for Timer0.

## References

- **Video Tutorial**: [Fan Controller System Overview](https://youtu.be/RFQGjcikfK4)
- **Datasheets**: Refer to the ATmega32 and LM35 datasheets for detailed specifications and configuration options.

## Acknowledgements

Special thanks to the course materials and resources that provided guidance and code snippets used in this project.
