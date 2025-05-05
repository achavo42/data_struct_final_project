# data_struct_final_project
# Modular Finite State Machine System for Equipment Control
# Project Overview
This project simulates a basic control system using Finite State Machines (FSMs). It models the behavior of industrial devices such as conveyors, pumps, or other equipment using simple state transitions triggered by boolean input conditions. Each device has its own state machine that can be extended or customized.

This approach mirrors how Programmable Logic Controllers (PLCs) manage state transitions in automation systems—making this a great educational tool or the foundation for a more robust control system.

##  Project Data Structure Implemented

This project implements a **Finite State Machine (FSM)** using a **control table data structure**. The FSM simulates a basic control system for process equipment with states like `IDLE`, `RUNNING`, and `ERROR`, controlled by button and sensor inputs.

### Key Components:
- At the heart of this system is the ControlEntry struct, which models a single transition:
fromState: The state the machine must currently be in.

input: A pointer to a boolean condition (e.g., a button press).

toState: The state to move to if the condition is true.

message: A message printed during the transition.

- The StateMachine class encapsulates:

A name (e.g., "Conveyor")

A current state

A vector of transitions

An update() method that processes valid transitions

A printState() method for status output


## Short Explanation of the Data Structure

This C++ program simulates how a **Programmable Logic Controller (PLC)** might handle equipment logic using a **finite state machine**:

- **States** represent machine modes (`IDLE`, `RUNNING`, `ERROR`).
- **Inputs** (e.g., `startButton`, `jamSensor`) represent user actions or sensor events.
- A **control table** holds all the valid state transitions.
- When `updateState()` is called, it loops through the table and applies the first matching transition, printing a message and changing the state.

This design makes the logic easy to extend and mirrors real-world industrial control patterns.
The code includes adding and simulating equipment. The user just needs to run the code normally.
