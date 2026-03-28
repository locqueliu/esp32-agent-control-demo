import argparse
import json
from pathlib import Path


TOOL_TO_KIND = {
    "self.motion.play": "motion.play",
    "self.screen.show": "screen.show",
    "self.led.set": "led.set",
    "self.servo.set": "servo.set",
}


def require(arguments, key):
    if key not in arguments:
        raise ValueError(f"missing required argument: {key}")
    return arguments[key]


def normalize_params(tool_name, arguments):
    if tool_name == "self.motion.play":
        return {
            "name": require(arguments, "name"),
            "speed": int(arguments.get("speed", 3)),
        }

    if tool_name == "self.screen.show":
        return {
            "expression": require(arguments, "expression"),
            "duration_ms": int(arguments.get("duration_ms", 1500)),
        }

    if tool_name == "self.led.set":
        return {
            "mode": require(arguments, "mode"),
            "r": int(require(arguments, "r")),
            "g": int(require(arguments, "g")),
            "b": int(require(arguments, "b")),
        }

    if tool_name == "self.servo.set":
        return {
            "channel": int(require(arguments, "channel")),
            "angle": int(require(arguments, "angle")),
        }

    raise ValueError(f"unsupported tool name: {tool_name}")


def translate(payload, device_id):
    method = payload.get("method")
    if method != "tools/call":
        raise ValueError("only tools/call payloads are supported in this demo")

    params = payload.get("params", {})
    tool_name = params.get("name")
    if tool_name not in TOOL_TO_KIND:
        raise ValueError(f"unknown tool: {tool_name}")

    arguments = params.get("arguments", {})
    return {
        "device_id": device_id,
        "kind": TOOL_TO_KIND[tool_name],
        "params": normalize_params(tool_name, arguments),
    }


def main():
    parser = argparse.ArgumentParser(description="Translate MCP-style tool calls into device commands.")
    parser.add_argument("--input", required=True, help="Path to an MCP-style JSON payload.")
    parser.add_argument("--device-id", default="esp32-pet-01", help="Target device id.")
    parser.add_argument("--pretty", action="store_true", help="Pretty-print JSON output.")
    args = parser.parse_args()

    payload = json.loads(Path(args.input).read_text(encoding="utf-8"))
    command = translate(payload, args.device_id)

    if args.pretty:
        print(json.dumps(command, indent=2, ensure_ascii=False))
    else:
        print(json.dumps(command, ensure_ascii=False))


if __name__ == "__main__":
    main()
