#include <string>
#include <vector>

enum class PropertyType {
    kInteger,
    kString
};

struct PropertySpec {
    std::string name;
    PropertyType type;
    int min_value = 0;
    int max_value = 0;
};

struct ToolSpec {
    std::string name;
    std::string description;
    std::vector<PropertySpec> properties;
};

std::vector<ToolSpec> BuildToolCatalog() {
    return {
        {
            "self.motion.play",
            "Play a named motion preset on the device.",
            {
                {"speed", PropertyType::kInteger, 1, 5},
                {"name", PropertyType::kString, 0, 0},
            },
        },
        {
            "self.screen.show",
            "Show an expression on the screen.",
            {
                {"duration_ms", PropertyType::kInteger, 200, 10000},
                {"expression", PropertyType::kString, 0, 0},
            },
        },
        {
            "self.led.set",
            "Set LED mode and RGB values.",
            {
                {"r", PropertyType::kInteger, 0, 255},
                {"g", PropertyType::kInteger, 0, 255},
                {"b", PropertyType::kInteger, 0, 255},
                {"mode", PropertyType::kString, 0, 0},
            },
        },
        {
            "self.servo.set",
            "Set one servo channel to an angle.",
            {
                {"channel", PropertyType::kInteger, 0, 7},
                {"angle", PropertyType::kInteger, 0, 180},
            },
        },
    };
}
