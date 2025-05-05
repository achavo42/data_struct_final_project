#include <iostream>
#include <vector>
#include <string>

// Define state constants
const int STATE_IDLE    = 0;
const int STATE_RUNNING = 1;
const int STATE_ERROR   = 2;

// Define a control table entry
struct ControlEntry {
    int fromState;
    bool* input;          
    int toState;
    const char* message;  
};

// FSM class for any equipment
class StateMachine {
public:
    std::string name;
    int currentState;
    std::vector<ControlEntry> controlTable;

    StateMachine(const std::string& deviceName, int initialState)
        : name(deviceName), currentState(initialState) {}

    void addTransition(int from, bool* input, int to, const char* message) {
        controlTable.push_back({from, input, to, message});
    }

    void update() {
        for (const auto& entry : controlTable) {
            if (entry.fromState == currentState && *(entry.input)) {
                std::cout << "[" << name << "] " << entry.message << "\n";
                currentState = entry.toState;
                break;
            }
        }
    }

    void printState() const {
        std::cout << "[" << name << "] Current State: ";
        if (currentState == STATE_IDLE) std::cout << "IDLE\n";
        else if (currentState == STATE_RUNNING) std::cout << "RUNNING\n";
        else if (currentState == STATE_ERROR) std::cout << "ERROR\n";
    }
};

// Simulated inputs
bool startConveyor = false;
bool stopConveyor = false;
bool jamSensor = false;
bool jamCleared = false;

bool startPump = false;
bool stopPump = false;

int main() {
    // Create FSM for Conveyor
    StateMachine conveyor("Conveyor", STATE_IDLE);
    conveyor.addTransition(STATE_IDLE,    &startConveyor, STATE_RUNNING, "Starting conveyor...");
    conveyor.addTransition(STATE_RUNNING, &stopConveyor,  STATE_IDLE,    "Stopping conveyor...");
    conveyor.addTransition(STATE_RUNNING, &jamSensor,     STATE_ERROR,   "Jam detected! Moving to ERROR.");
    conveyor.addTransition(STATE_ERROR,   &jamCleared,    STATE_IDLE,    "Jam cleared. Returning to IDLE.");

    // Create FSM for Pump
    StateMachine pump("Pump", STATE_IDLE);
    pump.addTransition(STATE_IDLE,    &startPump, STATE_RUNNING, "Pump starting...");
    pump.addTransition(STATE_RUNNING, &stopPump,  STATE_IDLE,    "Pump stopping...");

    // Simulate interaction
    conveyor.printState();
    pump.printState();

    std::cout << "\n--- Activating Conveyor ---\n";
    startConveyor = true;
    conveyor.update();
    conveyor.printState();
    startConveyor = false;

    std::cout << "\n--- Starting Pump ---\n";
    startPump = true;
    pump.update();
    pump.printState();
    startPump = false;

    std::cout << "\n--- Conveyor Jam Detected ---\n";
    jamSensor = true;
    conveyor.update();
    conveyor.printState();
    jamSensor = false;

    std::cout << "\n--- Jam Cleared ---\n";
    jamCleared = true;
    conveyor.update();
    conveyor.printState();
    jamCleared = false;

    std::cout << "\n--- Stopping Pump ---\n";
    stopPump = true;
    pump.update();
    pump.printState();
    stopPump = false;

    return 0;
}
