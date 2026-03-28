# Tool Catalog

## Naming Style

Recommended pattern:

- `self.<module>.<action>`

This keeps tools readable for both AI agents and engineers.

## Demo Tools

### `self.motion.play`

Purpose:

- trigger a named motion preset such as `wave`, `nod`, or `idle_bounce`

Arguments:

- `name`: string
- `speed`: integer from 1 to 5

### `self.screen.show`

Purpose:

- display an expression or UI state on the screen

Arguments:

- `expression`: string
- `duration_ms`: integer from 200 to 10000

### `self.led.set`

Purpose:

- set the LED mode and RGB color

Arguments:

- `mode`: string
- `r`: integer from 0 to 255
- `g`: integer from 0 to 255
- `b`: integer from 0 to 255

### `self.servo.set`

Purpose:

- set one servo channel to a target angle

Arguments:

- `channel`: integer from 0 to 7
- `angle`: integer from 0 to 180

## Why These Four

These tools are enough to demonstrate:

- behavior-level control
- visual feedback
- low-level actuator control
- a realistic hardware abstraction boundary
