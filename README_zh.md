# esp32-agent-control-demo

[English Version](./README.md)

这个仓库可以看成我拿来理顺 `AI Agent -> ESP32` 这条控制链路的一套小型整理。

我一直觉得，这类项目最麻烦的地方不是“让模型去调一下硬件”，而是把中间这层关系理顺。模型侧的工具调用该怎么写，桥接层该怎么收口，到了 ESP32 端又该怎么把命令分发给屏幕、灯效、舵机和动作模块，这些东西如果一开始不整理清楚，后面基本只会越来越乱。

这个仓库就是围着这件事长出来的。

## 上游参考

- 仓库： [78/xiaozhi-esp32](https://github.com/78/xiaozhi-esp32)
- 描述：`An MCP-based chatbot`
- 观察到的许可证：`MIT`

上游里已经有比较完整的设备侧 MCP 思路，我把自己更关心、也更方便单独拆出来看的那一段重新整理成了这套更小的结构：协议、样例、桥接脚本和固件侧路由示例。

## 这里现在有什么

- 一套面向设备交互的 MCP 风格工具目录
- 一个把 `tools/call` 转成设备命令的桥接脚本
- 命令和状态回传的 JSON Schema
- ESP32 侧处理命令的 clean-room 固件示例

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

## 我为什么单独留这个仓库

因为对我来说，`ESP32 + AI Agent` 真正有意思的不是“能不能调动硬件”，而是中间这层契约到底写得顺不顺：

- 工具名稳不稳定
- 参数有没有类型和范围
- 桥接层是不是够干净
- 设备路由能不能独立于大模型那套东西

把这层单独整理出来以后，后面不管是继续往设备上扩，还是换别的 Agent 方案，都会轻松很多。

## 说明

这个仓库会一直聚焦在控制链路本身。更完整的固件分支和部署细节，会放在别的地方继续长。
