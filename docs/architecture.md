# Architecture

## Control Path

The demo splits the control path into three layers:

1. agent-facing tool calls
2. bridge-facing normalized command translation
3. device-facing command execution

## Why Split It This Way

This separation keeps each layer stable for a different reason:

- the AI agent sees natural tool names and typed arguments
- the bridge handles policy, normalization, and validation
- the firmware only needs a compact command envelope

## Layer Responsibilities

### Agent Layer

- issues `tools/call` requests
- uses semantic tool names like `self.screen.show`
- does not need to know board pin mappings or low-level timing

### Bridge Layer

- validates tool names
- validates required arguments
- normalizes aliases and enum values
- emits a device command envelope suitable for transport over WebSocket, MQTT, or serial

### Device Layer

- parses the compact device command
- dispatches by `kind`
- hands off to screen, LED, servo, or motion code
- returns a status report after execution when needed

## Suggested Transport Choices

- WebSocket for interactive local-network demos
- MQTT for multi-device routing and cloud-side orchestration
- serial for minimal offline lab testing

## Portfolio Signal

This architecture shows:

- protocol abstraction
- embedded system boundary design
- AI-agent integration thinking
- awareness of how to keep hardware logic isolated from model-facing complexity
