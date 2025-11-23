#include <stdio.h>

#define FLOORS 10

int upRequests[FLOORS] = {0};
int downRequests[FLOORS] = {0};
int carRequests[FLOORS] = {0};

int currentFloor = 0;
int direction = 1; // 1 = UP, -1 = DOWN

int anyRequestsAbove() {
    for (int i = currentFloor + 1; i < FLOORS; i++)
        if (upRequests[i] || downRequests[i] || carRequests[i])
            return 1;
    return 0;
}

int anyRequestsBelow() {
    for (int i = currentFloor - 1; i >= 0; i--)
        if (upRequests[i] || downRequests[i] || carRequests[i])
            return 1;
    return 0;
}

int anyPendingRequests() {
    for (int i = 0; i < FLOORS; i++)
        if (upRequests[i] || downRequests[i] || carRequests[i])
            return 1;
    return 0;
}

void openDoors() {
    printf(" → Doors opening at floor %d\n", currentFloor);
    upRequests[currentFloor] = 0;
    downRequests[currentFloor] = 0;
    carRequests[currentFloor] = 0;
}

void moveLift() {
    if (direction == 1) { // UP
        if (anyRequestsAbove()) {
            currentFloor++;
            printf("Lift moving UP to floor %d\n", currentFloor);
            if (upRequests[currentFloor] || carRequests[currentFloor])
                openDoors();
        } else {
            direction = -1;
        }
    } else { // DOWN
        if (anyRequestsBelow()) {
            currentFloor--;
            printf("Lift moving DOWN to floor %d\n", currentFloor);
            if (downRequests[currentFloor] || carRequests[currentFloor])
                openDoors();
        } else {
            direction = 1;
        }
    }
}

void printMenu() {
    printf("\n--- Elevator Simulation ---\n");
    printf("1. Call UP from a floor\n");
    printf("2. Call DOWN from a floor\n");
    printf("3. Press cabin button (inside lift)\n");
    printf("4. Simulate one step\n");
    printf("5. Exit\n");
}

int main() {
    int choice, floor;

    while (1) {
        printMenu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Floor (0-%d): ", FLOORS-1);
                scanf("%d", &floor);
                if (floor >= 0 && floor < FLOORS) upRequests[floor] = 1;
                break;

            case 2:
                printf("Floor (0-%d): ", FLOORS-1);
                scanf("%d", &floor);
                if (floor >= 0 && floor < FLOORS) downRequests[floor] = 1;
                break;

            case 3:
                printf("Destination floor (0-%d): ", FLOORS-1);
                scanf("%d", &floor);
                if (floor >= 0 && floor < FLOORS) carRequests[floor] = 1;
                break;

            case 4:
                if (anyPendingRequests())
                    moveLift();
                else
                    printf("No pending requests. Elevator idle at floor %d.\n", currentFloor);
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
