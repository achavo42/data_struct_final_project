#include <iostream>

// Define state constants
const int STATE_IDLE    = 0;
const int STATE_RUNNING = 1;
const int STATE_ERROR   = 2;

// Simulated inputs
bool startButton = false;
bool stopButton = false;
bool jamSensor = false;
bool jamCleared = false;

// Current state variable
int currentState = STATE_IDLE;

// Define a control table entry
struct ControlEntry {
    int fromState;
    bool* input;          // Pointer to input condition
    int toState;
    const char* message;  // Message to display during transition
};

// The control table: this is your PLC step chart in C++ form
ControlEntry controlTable[] = {
    {STATE_IDLE,    &startButton, STATE_RUNNING, "Starting conveyor..."},
    {STATE_RUNNING, &stopButton,  STATE_IDLE,    "Stopping conveyor..."},
    {STATE_RUNNING, &jamSensor,   STATE_ERROR,   "Jam detected! Going to ERROR."},
    {STATE_ERROR,   &jamCleared,  STATE_IDLE,    "Jam cleared. Resetting to IDLE."}
};

// Function to simulate the state update (like PLC scan)
void updateState() {
    for (const auto& entry : controlTable) {
        if (entry.fromState == currentState && *(entry.input)) {
            std::cout << entry.message << "\n";
            currentState = entry.toState;
            break; // Apply only the first valid transition
        }
    }
}

// Function to print the current state as text
void printState() {
    std::cout << "Current State: ";
    if (currentState == STATE_IDLE) std::cout << "IDLE\n";
    else if (currentState == STATE_RUNNING) std::cout << "RUNNING\n";
    else if (currentState == STATE_ERROR) std::cout << "ERROR\n";
}

int main() {
    printState();

    // Simulate pressing the start button
    startButton = true;
    updateState();
    printState();
    startButton = false; // Reset button

    // Simulate a jam occurring
    jamSensor = true;
    updateState();
    printState();
    jamSensor = false;

    // Simulate clearing the jam
    jamCleared = true;
    updateState();
    printState();
    jamCleared = false;

    // Simulate pressing stop (but we’re already IDLE, so nothing happens)
    stopButton = true;
    updateState();
    printState();

    return 0;
}
