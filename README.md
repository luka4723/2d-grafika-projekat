# Car Driving Simulation

A 2D graphics project demonstrating real-time rendering techniques, particle systems, framebuffer effects, and stencil-based rendering. The player controls a car while collecting randomly generated objects that trigger different visual and gameplay effects.

## Features

### Car Movement
- The car can be controlled using **WASD** keys.
- The car is constrained to the road and cannot leave the screen boundaries.
- The movement speed gradually increases over time.

### Particle System
- Smoke particles are emitted from the car exhaust.
- Particles use alpha blending to create a transparent effect.
- Particle colors can change dynamically depending on active effects.

### Collectible Objects and Effects

Objects are randomly generated on the road and can be collected by the player:

#### Mushroom
- Applies a full-screen color distortion effect using bilinear interpolation.
- Effect intensity and colors are randomly generated.
- The effect gradually fades until it disappears.
- While active, exhaust particles change color.

#### Drink
- Reverses the car's movement controls for 5 seconds.

#### Bottle
- Creates a spiral directional blur effect.
- The blur direction follows a rotating vector that gradually decreases in magnitude until the effect disappears.
- Implemented using a framebuffer.

#### Mud
- When the car drives through mud, random circular stains are rendered on the screen using stencil buffering.
- Multiple mud effects can accumulate if collected within a short time interval.
- Stains are automatically cleaned after several seconds.

### Additional Features
- **Pause (P key)**
  - Inverts screen colors while paused.
  - Preserves the current directional blur vector and mushroom effect intensity.

- **Screen Rotation (R key)**
  - Rotates the entire scene.

- **Exit (ESC key)**
  - Closes the game.

### Procedural Road Generation
- The road is generated dynamically by randomly selecting and placing tiles.

## Demo

![Demo](domaci1-demo.mp4)

## Building and Running

1. Open the project using CMake.
2. Configure and build the project.
3. Run the generated executable (`main`).

