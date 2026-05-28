# 学习资源汇总

## 书籍

### 核心教材

| 书名 | 作者 | 适合阶段 | 说明 |
|------|------|---------|------|
| 《学习 OpenCV 3》 | Kaehler & Bradski | Phase 1 | OpenCV 百科全书，当工具书查 |
| 《计算机视觉：算法与应用》 | Szeliski | Phase 1-3 | 领域圣经，覆盖面广，数学推导清晰 |
| 《机器视觉算法与应用》 | Steger | Phase 4 | 工业机器视觉最佳参考，偏工程实践 |
| 《机器视觉》 | 张广军 | Phase 3 | 结构光、线激光、双目，中文教材里最扎实的 |

### 深度学习相关

| 书名 | 作者 | 适合阶段 | 说明 |
|------|------|---------|------|
| 《动手学深度学习》 | 李沐等 | Phase 2 | 中文，有代码，推荐 |
| 《深度学习》(花书) | Goodfellow | Phase 2+ | 理论经典，需要一定数学基础 |

### 专项

| 书名 | 作者 | 适合阶段 | 说明 |
|------|------|---------|------|
| 《Probabilistic Robotics》 | Thrun | Phase 5-B | SLAM 和机器人状态估计圣经 |
| 《Multiple View Geometry》 | Hartley & Zisserman | Phase 3 | 多视角几何，难度较高，作为参考书 |
| 《机器人学中的状态估计》 | Barfoot | Phase 5-B | 中文译本，适合做 SLAM 的入门理论 |

## 在线课程

| 课程 | 平台 | 适合阶段 |
|------|------|---------|
| [CS231n: Deep Learning for Computer Vision](http://cs231n.stanford.edu/) | Stanford | Phase 2 |
| [First Principles of Computer Vision](https://www.youtube.com/@firstprinciplesofcomputerv3258) | YouTube | Phase 1 |
| [OpenCV Python Tutorials](https://docs.opencv.org/master/d6/d00/tutorial_py_root.html) | 官方文档 | Phase 1 |
| [ROS2 Tutorials](https://docs.ros.org/en/humble/Tutorials.html) | 官方文档 | Phase 5-B |

## 关键工具与库

| 工具 | 用途 | 阶段 |
|------|------|------|
| OpenCV | 图像处理、相机标定、双目立体 | Phase 1, 3 |
| NumPy | 数组计算基础 | Phase 0+ |
| PyTorch | 深度学习框架 | Phase 2 |
| Ultralytics | YOLO 训练与推理（最简单入口） | Phase 2 |
| ONNX Runtime | 模型跨平台部署 | Phase 2 |
| TensorRT | NVIDIA GPU 推理加速 | Phase 2 |
| Open3D | 点云处理与可视化 | Phase 3 |
| PCL (Point Cloud Library) | C++ 点云库 | Phase 3 |
| Albumentations | 图像数据增强 | Phase 2 |
| Label Studio / CVAT | 图像标注工具 | Phase 2 |
| HALCON | 商业机器视觉库（工业标准） | Phase 4 |
| Docker | 容器化部署 | Phase 4 |
| ROS2 | 机器人系统框架 | Phase 5-B |

## 数据集

| 数据集 | 内容 | 用途 |
|--------|------|------|
| [COCO](https://cocodataset.org/) | 80 类目标检测/分割 | 通用检测基准 |
| [ImageNet](https://www.image-net.org/) | 1000 类图像分类 | 分类基准 |
| [KITTI](https://www.cvlibs.net/datasets/kitti/) | 自动驾驶多传感器 | 3D 检测/双目/SLAM |
| [nuScenes](https://www.nuscenes.org/) | 自动驾驶多传感器 | BEV 感知 |
| [MVTec AD](https://www.mvtec.com/company/research/datasets/mvtec-ad) | 工业异常检测 | 缺陷检测基准 |

## 中文社区与资讯

| 资源 | 说明 |
|------|------|
| [自动驾驶之心](https://www.zdjszx.com/) | 自动驾驶感知方向中文社区 |
| [机器之心](https://www.jiqizhixin.com/) | AI 综合资讯 |
| [OpenCV 学堂](https://mp.weixin.qq.com/) | 公众号，工业视觉实战文章 |
| 知乎「计算机视觉」话题 | 高质量讨论和论文解读 |
| B 站「3Blue1Brown 神经网络」 | 可视化理解神经网络 |

## 硬件供应商（国内）

| 品牌 | 产品 |
|------|------|
| 海康机器人 | 工业相机、镜头、视觉控制器 |
| 大恒图像 | 工业相机、镜头 |
| 奥普特(OPT) | 机器视觉光源 |
| Basler | 工业相机（德国品牌，国内有代理） |
| 英特尔 RealSense | 深度相机(D435 等) |
| 思岚(SLAMTEC) | 激光雷达(LiDAR) |

## 云 GPU 平台

| 平台 | 说明 |
|------|------|
| [AutoDL](https://www.autodl.com/) | 国内性价比高，按小时租 |
| [恒源云](https://www.gpushare.com/) | 国内 GPU 租用 |
| Google Colab | 免费 T4 GPU，适合轻量实验 |
| Lambda Labs / RunPod | 海外选择 |
