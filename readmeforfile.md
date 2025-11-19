# VEX V5 Robot Control System - LemLib Implementation

This project is a comprehensive robot control system built for VEX V5 robotics using the LemLib library for advanced chassis control and odometry.

## Robot Hardware Configuration

### Drivetrain
- **Wheels**: 4 Omniwheel + 4 Traction wheels (3.25" diameter)
- **Motors**: 4 VEX 11W Smart Motors with blue cartridges (600 RPM)
- **Additional Motors**: 2 VEX 5.5W Smart Motors at 200 RPM
- **Drive Modes**: Supports Arcade, Curvature, and Tank drive
- **No deadzone implementation** for maximum sensitivity

### Chain Hoist System
- **3 Motors** for multi-level lifting mechanism:
  - `chainHoist1` (Port 12): Primary hoist motor
  - `chainHoist2` (Port 18): Secondary hoist motor  
  - `chainHoist3` (Port 6): Directional control motor

### Pneumatics
- Helper intake pneumatics (Port A)
- Flap pneumatic system (Port B)

### Sensors
- IMU on Port 7 for heading tracking
- Horizontal rotation sensor (Port 10) 
- Vertical rotation sensor (Port 19)
- AI Vision sensor (Port 13)

## Control Scheme

### Drive Controls
| Input | Function |
|-------|----------|
| **Left Stick Y** | Forward/Backward movement |
| **Right Stick X** | Turning/Steering |
| **Left Arrow (D-Pad)** | Cycle through drive modes |

### Drive Modes
1. **Curvature Drive** (Default) - Smooth curved turning
2. **Arcade Drive** - Traditional arcade-style controls
3. **Tank Drive** - Independent left/right side control

### Subsystem Controls
| Button | Function |
|--------|----------|
| **L1** | Toggle boost levels (Normal → Medium → Max → Normal) |
| **L2** | Chain hoist custom mode (chainHoist1 only) |
| **R1** | Top rack mode (all motors reverse) |
| **R2** | Middle rack mode (chainHoist1,2 reverse, chainHoist3 forward) |
| **Y** | Enter diagnostic/update loop |

### Boost Levels
- **Level 0**: Normal voltage (111.01V)
- **Level 1**: Medium boost (120.0V) 
- **Level 2**: Maximum boost (127.0V)

## Code Structure & Modification Guide

### Core Files

#### [`main.cpp`](src/main.cpp)
**Purpose**: Main program entry point and robot lifecycle management
**Functions**:
- `initialize()`: Sets up chassis calibration and subsystem initialization
- `autonomous()`: Autonomous period control
- `opcontrol()`: Driver control period with main control loop
- `disabled()`: Safely stops all systems when disabled

**To Modify**:
- **Button bindings**: Change controller mappings in `opcontrol()` function
- **Initialization sequence**: Modify `initialize()` to change startup behavior
- **Autonomous routines**: Edit `autonomous()` for competition autonomous code
- **Main control loop timing**: Adjust `pros::delay(20)` value in `opcontrol()`

#### Hardware Configuration: [`globals.h`](include/globals.h) / [`global.cpp`](src/global.cpp)
**Purpose**: All hardware definitions, port assignments, and configurations

**To Modify Motor Configuration**:
```cpp
// In global.cpp - Change motor ports and settings
pros::Motor RightFront(2, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor chainHoist1(12, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
```

**To Modify Sensor Configuration**:
```cpp
// In global.cpp - Change sensor ports
pros::Imu mainIMU(7); // Change port number
pros::Rotation horizontalRotation(10); // Change port number
```

**To Modify LemLib Settings**:
```cpp
// In global.cpp - Adjust PID values and drive curves
lemlib::ControllerSettings lateral_controller(10, 0, 3, 3, 1, 100, 3, 500, 20);
```

#### Drivetrain Control: [`drivetrain.h`](include/robot/drivetrain.h) / [`drivetrain.cpp`](src/system/drivetrain.cpp)
**Purpose**: All drivetrain movement and control logic

**To Modify Drive Modes**:
- **Add new drive mode**: Add to `DRIVE_MODE` enum in `drivetrain.h`, implement function in `drivetrain.cpp`
- **Change drive sensitivity**: Modify drive functions `ArcadeDrive()`, `TankDrive()`, `CurvatureDrive()`
- **Adjust control curves**: Edit arcade drive parameters in `ArcadeDrive()` function
- **Change default drive mode**: Modify `driveMode` initialization in `initialize()`

**To Modify Drive Switching**:
```cpp
// In drivetrain.cpp - Edit SwitchDrive() function to change mode names/behavior
std::string drive::SwitchDrive(int driveMode) {
    switch (driveMode) {
    case 0: // Modify this case for different default mode
        drive::driveMode = CURVATURE_DRIVE;
```

#### Subsystem Control: [`subsystems.h`](include/robot/subsystems.h) / [`subsystems.cpp`](src/system/subsystems.cpp)
**Purpose**: All non-drivetrain mechanisms (chain hoist, pneumatics, etc.)

**To Modify Chain Hoist Control**:
```cpp
// In subsystems.cpp - Edit start() function button mappings
if (r1) {
    // Change motor directions and voltages here
    chainHoist1.move_voltage(-voltageInt);
}
```

**To Modify Pneumatic Control**:
```cpp
// In subsystems.cpp - Edit pneumatic logic in start() function
// Currently commented out - uncomment and modify as needed
```

**To Modify Boost System**:
```cpp
// In subsystems.cpp - Edit boost() function voltage levels
case 1:
    regularVoltage = 120.0; // Change boost voltage here
```

**To Add New Subsystem Functions**:
1. Declare function in `subsystems.h`
2. Implement in `subsystems.cpp`
3. Call from `run()` function or add button binding in `start()`

## Customization Examples

### Adding a New Motor
1. **Hardware Definition** (`global.cpp`):
```cpp
pros::Motor newMotor(PORT_NUMBER, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
```

2. **Header Declaration** (`globals.h`):
```cpp
extern pros::Motor newMotor;
```

3. **Initialize in Subsystems** (`subsystems.cpp`):
```cpp
void robot::Subsystems::initialize() {
    // Add motor initialization
    newMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}
```

### Adding a New Button Control
1. **In main.cpp** (`opcontrol()` function):
```cpp
if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
    // Call your function here
    subsystem.subsystems.yourNewFunction();
}
```

### Changing Drive Mode Cycle Order
1. **In drivetrain.cpp** (`SwitchDrive()` function):
```cpp
// Reorder or change the case numbers to modify cycle order
case 0: drive::driveMode = TANK_DRIVE; // Changed from CURVATURE_DRIVE
```

### Modifying PID Values
1. **In global.cpp** (Controller Settings):
```cpp
lemlib::ControllerSettings lateral_controller(
    15, // kP - increase for faster response
    0.1, // kI - add for steady-state error correction
    5,  // kD - increase for less overshoot
    // ... other parameters
);
```

## File Organization Summary

| Want to Change | Edit These Files |
|----------------|------------------|
| **Motor ports/hardware** | `globals.h`, `global.cpp` |
| **Button mappings** | `main.cpp` (opcontrol function) |
| **Drive behavior** | `drivetrain.h`, `drivetrain.cpp` |
| **Subsystem mechanisms** | `subsystems.h`, `subsystems.cpp` |
| **PID/LemLib settings** | `global.cpp` |
| **Initialization sequence** | `main.cpp` (initialize function) |
| **Autonomous routines** | `main.cpp` (autonomous function) |
| **Main control loop** | `main.cpp` (opcontrol function) |

## Development Notes

### Dependencies
- **PROS**: VEX V5 development environment
- **LemLib**: Advanced chassis control library
- **Standard C++ libraries**: For string handling and math operations

### Performance Considerations
- 20ms main loop delay for stable operation
- Temperature monitoring prevents motor damage
- Efficient memory usage with static variables
- Proper resource cleanup in disabled state

This system provides a robust foundation for competitive VEX robotics with advanced features for precise control and monitoring.
