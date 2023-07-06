# MilkyWay Maker

🌌 MilkyWay Maker 🌌 is an Arduino-based system that allows you to make delicious cocoa milk drinks conveniently at home. This project includes a smart liquid dispenser with a keyboard for inputting the desired quantity of milk and a distance sensor that activates the powder dispensing mechanism when a cup is detected. The goal of this project is to simplify and automate the process of making cocoa milk drinks, ensuring consistent quality every time. 🍫🥛☕️

## General Description

MilkyWay Maker combines the functionality of Arduino, the convenience of automation, and the enjoyment of delicious milk-coffee beverages. With this system, users can input the desired quantity of milk using the keyboard, and the system will dispense the milk accordingly. The presence of a cup is detected by the distance sensor, which activates the powder dispensing mechanism to add cocoa powder. This ensures accurate and consistent drink preparation. 🖥️🤖🍶

![Block Diagram](https://github.com/maruwu8/MilkyWay-Maker/blob/main/assets/block%20schema.png)


The project not only caters to coffee lovers but also provides an opportunity for learning about electronics and programming. The code includes functionalities such as reading keypad inputs, controlling a servo motor, calculating milk flow rate, displaying information on an LCD screen, and playing beep sequences for notifications. ☕️💡📝

## Hardware Design

### Components
- Water Diaphragm Pump, 6-12V, R385
- 400-Point Breadboard
- 3x4 Membrane Keypad
- LCD 1602 + I2C LCD Interface Module 1602
- HC SR-04P Ultrasonic Sensor, 3-5.5V
- SG90 Servo Motor, 180 degrees
- Flow Sensor 0.3-6l/min, YF-S401, 120 degrees
- 5V Relay Module, High-Level Trigger
- 9V Battery
- UNO R3 Arduino Compatible Development Board
- Passive Buzzer 5V
- Water Pump Hose 6x8mm
- Dupont Wires

![Fritzing Diagram](https://github.com/maruwu8/MilkyWay-Maker/blob/main/assets/Fritzing.png)

## Software Design

The software design of MilkyWay Maker includes the following features:

- **User Input**: The keypad allows users to input the desired volume of liquid. The code reads the input and stores it as the target volume for dispensing.
- **Liquid Dispensing**: The flow sensor measures the flow rate of the liquid. The code calculates the amount of liquid dispensed based on the flow rate and time. It keeps track of the total amount of liquid dispensed until it reaches the target volume.
- **Powder Dispensing**: The ultrasonic sensor detects the presence of a glass near the machine. When the glass is detected, a servo motor is activated to dispense the cocoa powder.
- **Display and Feedback**: The LCD display shows various information such as the input volume, flow rate, and total dispensed volume. It provides feedback messages like "Insert volume," "Volume reached," and "Remove cup" to guide the user through the process.
- **Buzzer**: The buzzer generates beep sounds during certain events, such as when the volume is entered correctly or when the target volume is reached.

The code utilizes libraries for the keypad, LCD display, and servo motor. Pin connections for various components are defined within the code. The code also includes functions for pulse counting, distance measurement using the ultrasonic sensor, and generating beep sequences with the buzzer. 🖥️🧪🎶

## Results

I am thrilled and proud of the successful incorporation of my everyday favorite beverage into an Arduino project. By creating the Milky Way Maker coffee maker machine, I have not only combined my passion for coffee with my interest in electronics

and programming but also brought a new level of convenience and automation to my daily coffee routine. ☕️💻🤩

Looking forward, the project holds immense potential for customization and expansion. The Arduino platform allows for further enhancements and the addition of new features. For instance, temperature control could be incorporated to ensure the perfect brewing temperature, or programmable recipes could be created to cater to different coffee preferences. The adaptability and room for growth make Milky Way Maker a versatile and dynamic coffee maker machine. 🌟🔧🌱

## Conclusions

In conclusion, the development of Milky Way Maker, a coffee maker machine using Arduino, has been a successful project. It demonstrates the potential of integrating electronics and programming into everyday appliances to automate processes and enhance functionality. The user-friendly interface, sensor integration, and customization options make it a versatile and enjoyable coffee-making experience. The project provides valuable learning opportunities and highlights the possibilities for future innovation in home automation. 🏠🚀😃


## Journal Log

- **15.05**: Researched for a project theme 📚🔍
- **17.05**: Decided on Milky Way Maker as the project 🌌✨
- **18.05**: Ordered the required components 📦📦
- **21.05**: Components arrived, started brainstorming the project 💡💭

![Demo Video](https://example.com/milkywaymaker-demovideo.zip) 🎥🎬
