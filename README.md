# 从零构建扫地机器人 — 全栈学习项目

从零做一个真正的扫地机器人。五条轨道并行推进，覆盖嵌入式 STM32、ROS2 导航、传感器感知、机械硬件、系统集成。

## 系统架构

```
Linux 开发板 (ROS2 Humble)  ← SLAM、导航、视觉、状态机
       │ UART
STM32                       ← 电机 PID、IMU、悬崖/碰撞传感器、编码器、电池
```

## 五条轨道

| Track | 方向 | 环境 | 当前状态 |
|-------|------|------|---------|
| **A** — 嵌入式 | STM32 下位机开发 | Windows + Keil | 🔄 平衡车调试中 |
| **B** — ROS2 | 上位机软件 + 导航 | Mac VM → Linux 板 | 🔄 ROS2 核心学习 |
| **C** — 感知 | 传感器 + 视觉 + AI | Mac | ✅ Phase 0-2 完成，C2 线激光待开始 |
| **D** — 硬件 | 底盘 + 供电 + 布线 | — | ⏳ 待采购 |
| **E** — 集成 | 联调 + 清扫 Demo | — | ⏳ 等 A-D 就绪 |

## 目录结构

```
robot-vacuum-lab/
├── README.md                    # 项目总览
├── ROADMAP.md                   # 完整五轨学习路线图（核心文档）
├── resources.md                 # 书籍、课程、工具、硬件
├── code/
│   ├── perception/              # Track C: 感知代码
│   ├── stm32/                   # Track A: STM32 代码
│   └── ros2/                    # Track B: ROS2 代码
├── notes/
│   ├── track-a-stm32.md         # Track A 进度与笔记
│   ├── track-b-ros2.md          # Track B 进度与笔记
│   ├── track-c-perception.md    # Track C 进度与笔记
│   ├── track-d-hardware.md      # Track D 进度与笔记
│   └── track-e-integration.md   # Track E 进度与笔记
└── projects/                    # 阶段项目
```

## 快速开始

每个轨道有独立的开发环境，选一个方向开始：

- **Track A**：Windows 上打开 Keil，继续江科大平衡车项目
- **Track B**：Mac VM 中 `source /opt/ros/humble/setup.bash`，写 ROS2 Python 节点
- **Track C**：Mac 上 `source venv/bin/activate`，参考 [ROADMAP.md](./ROADMAP.md) Track C

## 验证里程碑

| 里程碑 | 怎么验证 | 标准 |
|--------|---------|------|
| A1 | 平衡车站立 + 行走 | 不倒地 |
| C2 | 线激光扫杯子 → Open3D | 3D 轮廓可见 |
| C4+B4 | SLAM Toolbox 建图 | 房间地图清晰 |
| E1 | 上位机发指令 → 轮子转 | 走直线 1m ±5cm |
| E3 | 房间自主清扫 | 覆盖率 > 70%，不撞墙 |

## 🔗 相关仓库（2026-06 拆分后）

本项目是"扫地机器人 Capstone"主仓库。学习笔记、基础知识、硬件设计已拆分到：

| 仓库 | 内容 |
|------|------|
| 📚 [embedded-notes](https://github.com/finnyoun9/embedded-notes) | 学习笔记、路线规划、面试八股 |
| 🔵 [stm32-from-scratch](https://github.com/finnyoun9/stm32-from-scratch) | STM32 裸机 + FreeRTOS |
| 🟢 [esp32-playground](https://github.com/finnyoun9/esp32-playground) | ESP32/Arduino 实验 |
| 🔧 [hardware-lab](https://github.com/finnyoun9/hardware-lab) | 原理图/仿真/PCB |
| 🔬 [theory-lab](https://github.com/finnyoun9/theory-lab) | 数电模电理论 |

## 原则

1. **跑通 > 看懂** — 代码能跑比理论精通重要
2. **一 Phase 不完成不进下个** — 验证标准不打折
3. **笔记写 notes/，代码写 code/** — 不让知识散落
4. **完成 > 完美** — 做完了比想得很完美但没动手强
