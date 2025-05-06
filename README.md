# data_struct_final_project
# Modular Finite State Machine System for Equipment Control
# Project Overview
This project simulates a modular control system for industrial equipment using Finite State Machines (FSMs). Each piece of equipment (e.g., conveyor, pump) is modeled with its own customizable state machine using a control table approach — a common structure in automation and embedded systems.

It reflects how Programmable Logic Controllers (PLCs) handle state transitions triggered by inputs such as buttons or sensors, making it useful for both learning and as a foundation for more advanced control logic.

##  Project Data Structure Implemented

This project implements a **Finite State Machine (FSM)** using a **control table data structure**. The FSM simulates a basic control system for process equipment with states like `IDLE`, `RUNNING`, and `ERROR`, controlled by button and sensor inputs.

### Key Components:
States:

- IDLE, RUNNING, ERROR

- Control Table:
A std::vector of ControlEntry structs, each defining:

 fromState: current state required

input: pointer to a bool condition (e.g., button press or sensor trigger)

toState: target state if the condition is true

message: status output for the transition

- StateMachine Class:

Holds the name of the equipment

Tracks the current state

Stores transitions in a control table

Provides methods to:

  addTransition()

  removeTransition()

  modifyTransition()

  update() (evaluate transitions)

  printState() (display current state)




## Short Explanation of the Data Structure

This C++ program simulates how a **Programmable Logic Controller (PLC)** might handle equipment logic using a **finite state machine** Equipment Management System
to manage multiple machines and ensure modularity:

- EquipmentManager Class:

Tracks all added equipment by name

Prevents adding duplicates

Allows dynamic creation and deletion of equipment

Lists all active machines

- Features:

 Add new equipment

 Prevent duplicate names

 Remove equipment by name

 Modify or delete FSM transitions

 List currently active equipment

This design makes the logic easy to extend and mirrors real-world industrial control patterns.
The code includes adding and simulating equipment. The user just needs to run the code normally.
