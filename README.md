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

<img src="https://github.com/user-attachments/assets/be6ee8fd-acbf-469c-b1dd-3975c0d50ffb" width=500px height=350px><img src="https://github.com/user-attachments/assets/26e24e5b-4a28-47c5-84a7-e5e80e5646df" width=500px height=350px><br>

<img src="https://github.com/user-attachments/assets/c1df0c5c-c043-4371-9763-1fb5f29fb2a9" width=500px height=350px><img src="https://github.com/user-attachments/assets/1b4169cf-b9b1-4052-bda5-3f129494afd8" width=500px height=350px><br>

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
