# data_struct_final_project
# data_struct_final_project
# Conveyor Control System Simulation (Finite State Machine)

## 📦 Project Data Structure Implemented

This project implements a **Finite State Machine (FSM)** using a **control table data structure**. The FSM simulates a basic control system for a conveyor with states like `IDLE`, `RUNNING`, and `ERROR`, controlled by button and sensor inputs.

### Key Components:
- `ControlEntry` struct – Defines a transition rule with `fromState`, `input`, `toState`, and a `message`.
- `controlTable[]` – An array of `ControlEntry` items that defines all valid transitions.
- `updateState()` – Simulates a scan cycle, checking for valid transitions based on inputs and updating the system state.
- `printState()` – Displays the current system state.

---

## Short Explanation of the Data Structure

This C++ program simulates how a **Programmable Logic Controller (PLC)** might handle conveyor logic using a **finite state machine**:

- **States** represent machine modes (`IDLE`, `RUNNING`, `ERROR`).
- **Inputs** (e.g., `startButton`, `jamSensor`) represent user actions or sensor events.
- A **control table** holds all the valid state transitions.
- When `updateState()` is called, it loops through the table and applies the first matching transition, printing a message and changing the state.

This design makes the logic easy to extend and mirrors real-world industrial control patterns.
