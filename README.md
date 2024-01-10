# casa0016-smart-windows-system

Welcome to the Smart Window Control System GitHub repository. This documentation provides insights into the project's code and components, enabling easy reproduction for future use.

## Project Overview

In the rapidly evolving landscape of technology, the Smart Window Control System introduces an innovative approach to window management. By integrating advanced sensing technologies, the system aims to intelligently control window states, enhancing user comfort while reducing reliance on artificial air conditioning.

## Composition and Dependencies

### Project Composition

- Arduino Uno
- Sound Sensor V1.6
- DFRobot mmwave Radar
- Servo
- LCD Screen
- Buttons

### Dependencies

you need to install the dependencies below:

- SoftwareSerial.h
- Servo.h
- LiquidCrystal.h
- DFRobot_mmWave_Radar.h

### Component assembly

1. mmwave radar:

   | mmwave Radar | Ardunio Uno |
   | ------------ | ----------- |
   | VCC          | 5v          |
   | GND          | GND         |
   | RX           | D2          |
   | TX           | D3          |

2. Sound Sensor V1.6:

   | Sound Sensor V1.6 | Arduino Uno |
   | ----------------- | ----------- |
   | Red               | 5V          |
   | Black             | GND         |
   | White             | A1          |
   | Yellow            | A0          |

3. MG90S Servo

   | MG90S Servo | Arduino Uno |
   | ----------- | ----------- |
   | Red         | 5V          |
   | Brown       | GND         |
   | Orange      | D9          |

4. Button

   | Button | Arduino Uno |
   | ------ | ----------- |
   | button | D8          |



## Flow Chart

This is the basic logic of the system working (auto mode):

<img src="figures\17047691691052.png" style="zoom: 67%;" />

If in manual mode, the system will only controlled by the button.



## Future Works

The user interface can be developed further for better user experience.

Remote control can be added in the future.

More sensors can be added to monitor more environment data.



## Troubleshooter

If you find any problems or bugs, feel free to ask me. 