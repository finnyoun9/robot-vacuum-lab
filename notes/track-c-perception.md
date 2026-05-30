# Track C: 感知（传感器逐一打通）

> 开发环境：Mac（Python/OpenCV/NumPy/Open3D）

## 当前进度

| Phase | 内容 | 状态 | 完成日期 |
|-------|------|------|---------|
| C0 | 相机基础 | ✅ 完成 | — |
| C1 | 2D 图像处理 + 相机标定 | ✅ 完成 | — |
| C2 | 线激光三角测量 | ⏳ 下一步 | — |
| C3 | YOLO 目标检测 | ✅ 完成 | — |
| C4 | LDS 激光雷达 + 建图 | ⏳ 未开始 | — |
| C5 | ToF + 红外传感器 | ⏳ 未开始 | — |
| C6 | 传感器融合 | ⏳ 未开始 | — |

## Phase C2 — 线激光三角测量 ⏳

- [ ] 采购 650nm 一字线激光模组 USB（~15-50 元）
- [ ] 激光线中心提取（灰度重心法 → 高斯拟合 → Steger）
- [ ] 光平面标定（激光平面在相机坐标系的方程）
- [ ] 三角测量计算：像素 → 相机坐标 → 实际 3D
- [ ] 运动扫描 → 逐帧拼 3D 点云 → Open3D 可视化

**验证**：扫描手机/杯子，3D 轮廓可见，高度误差 < 1mm（30cm 近场）

## 代码索引

| 文件 | Phase | 说明 |
|------|-------|------|
| `code/perception/phase0_camera_test.py` | C0 | 相机基础 |
| `code/perception/phase1_basics.py` | C1 | 图像处理基础 |
| `code/perception/phase1_contours.py` | C1 | 轮廓检测 |
| `code/perception/phase1_doc_scanner.py` | C1 | 透视变换 |
| `code/perception/phase1_calibration.py` | C1 | 相机标定 |
| `code/perception/phase2_yolo_detect.py` | C3 | YOLO AI 检测 |

## 笔记

<!-- 学习过程中的问题、心得记录在这里 -->
