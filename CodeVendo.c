#include <lpc213x.h>
#include <string.h>

////////////////////////
#define SLAVE_ADDR 78
#define MAX        12
#define AA         2
#define SI         3
#define STO        4
#define STA        5
#define I2EN       6

////////////////////////////
//         Delay Function
//
void wait(int count)
{
    while (count--);
}

//////////////////////////
//        Initialize I2C
//
void I2C_Init(void)
{
    VPBDIV    =   0x02;        // sets FOSC = 60MHz
    PINSEL0   =   0x00000050;  // set p0.2, p0.3 to SDA, SCL

    I2C0SCLH  =   150;        // 50% duty, I2CFreq->100KHz, PCLK=30MHz
    I2C0SCLL  =   150;

    I2C0CONSET =  (1 << I2EN);  // Enable I2C module

    PINSEL1 = 0x00000000;     // Configure P0.16 to P0.31 as GPIO
    IO0DIR  = 0x000F0000;
    IO0CLR = 0x000F0000;
}

//////////////////////////
//     Enter Master
//     Transmitter Mode
//
int I2C_Start(void)
{
    I2C0CONCLR = 1 << STO;
    I2C0CONCLR = 1 << SI;
    I2C0CONSET = 1 << STA;
    return 0;
}

//////////////////////////////////////
//      Delay Function
//
void delay_ms(int count)
{
    int j = 0, i = 0;

    for (j = 0; j < count; j++)
    {
        /* At 60MHz, the below loop introduces
        delay of 10 us */
        for (i = 0; i < 35; i++);
    }
}

///////////////////////////////////////////////////////
//      Function to send data from Master to slave I2C
//      device
//
void senddata(char data)
{
    while (!(I2C0CONSET & 0x08));
    I2C0DAT = data;
    I2C0CONCLR = 1 << SI;
    delay_ms(200);
}

void LCD_Command(char cmnd)  /* LCD16x2 command function */
{
    char data;
    data = (cmnd & 0xF0) | 0x04 | 0x08; /* Send upper nibble */
    // rs = 0; rw = 0; en = 1; 0100 = 0x04 LSB
    senddata(data);
    delay_ms(100);
    // en = 0;
    data = (cmnd & 0xF0) | 0x08;
    senddata(data);
    delay_ms(100);

    data = (cmnd << 4) | 0x04 | 0x08; /* Send lower nibble */
    senddata(data);
    delay_ms(100);
    // en = 0;
    data = (cmnd << 4) | 0x08;
    senddata(data);
    delay_ms(100);
}

void LCD_Char(char char_data)  /* LCD data write function */
{
    char data;
    // rs = 1; rw = 0; en = 1;
    data = (char_data & 0xF0) | 0x08 | 0x05; /* Send upper nibble */
    senddata(data);
    delay_ms(1);
    // rs = 1; rw = 0; en = 0;
    data = (char_data & 0xF0) | 0x08 | 0x01;
    senddata(data);
    delay_ms(2);

    // rs = 1; rw = 0; en = 1;
    data = (char_data << 4) | 0x08 | 0x05; /* Send lower nibble */
    senddata(data);
    delay_ms(1);
    // rs = 1; rw = 0; en = 0;
    data = (char_data << 4) | 0x08 | 0x01;
    senddata(data);
    delay_ms(5);
    senddata(0x08);
}

void LCD_String(char *str)  /* Send string to LCD function */
{
    int i;
    for (i = 0; str[i] != 0; i++)  /* Send each char of string till the NULL */
    {
        LCD_Char(str[i]);  /* Call LCD data write */
    }
}

void LCD_String_xy(char row, char pos, char *str)  /* Send string to LCD function */
{
    if (row == 0)
        LCD_Command((pos & 0x0F) | 0x80);
    else if (row == 1)
        LCD_Command((pos & 0x0F) | 0xC0);
    LCD_String(str);  /* Call LCD string function */
}

///////////////////////////////////////////////////////
//      Delay Function
//
void delay(unsigned int del)
{
    unsigned int k;
    for (k = 0; k < del; k++);
}

///////////////////////////////////////////////////////
//      Display Function
//
void disp(unsigned int temp)
{
    unsigned int i;
    LCD_Command(0x01);  /* Clear display */
    i = temp;
    if (i == 0)
    {
        delay(65000);
        LCD_String_xy(0, 0, "Coke Dispensed");
        delay(6500000);
    }
    else if (i == 1)
    {
        delay(65000);
        LCD_String_xy(0, 0, "Fanta Dispensed");
        delay(6500000);
    }
    else if (i == 2)
    {
        delay(65000);
        LCD_String_xy(0, 0, "7Up Dispensed");
        delay(6500000);
    }
    else if (i == 3)
    {
        delay(65000);
        LCD_String_xy(0, 0, "M'Dew Dispensed");
        delay(6500000);
    }
    else
    {
        delay(65000);
        LCD_String_xy(0, 0, "Not available");
        delay(6500000);
    }
    delay(20000000);
    // delay(65000);
    // delay(65000);
    // delay(65000);
    // delay(65000);

    LCD_Command(0x01);  /* Clear display */
    LCD_String_xy(0, 0, "Thank You");
    LCD_String_xy(1, 0, "Visit Again!");
    delay(15000000);
    LCD_Command(0x01);  /* Clear display */
}

