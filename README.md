# Automatic Door Locking System

**Microcontroller-based access control using DC motor and RFID sensors**

**Author:** Alexandru-Florin Ionescu
**Date:** Sep 2019 – Feb 2020
**Affiliation:** University POLITEHNICA of Bucharest

---

## 🚀 Project Overview

Developed a microcontroller-driven automatic door locking system that uses RFID card authentication to grant secure access. When a valid card is presented, the system activates a DC motor to unlock and relock the door automatically.

---

## 🔧 Hardware Components

| Component                 | Purpose                                      |
| ------------------------- | -------------------------------------------- |
| ATMega164 Microcontroller | Core control unit                            |
| 12 V DC Motor             | Drives the door mechanism                    |
| RFID Sensor Module        | Reads RFID tags for authentication           |
| Proteus Design Suite      | Electronic circuit schematic and simulations |
| Power Supply (12 V)       | Powers microcontroller and motor             |

---

## 🖥️ Software & Tools

* **IDE:** AVR-GCC and WinAVR
* **Language:** C
* **Libraries:** `<avr/io.h>`, `<util/delay.h>`, `<string.h>`

---

## ⚙️ Features

* **RFID Authentication**: Reads a 4-byte tag and validates against a hard-coded key.
* **Motor Control**: Spins motor to unlock, waits, then reverses to lock.
* **UART Telemetry**: Uses serial commands (`state?`, `data?`) to interrogate RFID module and debug.
* **Robust Operation**: Includes state checks and resets for continuous operation.

---

## 📋 Usage & Operation

1. **Power On**: System initializes UART at 9600 baud and configures motor pins.
2. **Idle State**: Sends `state?` via UART to detect card presence.
3. **Card Detected**: If response is `1`, sends `data?` to read tag ID.
4. **Validation**: Compares received 4-byte ID to stored key (`"1234"`).
5. **Unlock Sequence**: On match, spins motor left (open) for 1 s, stops for 2 s, then spins right (close) for 1 s.
6. **Loop**: Resets state and repeats every 100 ms.

---

## 🗂️ File Structure

```
AutomaticDoorProject/
├─ LICENSE                  # MIT license
├─ README.md                # Project overview and instructions
├─ src/
│  ├─ main.c                # Main application code
```

---

## 📜 License

This project is released under the **MIT License**. See [LICENSE](LICENSE) for details.

---

## 🎓 Acknowledgments

Built as part of the **Embedded Systems** coursework at University POLITEHNICA of Bucharest.
