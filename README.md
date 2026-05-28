# 计算机视觉学习之路

从零开始系统学习计算机视觉与机器视觉，从 2D 图像处理到 3D 感知，从传统算法到深度学习。

## 这是什么

一份**可执行的学习路线图**，不是收藏夹。每个 Phase 有明确的学习目标、动手练习和验证标准。完成一个检查一个。

## 快速开始

```bash
python -m venv venv
source venv/bin/activate
pip install opencv-python numpy matplotlib jupyter
```

然后打开 [ROADMAP.md](./ROADMAP.md) 从 Phase 0 开始。

## 目录结构

```
cv-learning-roadmap/
├── README.md           # 你在这里
├── ROADMAP.md          # 完整学习路线图（核心文档）
├── resources.md        # 书籍、课程、工具、硬件
├── notes/              # 学习笔记
├── code/               # 练习代码（按 Phase 组织）
└── projects/           # 阶段项目
```

## 路线概览

| Phase | 主题 | 周期 |
|-------|------|------|
| 0 | 环境准备 | 1 周 |
| 1 | 2D 视觉基础：OpenCV、图像处理、相机标定 | 2-4 周 |
| 2 | 深度学习视觉：YOLO、分割、模型部署 | 4-6 周 |
| 3 | 3D 感知：双目、线激光、点云处理 | 4-8 周 |
| 4 | 系统工程：硬件选型、标定、实时 pipeline | 持续 |
| 5 | 领域深入：工业检测 / 机器人 / 自动驾驶 | 择一 |

## 原则

1. **先跑通再看懂** — 代码能跑比理论精通重要
2. **一个 Phase 没完成不进下一个** — 验证标准不打折
3. **笔记写到 notes/，代码写到 code/** — 不让知识散落
4. **完成 > 完美** — 「做完了」比「想得很完美但没动手」强一百倍
