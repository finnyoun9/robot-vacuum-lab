# 学习资源汇总 — 扫地机传感器与视觉系统

## 书籍

### 核心教材

| 书名 | 作者 | 适合阶段 | 说明 |
|------|------|---------|------|
| 《机器视觉》 | 张广军 | Phase 2 | 中文教材，结构光/线激光/双目最扎实的一本 |
| 《计算机视觉：算法与应用》 | Szeliski | Phase 3,5 | 领域圣经，多视角几何与立体视觉部分 |
| 《Probabilistic Robotics》 | Thrun | Phase 3 | SLAM 和状态估计圣经，占据栅格建图必读 |
| 《机器人学中的状态估计》 | Barfoot | Phase 3,7 | 中文译本，传感器融合理论基础 |
| 《Multiple View Geometry》 | Hartley & Zisserman | Phase 5 | 多视角几何参考书，难度较高 |
| 《学习 OpenCV 3》 | Kaehler & Bradski | Phase 1-2 | OpenCV 工具书 |

### 深度学习

| 书名 | 作者 | 说明 |
|------|------|------|
| 《动手学深度学习》 | 李沐等 | 中文，有代码，CNN 基础 |
| 《深度学习》(花书) | Goodfellow | 理论经典，按需查阅 |

---

## 在线课程

| 课程 | 平台 | 适合阶段 |
|------|------|---------|
| [First Principles of Computer Vision](https://www.youtube.com/@firstprinciplesofcomputerv3258) | YouTube | Phase 1-2 |
| [CS231n: Deep Learning for Computer Vision](http://cs231n.stanford.edu/) | Stanford | Phase 6 |
| [OpenCV Python Tutorials](https://docs.opencv.org/master/d6/d00/tutorial_py_root.html) | 官方文档 | Phase 1-2 |
| [Cyrill Stachniss SLAM 课程](https://www.youtube.com/playlist?list=PLgnQpQtFTOGQrZ4O5QzbIHgl3b1JHimN_) | YouTube | Phase 3 |
| [ROS2 Tutorials](https://docs.ros.org/en/humble/Tutorials.html) | 官方文档 | Phase 7（如果之后接 ROS）|

---

## 传感器硬件资源

### 线激光模组
| 型号/来源 | 说明 |
|-----------|------|
| 淘宝 "650nm 线激光模组" | 选可调焦距的，5mW 足够，带驱动的更好 |
| 淘宝 "一字线激光" | 另一种说法，60-90° 发散角 |
| 带通滤光片 650nm | 装在相机镜头上，只让激光波长通过，抗环境光 |

### 激光雷达（LDS）
| 型号 | 价格 | 说明 |
|------|------|------|
| YDLIDAR X4 | ~300 元 | 10m 范围，5000 pts/s，三角法 |
| RPLIDAR A1M8 | ~400 元 | 思岚入门款，12m 范围，SDK 成熟 |
| RPLIDAR A2 | ~600 元 | 更高频率，更适合机器人 |
| 二手扫地机拆机 LDS | ~50-100 元 | 咸鱼搜"扫地机激光头"，Roborock/Dreame 拆机件 |

> 三角法雷达原理都一样，入门买 YDLIDAR X4 性价比最高。

### ToF / 红外传感器
| 型号 | 价格 | 说明 |
|------|------|------|
| VL53L0X 模块 | ~15 元 | I2C，2m 范围，单区 |
| VL53L1X 模块 | ~30 元 | I2C，4m 范围，多区（ROI），推荐 |
| Sharp GP2Y0A21 | ~25 元 | 模拟输出，10-80cm 红外三角 |
| 红外避障模块 | ~2 元 | 简单反射式，2-30cm |

### 深度相机（Phase 5 对比用）
| 型号 | 价格 | 说明 |
|------|------|------|
| Intel RealSense D435 | ~1500 元 | 双目+结构光辅助 |
| 奥比中光 Astra Pro | ~600 元 | 国产结构光方案 |
| 两个同型号 USB 摄像头 | ~100 元 | 自己搭双目 |

### 扫地机拆解参考
| 资源 | 说明 |
|------|------|
| B 站 "Roborock 拆解" | 看内部传感器布局 |
| iFixit 扫地机拆解 | 看 iRobot Roomba 结构 |
| [Roborock 技术博客](https://blog.roborock.com/) | 官方技术介绍 |

---

## 关键工具与库

| 工具 | 用途 | 阶段 |
|------|------|------|
| OpenCV | 图像处理、相机标定、激光线提取 | Phase 1-5 |
| NumPy | 数组计算基础 | 全阶段 |
| Open3D | 点云处理与可视化 | Phase 2,5 |
| Matplotlib | 数据可视化（雷达点云等）| 全阶段 |
| PySerial | 串口通信（雷达数据读取）| Phase 3 |
| smbus2 | I2C 通信（VL53L0X）| Phase 4 |
| ONNX Runtime | AI 模型推理部署 | Phase 6 |
| PyTorch | 深度学习训练 | Phase 6 |
| Ultralytics | YOLO 训练（最简单入口）| Phase 6 |
| ROS2 | 机器人框架（如果后续接机器人底盘）| Phase 7 |

---

## 数据集

| 数据集 | 内容 | 用途 |
|--------|------|------|
| [COCO](https://cocodataset.org/) | 80 类通用检测 | Phase 6 预训练基准 |
| [TACO](http://tacodataset.org/) | 户外垃圾数据集 | 可借鉴做障碍物检测 |
| 自采集数据 | 贴地视角拍线缆/鞋子 | Phase 6 核心训练数据 |

---

## 扫地机行业参考

### 主流产品传感器配置

| 产品 | LDS | 线激光 | RGB 相机 | 红外悬崖 | ToF | 备注 |
|------|-----|--------|----------|----------|-----|------|
| Roborock S8 | 有 | 有 | 有 | 有 | - | 3D 避障 |
| Roborock Q Revo | 有 | - | - | 有 | - | 基础型号 |
| Dreame X40 | 有 | 有 | 有 | 有 | - | 线激光+AI |
| iRobot Roomba j7+ | - | - | 有 | 有 | - | 纯视觉方案 |
| Ecovacs X2 | 有 | 有 | 有 | 有 | - | 半固态雷达 |

### 关键供应商

| 品牌 | 产品 | 说明 |
|------|------|------|
| 思岚 SLAMTEC | LDS 雷达、SLAM 模组 | 国内扫地机雷达主要供应商 |
| 欢创 Camsense | 三角法雷达 | 多家扫地机厂商供应商 |
| ST意法半导体 | VL53L0X/VL53L1X ToF | 扫地机悬崖传感器常用 |
| 奥比中光 | 深度相机 | 3D 结构光方案 |

---

## 中文社区

| 资源 | 说明 |
|------|------|
| [自动驾驶之心](https://www.zdjszx.com/) | 感知方向中文社区 |
| 知乎 "扫地机器人" 话题 | 产品测评、技术讨论 |
| B 站 "扫地机拆机评测" | 大量拆解视频 |
| 52pojie 扫地机逆向 | 协议分析和破解 |

---

## 云 GPU 平台

| 平台 | 说明 |
|------|------|
| [AutoDL](https://www.autodl.com/) | 国内按小时租，性价比高 |
| [恒源云](https://www.gpushare.com/) | 国内 GPU 租用 |
| Google Colab | 免费 T4，轻量实验够用 |