int main() {
    char code = SLAVE_ADDR; // 0x6e;
    unsigned long int value, j;
    int i = 0;
    char str[] = "**<COKE VENDO>**";
    char str1[] = "                        Enter choice!";

    unsigned int row0[4] = { 0x00ee0000, 0x00ed0000, 0x00eb0000, 0x00e70000 };
    unsigned int row1[4] = { 0x00de0000, 0x00dd0000, 0x00db0000, 0x00d70000 };
    unsigned int row2[4] = { 0x00be0000, 0x00bd0000, 0x00bb0000, 0x00b70000 };
    unsigned int row3[4] = { 0x007e0000, 0x007d0000, 0x007b0000, 0x00770000 };

    IODIR1 = 0XFFF0FFFF; // Set rows as output and columns as input
    PINSEL1 = 0x00000000;
    I2C_Init();          // Initialize I2C module
    I2C_Start();         // Start I2C module
    wait(4000);

    while (!(I2C0CONSET & 0x08)); // Wait till SI bit is set
    IO0SET = (1 << 21);
    I2C0CONCLR = 1 << STO;
    I2C0CONCLR = 1 << STA;
    I2C0CONSET = 1 << AA;
    I2C0DAT = code;

    I2C0CONCLR = 1 << SI;
    // wait(4000);
    while (!(I2C0CONSET & 0x08));
    IO0SET = 0x00010000;

    if (I2C0STAT == 0x18) {
        IO0SET = (1 << 23);
        I2C0CONSET = 1 << AA;
        I2C0DAT = 0x00; // x00; Buff[index]
        I2C0CONCLR = 1 << SI;
        IO0SET = 0x00020000;
        while (!(I2C0CONSET & 0x08));
        for (i = 0; i < 2000; i++) wait(800);

        if (I2C0STAT == 0x28) {
            IO0SET = 0x00030000;
            LCD_Command(0x02);
            LCD_Command(0x28);  // Initialization of 16X2 LCD in 4-bit mode
            LCD_Command(0x0C);  // Display ON Cursor OFF
            LCD_Command(0x06);  // Auto Increment cursor
            LCD_Command(0x01);  // Clear display
            LCD_Command(0x80);  // Cursor at home position

            LCD_String(str);
            LCD_String(str1);

            for (i = 0; i < 2000; i++) wait(8000);
            LCD_Command(0x01);  // Clear display
            LCD_Command(0x80);  // Cursor at home position

            while (1) {
                LCD_String_xy(0, 0, "1.Coke   2.Fanta");
                LCD_String_xy(1, 0, "3.7UP    4.M'Dew");
                delay(650000);
                IOPIN1 = 0x00ff0000; // Initialize rows and columns with one
                IOCLR1 = 0x00100000; // Enable row0
                value = IOPIN1;
                delay(50000);
                value = value & 0x00ff0000;

                for (j = 0; j < 4; j++) {
                    if (value == row0[j]) {
                        disp(j);
                        delay(65000); delay(65000);
                        delay(65000); delay(65000);
                        delay(65000);
                    }
                }

                IOPIN1 = 0x00ff0000; // Initialize rows and columns with one
                IOCLR1 = 0x00200000; // Enable row1
                value = IOPIN1;
                delay(50000); delay(50000);
                value = value & 0x00ff0000;
                for (i = 0; i < 4; i++) {
                    if (value == row1[i]) {
                        disp(i + 4);
                        delay(65000); delay(65000);
                        delay(65000); delay(65000);
                        delay(65000);
                    }
                }

                IOPIN1 = 0x00ff0000; // Initialize rows and columns with one
                IOCLR1 = 0x00400000; // Enable row2
                value = IOPIN1;
                delay(65000); delay(65000); delay(65000);
                value = value & 0x00ff0000;
                for (i = 0; i < 4; i++) {
                    if (value == row2[i]) {
                        disp(i + 8);
                        delay(50000);
                    }
                }

                IOPIN1 = 0x00ff0000; // Initialize rows and columns with one
                IOCLR1 = 0x00800000; // Enable row3
                value = IOPIN1;
                delay(65000); delay(65000); delay(65000);
                value = value & 0x00ff0000;
                for (i = 0; i < 4; i++) {
                    if (value == row3[i]) {
                        disp(i + 12);
                        delay(65000); delay(65000);
                        delay(65000); delay(65000);
                        delay(65000);
                    }
                }
                delay(650000);
            }
        }
    }
}

