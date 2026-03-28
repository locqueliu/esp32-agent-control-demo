# esp32-agent-control-demo

[English Version](./README.md)

这个仓库可以看成一条比较紧凑的 `AI Agent -> ESP32` 控制链路。

我主要用它来整理一个很实际的问题：模型侧的工具调用应该长什么样，桥接层怎么把它们归一成设备命令，而 ESP32 端又该怎样把这些命令稳定地分发到屏幕、灯效、舵机和动作层。

## 上游参考

- 仓库： [78/xiaozhi-esp32](https://github.com/78/xiaozhi-esp32)
- 描述：`An MCP-based chatbot`
- 观察到的许可证：`MIT`

之所以把它作为参考，是因为上游已经有比较完整的设备侧 MCP 控制思路。这个仓库则保留了我自己更小、更好读的一版：协议结构、样例、桥接脚本和固件侧的 clean-room 路由示例。

## 包含内容

- 一套面向设备交互的 MCP 风格工具目录
- 一个把 `tools/call` 转成设备命令的桥接脚本
- 命令和状态回传的 JSON Schema
- ESP32 端处理命令的 clean-room 固件示例

## 仓库结构

- [`docs/upstream-reference.md`](./docs/upstream-reference.md) 上游背景和仓库边界
- [`docs/architecture.md`](./docs/architecture.md) 从 Agent 到设备的控制流
- [`docs/tool-catalog.md`](./docs/tool-catalog.md) 工具命名和参数模型
- [`schemas/device-command.schema.json`](./schemas/device-command.schema.json) 命令结构
- [`schemas/device-status.schema.json`](./schemas/device-status.schema.json) 状态结构
- [`examples/mcp`](./examples/mcp) MCP 风格请求和响应示例
- [`examples/device`](./examples/device) 设备侧命令示例
- [`bridge/mcp_to_device_bridge.py`](./bridge/mcp_to_device_bridge.py) 可直接运行的桥接脚本
- [`firmware/command_router_example.cpp`](./firmware/command_router_example.cpp) 命令路由示例
- [`firmware/tool_registry_example.cpp`](./firmware/tool_registry_example.cpp) 精简版工具注册示例

## 核心工具

- `self.motion.play`
- `self.screen.show`
- `self.led.set`
- `self.servo.set`

## 快速运行

转换一条 MCP 风格请求：

```powershell
python .\bridge\mcp_to_device_bridge.py --input .\examples\mcp\tools.call.motion.play.json --pretty
```

再转换另一条请求：

```powershell
python .\bridge\mcp_to_device_bridge.py --input .\examples\mcp\tools.call.led.set.json
```

## 我为什么保留这个仓库

对我来说，`ESP32 + AI Agent` 真正有意思的地方不只是“模型可以触发硬件”，而是中间这层契约怎么设计：

- 工具名要稳定
- 参数要有类型和范围
- 桥接层要尽量简单
- 设备路由不要依赖大模型特有逻辑

## 说明

这个仓库会一直聚焦在控制链路本身。更完整的固件分支和部署细节，会放在别的地方继续演化。
