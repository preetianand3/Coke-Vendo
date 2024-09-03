# Coke-Vendo
The project implements a coke vending machine using an ARM7-LPC2148 development board.

### Description
This project implements a coke vending machine using an ARM7TDMI-LPC2148-T10 development board. The system is designed to provide customers with multiple options for selecting a drink using a keypad, LCD screen and perform the dispensing activity using seven segment display, buzzer. 

### Problem Statement
Dhriti wants to have a coke during the interval of a movie. The task is to implement a coke vending machine that provides different options for the customer using a keypad and a display, allowing them to make their choice quickly and conveniently also dispense the beverage as convinient.

### Features
- **Keypad Interface:** Enables user input to navigate and select from available drink options.
- **Display Screen:** Shows available drinks.
- **User Feedback:** Provides visual feedback for successful selections or errors.
- **Dispensing Status** Shows the dispensing status with countdown upto and beep.

### Hardware Requirements
- ARM7TDMI (LPC2148) Development Board
- Matrix Keypad
- LCD Display
- Buzzer
- Seven Segment Display
- Power Supply
- 
### Software Requirements
- Keil uVision 5 
- Flash Magic tool for uploading firmware

### Setup Used
1. **Hardware Setup:**
   - Ensure the board is properly powered.

2. **Software Setup:**
   - Open the project in Keil uVision 5 IDE.
   - Compile the code to generate the binary/hex file.

3. **Upload Firmware:**
   - Use Flash Magic tool to flash the compiled firmware onto the LPC2148 development board.

### How to Use
- Power up the vending machine system.
- Use the keypad to select different options displayed on the screen.
- Follow the display and know the status of the drink being dispensed.

### Future Enhancements
- Add support for multiple languages on the display.
- Introduce payment integration for a more realistic vending machine experience.
