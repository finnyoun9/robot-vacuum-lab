# 计算机视觉学习路线图

> 从 2D 图像处理到 3D 感知，从传统算法到深度学习，系统掌握机器视觉 / 计算机视觉领域。
> 每个 Phase 建议按顺序完成，后面的内容依赖前面的基础。

---

## Phase 0 — 环境准备

**目标**：搭好开发环境，跑通第一个 OpenCV demo。

### 知识点

- Python 虚拟环境（venv / conda）
- OpenCV 安装与基本 IO（读图、显示、写图）
- NumPy 基础（数组操作、索引、广播）
- Matplotlib 可视化
- Jupyter Notebook / VS Code 开发环境

### 动手练习

```bash
# 创建虚拟环境
python -m venv venv
source venv/bin/activate
pip install opencv-python numpy matplotlib jupyter

# 写一个脚本：读取图片 → 转灰度 → 显示 → 保存
```

### 验证标准

- [ ] 能用 OpenCV 读取图片、视频文件、摄像头实时流
- [ ] 理解图像在 NumPy 中的数据结构（H×W×C, dtype=uint8）
- [ ] 能用 Matplotlib 正确显示 BGR/RGB 图像（注意通道顺序转换）

### 推荐资源

- [OpenCV 官方 Python Tutorial](https://docs.opencv.org/master/d6/d00/tutorial_py_root.html)
- [NumPy 快速入门](https://numpy.org/doc/stable/user/quickstart.html)

---

## Phase 1 — 2D 视觉基础（2-4 周）

**目标**：掌握图像处理核心操作，理解相机成像模型，完成相机标定。

### 知识点

#### 图像处理基础
- 色彩空间（RGB / HSV / LAB）与转换
- 直方图、直方图均衡化、自适应直方图均衡(CLAHE)
- 滤波：高斯模糊、中值滤波、双边滤波
- 边缘检测：Sobel、Canny、Laplacian
- 形态学操作：腐蚀、膨胀、开运算、闭运算
- 阈值分割：全局阈值、Otsu、自适应阈值
- 轮廓检测与分析：面积、周长、外接矩形、凸包
- 几何变换：仿射变换、透视变换、图像拼接基础

#### 特征与匹配
- 角点检测：Harris、Shi-Tomasi
- 特征描述子：SIFT、ORB、AKAZE
- 特征匹配：BFMatcher、FLANN、RANSAC
- 模板匹配：相关性匹配、多尺度匹配

#### 相机成像模型
- 针孔相机模型：世界坐标系 → 相机坐标系 → 图像坐标系 → 像素坐标系
- 内参矩阵 K：焦距(fx, fy)、主点(cx, cy)
- 外参：旋转矩阵 R、平移向量 t
- 畸变模型：径向畸变(k1, k2, k3)、切向畸变(p1, p2)
- **张正友标定法**：棋盘格拍摄 → 角点提取 → 标定计算 → 重投影误差评估

### 动手练习

1. **拍照标定**：打印棋盘格，用手机拍 15-20 张不同角度照片，跑通 `cv2.calibrateCamera()`
2. **畸变矫正**：用标定结果矫正广角照片/视频
3. **文档扫描仪**：拍照 → 找四边形轮廓 → 透视变换 → 输出矫正后的文档图像
4. **全景拼接**：拍一组重叠照片，用 SIFT + 单应矩阵拼接

### 验证标准

- [ ] 能解释图像从 BGR 转 HSV 后每个通道代表什么
- [ ] 能独立完成相机标定并评估标定精度（重投影误差 < 0.5 pixel）
- [ ] 能根据场景选择正确的预处理流程（比如：检测划痕该用什么滤波 + 什么阈值方法）
- [ ] 理解畸变矫正的物理意义

### 推荐资源

- 《学习 OpenCV 3》（Kaehler & Bradski）—— 第 1-13 章
- [OpenCV Camera Calibration Tutorial](https://docs.opencv.org/master/dc/dbb/tutorial_py_calibration.html)
- 《计算机视觉：算法与应用》（Szeliski）—— 第 2-4 章
- [张正友标定论文 (2000)](https://www.microsoft.com/en-us/research/publication/a-flexible-new-technique-for-camera-calibration/)

---

## Phase 2 — 深度学习视觉（4-6 周）

**目标**：掌握目标检测与图像分割模型的使用、微调和部署。

### 知识点

#### 模型基础
- CNN 核心概念：卷积层、池化层、感受野、特征图
- 分类网络：AlexNet → VGG → ResNet → EfficientNet
- 目标检测：两阶段(Faster R-CNN) vs 单阶段(YOLO/SSD)
- YOLO 系列演进：YOLOv5 → YOLOv8 → YOLOv11
- 实例分割：Mask R-CNN、YOLOv8-seg
- 语义分割：U-Net、DeepLab
- 基础模型：SAM (Segment Anything Model)

#### 实战技能
- 数据集准备：标注格式(COCO/YOLO)、数据增强(Albumentations)
- 模型微调：用预训练权重在自己的数据上 finetune
- 评估指标：mAP、IoU、Precision/Recall、F1
- 模型部署：ONNX 导出、TensorRT 加速、OpenVINO
- 边缘设备部署：NVIDIA Jetson、树莓派 + Coral TPU

### 动手练习

1. **跑通 YOLOv8 推理**：用预训练模型检测图片/视频/摄像头
2. **在自己的数据上微调**：拍 100 张特定物体照片 → 标注 → 训练 → 评估
3. **模型导出与加速**：pt → ONNX → TensorRT，对比推理速度
4. **实战小项目**：做一个「桌面物品计数」或「人脸口罩检测」

### 验证标准

- [ ] 能解释 mAP@0.5 和 mAP@0.5:0.95 的区别
- [ ] 能独立完成数据集标注 → 训练 → 评估 → 导出的完整流程
- [ ] 理解输入分辨率、batch size、推理速度之间的 tradeoff
- [ ] 能把模型从 Python 环境部署到 ONNX 并成功推理

### 推荐资源

- [Ultralytics YOLO 文档](https://docs.ultralytics.com/)
- [PyTorch 官方教程](https://pytorch.org/tutorials/)
- [Roboflow 数据集管理与标注](https://roboflow.com/)
- [ONNX Runtime 文档](https://onnxruntime.ai/)

---

## Phase 3 — 3D 感知（4-8 周）

**目标**：理解三种主流 3D 感知技术原理，能用点云做基本处理。

### 知识点

#### 双目视觉
- 对极几何：本质矩阵 E、基础矩阵 F
- 立体校正(Bouguet 算法)：让左右图行对齐
- 立体匹配：BM 算法、SGBM 算法
- 视差图 → 深度图 → 点云的转换
- 双目相机标定：单目标定 + 双目标定 + 立体校正
- 精度分析：基线长度、焦距、距离对深度精度的影响

#### 结构光与线激光
- 激光三角测量原理（核心公式推导）
- 线激光传感器标定：光平面标定
- 3D 轮廓扫描：运动方向 + 线激光 → 逐行重建
- 结构光编码：格雷码、相移法
- 与双目的对比：精度、速度、适用场景

#### 点云处理
- 点云数据结构（XYZ / XYZRGB / XYZNormal）
- 滤波：体素降采样、统计滤波、半径滤波
- 特征：法向量估计、FPFH、VFH
- 配准：ICP(迭代最近点)、SAC-IA + ICP
- 分割：RANSAC 平面分割、区域生长、聚类
- 点云深度学习：PointNet/PointNet++、PointPillars

### 动手练习

1. **双目测距**：用两个 webcam 搭一个简易双目系统，测 1-5m 内物体距离
2. **Open3D 点云可视化**：加载 PLY/PCD 文件，做滤波和法向量估计
3. **ICP 配准**：从两个视角扫描同一个物体，用 ICP 对齐
4. **RANSAC 平面提取**：从点云中自动提取桌面、墙面

### 验证标准

- [ ] 能推导激光三角测量的几何公式
- [ ] 能解释视差图到深度图的转换过程
- [ ] 能用 Open3D 完成点云的读取→滤波→配准→分割完整流程
- [ ] 理解为什么双目在无纹理表面（白墙）会失效

### 推荐资源

- 《计算机视觉：算法与应用》（Szeliski）—— 第 11-13 章（多视角几何与立体视觉）
- [Open3D 官方文档](http://www.open3d.org/docs/release/)
- [OpenCV 立体视觉教程](https://docs.opencv.org/master/dd/d53/tutorial_py_depthmap.html)
- 《机器视觉》（张广军）—— 结构光与激光三角测量

---

## Phase 4 — 系统工程（持续学习）

**目标**：把算法从笔记本搬到产线上。

### 知识点

#### 光学与成像（硬件选型）
- 相机选型：分辨率、帧率、传感器尺寸、全局快门 vs 卷帘快门
- 镜头选型：焦距/视场角关系、工作距离、景深计算、镜头接口
- **光源与打光**：同轴光 / 背光 / 环形光 / 低角度光 / 偏振光
- 滤光片：窄带滤光片配合单色光源抑制环境光

#### 精度与标定
- 像素当量(pixel/mm)标定
- 测量系统分析(MSA)与 GR&R
- 手眼标定：Eye-in-Hand vs Eye-to-Hand
- 多传感器联合标定（相机 + 激光雷达 / 相机 + 机械臂）

#### 实时系统
- 多线程采集-处理 pipeline（采集 → 预处理 → 推理 → 后处理 → 输出）
- CPU-GPU 数据搬运优化
- 触发与同步：硬件触发(encoder)、频闪照明、多相机同步
- 延迟分析：端到端延迟的每个环节

#### 工程化
- C++ SDK 封装（Python 原型 → C++ 上线）
- Docker 容器化部署
- 与 PLC/机器人的通信：Modbus TCP、Profinet、Socket
- 日志与监控：异常检测、模型 drift 监控

### 动手练习

1. **搭建一个完整的检测 pipeline**：相机采集 → 预处理 → YOLO 推理 → 结果可视化，计算端到端延迟
2. **GR&R 分析**：对同一个工件重复测量 30 次，计算重复性
3. **手眼标定**：（如果有机械臂）跑通 Eye-to-Hand 标定

### 验证标准

- [ ] 能根据检测需求选相机、镜头、光源
- [ ] 能说出全局快门和卷帘快门的适用场景差异
- [ ] 能完成一个系统的 GR&R 评估
- [ ] 理解触发模式 vs 自由运行模式的差异

### 推荐资源

- [Edmund Optics 光学基础知识](https://www.edmundoptics.com/knowledge-center/)
- 《机器视觉算法与应用》（Steger）—— 第 2 章（光学成像）
- [MVTec HALCON 文档](https://www.mvtec.com/products/halcon/documentation) —— 即使不用 HALCON，文档也是很好的参考

---

## Phase 5 — 领域深入

根据兴趣选择一个方向深入。

### 方向 A：工业缺陷检测

| 主题 | 内容 |
|------|------|
| 表面缺陷检测 | 划痕、脏污、凹坑、毛刺的算法选型（传统 vs DL）|
| 尺寸测量 | 边缘检测 → 亚像素精度 → 拟合直线/圆 → 公差判断 |
| 3D 缺陷检测 | 线激光扫描 → 点云高度图 → 缺陷提取 |
| 行业应用 | 3C 电子 / 锂电池 / 光伏 / 半导体 |
| 商业库 | Halcon / VisionPro —— 理解商业库的能力边界 |

### 方向 B：机器人与具身智能

| 主题 | 内容 |
|------|------|
| ROS/ROS2 | 话题/服务/动作、TF2 坐标变换、rviz 可视化 |
| SLAM | ORB-SLAM3、视觉惯性里程计(VIO) |
| 手眼标定 | Eye-in-Hand、Eye-to-Hand |
| 视觉伺服 | 基于图像的视觉伺服(IBVS) |
| 抓取检测 | GraspNet、AnyGrasp |
| 具身智能 | VLA 模型(RT-2)、Sim-to-Real |

### 方向 C：自动驾驶感知

| 主题 | 内容 |
|------|------|
| 多传感器融合 | Camera + LiDAR + Radar 前融合/后融合 |
| BEV 感知 | BEVFormer、BEVFusion |
| Occupancy Network | 3D 占据栅格预测 |
| 在线高精地图 | MapTR、VectorMapNet |
| 端到端 | UniAD、VAD |

### 推荐资源

- **工业检测**：《机器视觉算法与应用》（Steger），HALCON 官方示例
- **机器人**：[ROS2 官方教程](https://docs.ros.org/en/humble/Tutorials.html)，《Probabilistic Robotics》（Thrun）
- **自动驾驶**：[自动驾驶之心](https://www.zdjszx.com/)（中文社区），Waymo/特斯拉 AI Day 演讲

---

## 学习节奏建议

```
Phase 0  ████░░░░░░░░░░░░░░░░  1 周
Phase 1  ████████░░░░░░░░░░░░  2-4 周
Phase 2  ████████████░░░░░░░░  4-6 周
Phase 3  ████████████████░░░░  4-8 周
Phase 4  ████████████████████  持续（与后续并行）
Phase 5  ████████████████████  选择一个方向深入
```

- **前 3 个月**：完成 Phase 0-2，掌握 2D 视觉 + DL 检测
- **3-6 个月**：进入 Phase 3，理解 3D 感知
- **6 个月后**：Phase 4 系统工程化 + Phase 5 选定方向深入

## 硬件采购建议（Progressive）

| 阶段 | 设备 | 预算 |
|------|------|------|
| Phase 0-1 | 任何 USB 摄像头 + 打印棋盘格 | ~100 元 |
| Phase 2 | NVIDIA GPU（RTX 3060+ 或云 GPU） | 2000-5000 元 |
| Phase 3 | 第二个 webcam（组双目）+ 便宜线激光模组 | ~200 元 |
| Phase 4 | 工业相机 + 镜头 + 光源（如海康机器人入门套件） | 2000-5000 元 |

**建议**：先用手头现有设备跑起来，不要一开始买一堆硬件吃灰。
