# Classic LLD of Elevator Simulation System

## **1. Overview**

This LLD describes a **single-elevator simulation system** implemented in C using a **modular, struct-based design**.
The simulation supports:

* Up requests (from outside the elevator)
* Down requests (from outside the elevator)
* Cabin requests (inside the elevator)
* Step-by-step elevator movement
* Directional logic (UP, DOWN, IDLE)
* Automated door operations

The system moves the elevator **one floor per simulation cycle** based on pending requests.

---

# **2. Architecture Components**

## **2.1 Data Structures**

### **2.1.1 `RequestQueue`**

Stores all pending requests for the elevator.

```c
typedef struct {
    int up[FLOORS];
    int down[FLOORS];
    int cabin[FLOORS];
} RequestQueue;
```

**Responsibilities**

* Maintain separate lists for UP, DOWN, and CABIN requests.
* Allow request lookup for each floor.
* Allow easy clearing of requests when elevator arrives.

---

### **2.1.2 `Elevator`**

Represents the elevator’s current state.

```c
typedef struct {
    int currentFloor;  
    int direction;     
    RequestQueue requests;
} Elevator;
```

**Responsibilities**

* Track the current floor.
* Track movement direction (`UP`, `DOWN`, or `IDLE`).
* Embed the request queue.

---

# **3. Modules**

## **3.1 Request Checking Module**

### `anyRequestsAbove(Elevator *e)`

Checks if any pending UP, DOWN, or CABIN requests exist above the elevator.

### `anyRequestsBelow(Elevator *e)`

Same as above but checks floors below.

### `anyRequests(Elevator *e)`

Checks if any request exists anywhere in the building.

**Responsibilities**

* Help elevator choose direction.
* Assist in movement/idle logic.

---

## **3.2 Door Module**

### `openDoors(Elevator *e)`

Handles door operations when elevator reaches a requested floor.

**Actions**

* Print door open/close messages.
* Clear all types of requests at that floor:

  * `up[floor] = 0`
  * `down[floor] = 0`
  * `cabin[floor] = 0`

---

## **3.3 Elevator Movement Module**

### `moveElevator(Elevator *e)`

Moves elevator one floor based on pending requests and current direction.

**Responsibilities**

1. Determine direction if elevator is IDLE.
2. Move UP if:

   * Requests exist above.
3. Move DOWN if:

   * Requests exist below.
4. Reverse direction if:

   * Current direction has no pending requests ahead.
5. Call door operations when arriving at a floor with requests.
6. Print current floor.

**Rules**

* Elevator continues in the current direction as long as requests exist in that direction.
* If no requests in the current direction, it reverses direction.
* If no requests at all → stays IDLE.

---

## **3.4 Input Handling Module**

### `printMenu()`

Prints menu options for the simulation.

### Input Options

| Choice | Action                                |
| ------ | ------------------------------------- |
| 1      | Add UP request at a floor             |
| 2      | Add DOWN request at a floor           |
| 3      | Add cabin request (destination floor) |
| 4      | Simulate one elevator movement step   |
| 5      | Exit the simulation                   |

**Validations**

* UP cannot be requested on top floor.
* DOWN cannot be requested on ground floor.
* Cabin floor must be between `0` and `FLOORS - 1`.

---

# **4. Control Flow**

### **4.1 User Input Loop**

1. Display menu.
2. Read user choice.
3. Based on choice:

   * Add request.
   * Simulate elevator movement.

---

### **4.2 Movement Flow**

```
Check if any pending requests
    ↓
If no -> direction = IDLE and stop
    ↓
If IDLE and requests above -> direction = UP
If IDLE and requests below -> direction = DOWN
    ↓
If direction = UP:
    If requests above: move up 1 floor
    Else if requests below: direction = DOWN (no movement this cycle)
If direction = DOWN:
    If requests below: move down 1 floor
    Else if requests above: direction = UP
    ↓
Print current floor
    ↓
If requests exist at this floor: open doors()
```

---

# **5. Constraints**

* Floors defined by constant `FLOORS`.
* Valid floor range: `0` to `FLOORS - 1`.
* Invalid requests must not be added.

---

# **6. Extensibility Points**

The new design supports future enhancements:

* Multi-elevator system
* Logging and analytics
* Real-time (threaded) movement
* Load balancing and scheduling algorithms
* Door timing animations
* Emergency handling
* Priority queues

---

# **7. Summary**

This LLD provides a modular, maintainable structure for an elevator simulation by:

* Using `struct`-based design
* Separating responsibilities into clear modules
* Implementing a clean request-handling and direction logic
* Supporting future scalability

---
