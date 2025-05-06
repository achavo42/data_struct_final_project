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

    bool removeTransition(int from, bool* input) {
        for (auto it = controlTable.begin(); it != controlTable.end(); ++it) {
            if (it->fromState == from && it->input == input) {
                controlTable.erase(it);
                std::cout << "[" << name << "] Transition removed.\n";
                return true;
            }
        }
        std::cout << "[" << name << "] Transition not found.\n";
        return false;
    }

    bool modifyTransition(int from, bool* input, int newTo, const char* newMessage) {
        for (auto& entry : controlTable) {
            if (entry.fromState == from && entry.input == input) {
                entry.toState = newTo;
                entry.message = newMessage;
                std::cout << "[" << name << "] Transition modified.\n";
                return true;
            }
        }
        std::cout << "[" << name << "] Transition not found.\n";
        return false;
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

// Equipment manager to handle StateMachine lifecycle
class EquipmentManager {
private:
    std::vector<std::string> equipmentNames;
    std::vector<StateMachine*> machines;

public:
    ~EquipmentManager() {
        for (auto* machine : machines) {
            delete machine;
        }
    }

    bool equipmentExists(const std::string& name) const {
        for (const auto& existingName : equipmentNames) {
            if (existingName == name) return true;
        }
        return false;
    }

    StateMachine* createEquipment(const std::string& name, int initialState) {
        if (equipmentExists(name)) {
            std::cout << "Equipment '" << name << "' already exists.\n";
            return nullptr;
        }

        equipmentNames.push_back(name);
        StateMachine* machine = new StateMachine(name, initialState);
        machines.push_back(machine);
        return machine;
    }

    bool removeEquipment(const std::string& name) {
        for (size_t i = 0; i < equipmentNames.size(); ++i) {
            if (equipmentNames[i] == name) {
                delete machines[i];
                machines.erase(machines.begin() + i);
                equipmentNames.erase(equipmentNames.begin() + i);
                std::cout << "Equipment '" << name << "' removed.\n";
                return true;
            }
        }
        std::cout << "Equipment '" << name << "' not found.\n";
        return false;
    }

    void listEquipment() const {
        if (equipmentNames.empty()) {
            std::cout << "No equipment currently registered.\n";
            return;
        }

        std::cout << "Registered Equipment:\n";
        for (const auto& name : equipmentNames) {
            std::cout << " - " << name << "\n";
        }
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
    EquipmentManager manager;

    // Create Conveyor
    StateMachine* conveyor = manager.createEquipment("Conveyor", STATE_IDLE);
    if (conveyor) {
        conveyor->addTransition(STATE_IDLE,    &startConveyor, STATE_RUNNING, "Starting conveyor...");
        conveyor->addTransition(STATE_RUNNING, &stopConveyor,  STATE_IDLE,    "Stopping conveyor...");
        conveyor->addTransition(STATE_RUNNING, &jamSensor,     STATE_ERROR,   "Jam detected! Moving to ERROR.");
        conveyor->addTransition(STATE_ERROR,   &jamCleared,    STATE_IDLE,    "Jam cleared. Returning to IDLE.");
    }

    // Create Pump
    StateMachine* pump = manager.createEquipment("Pump", STATE_IDLE);
    if (pump) {
        pump->addTransition(STATE_IDLE,    &startPump, STATE_RUNNING, "Pump starting...");
        pump->addTransition(STATE_RUNNING, &stopPump,  STATE_IDLE,    "Pump stopping...");
    }

    // Try duplicate equipment
    manager.createEquipment("Pump", STATE_IDLE);

    // List current equipment
    std::cout << "\n--- Equipment List ---\n";
    manager.listEquipment();

    // Simulate Conveyor activation
    std::cout << "\n--- Activating Conveyor ---\n";
    startConveyor = true;
    if (conveyor) conveyor->update();
    if (conveyor) conveyor->printState();
    startConveyor = false;

    // Simulate Pump start
    std::cout << "\n--- Starting Pump ---\n";
    startPump = true;
    if (pump) pump->update();
    if (pump) pump->printState();
    startPump = false;

    // Modify Conveyor transition
    std::cout << "\n--- Modifying Conveyor Start Transition ---\n";
    if (conveyor) {
        conveyor->modifyTransition(STATE_IDLE, &startConveyor, STATE_ERROR, "Overridden! Going to ERROR.");
        startConveyor = true;
        conveyor->update();
        conveyor->printState();
        startConveyor = false;
    }

    // Remove transition from Conveyor
    std::cout << "\n--- Removing Conveyor Stop Transition ---\n";
    if (conveyor) {
        conveyor->removeTransition(STATE_RUNNING, &stopConveyor);
    }

    // Jam and clear
    std::cout << "\n--- Conveyor Jam Detected ---\n";
    jamSensor = true;
    if (conveyor) conveyor->update();
    if (conveyor) conveyor->printState();
    jamSensor = false;

    std::cout << "\n--- Jam Cleared ---\n";
    jamCleared = true;
    if (conveyor) conveyor->update();
    if (conveyor) conveyor->printState();
    jamCleared = false;

    // Stop Pump
    std::cout << "\n--- Stopping Pump ---\n";
    stopPump = true;
    if (pump) pump->update();
    if (pump) pump->printState();
    stopPump = false;

    // Remove Pump
    std::cout << "\n--- Removing Pump ---\n";
    manager.removeEquipment("Pump");

    // List again
    std::cout << "\n--- Final Equipment List ---\n";
    manager.listEquipment();

    return 0;
}
