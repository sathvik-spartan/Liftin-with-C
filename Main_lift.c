#include <stdio.h>

#define FLOORS 10
#define UP 1
#define DOWN -1
#define IDLE 0

typedef struct {
    int up[FLOORS];
    int down[FLOORS];
    int cabin[FLOORS];
} RequestQueue;

typedef struct {
    int currentFloor;
    int direction;          // UP = 1, DOWN = -1, IDLE = 0
    RequestQueue requests;
} Elevator;

// UTILITY FUNCTIONS

int anyRequestsAbove(Elevator *e) {
    for (int i = e->currentFloor + 1; i < FLOORS; i++)
        if (e->requests.up[i] || e->requests.down[i] || e->requests.cabin[i])
            return 1;
    return 0;
}

int anyRequestsBelow(Elevator *e) {
    for (int i = e->currentFloor - 1; i >= 0; i--)
        if (e->requests.up[i] || e->requests.down[i] || e->requests.cabin[i])
            return 1;
    return 0;
}

int anyRequests(Elevator *e) {
    for (int i = 0; i < FLOORS; i++)
        if (e->requests.up[i] || e->requests.down[i] || e->requests.cabin[i])
            return 1;
    return 0;
}

// DOOR OPERATION 

void openDoors(Elevator *e) {
    printf(" → Doors opening at floor %d\n", e->currentFloor);
    e->requests.up[e->currentFloor] = 0;
    e->requests.down[e->currentFloor] = 0;
    e->requests.cabin[e->currentFloor] = 0;
    printf(" ← Doors closing...\n");
}

// LIFT MOVEMENT LOGIC 

void moveElevator(Elevator *e) {

    if (!anyRequests(e)) {
        e->direction = IDLE;
        printf("Elevator idle at floor %d\n", e->currentFloor);
        return;
    }

    // Determine direction if idle
    if (e->direction == IDLE) {
        if (anyRequestsAbove(e)) e->direction = UP;
        else if (anyRequestsBelow(e)) e->direction = DOWN;
    }

    // Move UP
    if (e->direction == UP) {
        if (anyRequestsAbove(e)) {
            e->currentFloor++;
        } else if (anyRequestsBelow(e)) {
            e->direction = DOWN;
            return;
        }
    }

    // Move DOWN
    else if (e->direction == DOWN) {
        if (anyRequestsBelow(e)) {
            e->currentFloor--;
        } else if (anyRequestsAbove(e)) {
            e->direction = UP;
            return;
        }
    }

    printf("Lift at floor %d\n", e->currentFloor);

    if (e->requests.up[e->currentFloor] ||
        e->requests.down[e->currentFloor] ||
        e->requests.cabin[e->currentFloor]) {
        openDoors(e);
    }
}

// INPUT HANDLING

void printMenu() {
    printf("\n--- Elevator Simulation ---\n");
    printf("1. Call UP from a floor\n");
    printf("2. Call DOWN from a floor\n");
    printf("3. Cabin request\n");
    printf("4. Simulate one step\n");
    printf("5. Exit\n");
}

// MAIN Function 

int main() {
    Elevator e = {0};
    e.currentFloor = 0;
    e.direction = IDLE;

    int choice, floor;

    while (1) {
        printMenu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Floor (0-%d): ", FLOORS - 1);
                scanf("%d", &floor);
                if (floor < FLOORS - 1 && floor >= 0)
                    e.requests.up[floor] = 1;
                else
                    printf("Invalid UP request.\n");
                break;

            case 2:
                printf("Floor (0-%d): ", FLOORS - 1);
                scanf("%d", &floor);
                if (floor > 0 && floor < FLOORS)
                    e.requests.down[floor] = 1;
                else
                    printf("Invalid DOWN request.\n");
                break;

            case 3:
                printf("Destination (0-%d): ", FLOORS - 1);
                scanf("%d", &floor);
                if (floor >= 0 && floor < FLOORS)
                    e.requests.cabin[floor] = 1;
                else
                    printf("Invalid floor.\n");
                break;

            case 4:
                moveElevator(&e);
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}

// I've optimised the code directly from the test file after a really long time but i'm praying that someone reviews my code.
