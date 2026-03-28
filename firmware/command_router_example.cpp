#include <map>
#include <string>

struct DeviceCommand {
    std::string kind;
    std::map<std::string, int> int_params;
    std::map<std::string, std::string> string_params;
};

void ShowExpression(const std::string& expression, int duration_ms);
void SetLedMode(const std::string& mode, int r, int g, int b);
void SetServoAngle(int channel, int angle);
void PlayMotion(const std::string& name, int speed);

void RouteCommand(const DeviceCommand& command) {
    if (command.kind == "screen.show") {
        ShowExpression(
            command.string_params.at("expression"),
            command.int_params.at("duration_ms"));
        return;
    }

    if (command.kind == "led.set") {
        SetLedMode(
            command.string_params.at("mode"),
            command.int_params.at("r"),
            command.int_params.at("g"),
            command.int_params.at("b"));
        return;
    }

    if (command.kind == "servo.set") {
        SetServoAngle(
            command.int_params.at("channel"),
            command.int_params.at("angle"));
        return;
    }

    if (command.kind == "motion.play") {
        PlayMotion(
            command.string_params.at("name"),
            command.int_params.at("speed"));
        return;
    }
}
