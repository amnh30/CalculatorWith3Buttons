# 🎉 Calculator Project

Welcome to the Calculator Project! This project implements a simple calculator using an LCD display and a keypad for user interaction.

## 📜 Overview

This project enables users to perform basic arithmetic operations: addition, subtraction, multiplication, and division. The user can select numbers and operations using a keypad, and the results are displayed on an LCD.

## 🛠️ Features

- Simple user interface with LCD display
- Supports four basic operations:
  - Addition ( + )
  - Subtraction ( - )
  - Multiplication ( * )
  - Division ( / )
- User-friendly keypad input
- Handles division by zero

## 📦 Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [Function Descriptions](#function-descriptions)
- [License](#license)

## 📥 Installation

1. **Clone the repository**:

   ```bash
   git clone <repository-url>
   ```

2. **Open the project** in your preferred IDE (e.g., Atmel Studio, Eclipse).
3. **Compile and upload** the code to your microcontroller.

## 📊 Usage

1. **Power on the device.** The display will show `0+0=`.
2. **Use the keypad** to select the first number (0-9).
3. **Choose an operation** (+, -, *, /).
4. **Select the second number** (0-9).
5. The result will be displayed on the LCD. 

## 🖥️ Code Structure

| File Name                | Description                                   |
|--------------------------|-----------------------------------------------|
| `main.c`                 | Contains the main function and logic          |
| `MDIO_Interface.h`       | Header file for MDIO interface                |
| `HLCD_interface.h`       | Header file for LCD interface                 |
| `HKPD_interface.h`       | Header file for keypad interface              |

## 📚 Function Descriptions

### `void NumberCounter(u8 Copy_u8Num)`

- **Description**: Increments or decrements the selected number based on keypad input.
- **Parameters**: 
  - `Copy_u8Num`: Indicates which number to modify (first or second).

### `void SignSelector()`

- **Description**: Allows the user to select an arithmetic operation using the keypad.
- **Parameters**: None.

### `void Sum()`

- **Description**: Performs the arithmetic operation selected by the user and displays the result.
- **Parameters**: None.

### `void clear()`

- **Description**: Clears the display and resets the calculator.
- **Parameters**: None.

## 🚀 Example Code

Here’s a snippet of the main function:

```c
int main(void)
{
    u8 Local_u8Mode = 0;

    // Initialize the MDIO and LCD
    MDIO_IntialPins();  // Initialize all necessary pins
    HLCD_VoidLcdIint(); // Initialize the LCD
    HLCD_u8WriteStr("0+0=");
    
    while (1)
    {
        NumberCounter(0);
        SignSlector();
        NumberCounter(2);
        Sum();
        clear();
    }
}
```

## 📝 Notes

- Ensure you have the necessary hardware components:
  - **Microcontroller**
  - **LCD Display**
  - **Keypad**
  - **Wires and breadboard** for connections

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
