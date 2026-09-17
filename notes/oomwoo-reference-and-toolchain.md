# OOMWOO 对照与扫地机工具链（2026-08-25）

参考项目：[makerspet/oomwoo](https://github.com/makerspet/oomwoo)。其目标是 3D 打印、树莓派、STM32、ROS 2、2D LiDAR 的本地化开源扫地机；目前仍为 `early development`，机械、PCB、固件与装配文档未齐，适合作为模块化设计参考，而非直接照抄的整机方案。

## 与本项目不谋而合的部分

| 层 | 早期扫地机计划 | 现有 `mecanum-robot` | OOMWOO | 结论 |
| --- | --- | --- | --- | --- |
| 上位机 | Pi + ROS 2、SLAM、Nav2、行为树 | Pi 5 + ROS 2 Jazzy + `ros2_control` + Nav2/SLAM 骨架 | CM4/CM5 + ROS 2/Nav2 | 软件架构方向正确，`mecanum-robot` 已明显领先早期计划。 |
| 下位机 | STM32 管 PID、编码器、IMU、悬崖/碰撞/电池 | FreeRTOS、UART/CRC、SIL、PID、编码器 | STM32G473 + 实时安全核心 | 继续沿用现有协议与安全分层。 |
| 感知 | 2D LiDAR、ToF、相机/线激光 | LiDAR、ToF、相机标定、YOLO、线激光实验 | 2D LiDAR 为主，视觉为后续增强 | MVP 先以 LiDAR + 编码器 + IMU 完成导航；视觉不应阻塞清扫车。 |
| 机械 | 差速底盘、供电、安装布线 | 已有可验证的软件/电机控制底座 | 3D 打印圆形底盘、复用吸尘器零件 | 这是当前主要缺口，也是 OOMWOO 最值得参考处。 |

## 关键取舍

不要把麦克纳姆底盘直接改成扫地机。扫地机 V0 应是圆形**差速**平台：更省空间、里程计/导航模型更简单，也更适合主刷、风道、尘盒和前保险杠的布局。

复用 `mecanum-robot` 的 Pi 5、STM32 FreeRTOS 模式、UART/CRC 协议、SIL 测试、传感器 ROS 2 接入、Docker/Jazzy 环境；新建 `vacuum` 的差速运动学、URDF、底盘/风道、清扫执行器和电源安全层。不要复用四麦克纳姆轮运动学、四轮底盘几何或其电源假设。

## 最小工具链

| 范围 | 首选 | 用途 |
| --- | --- | --- |
| 机械 CAD | [Onshape](https://www.onshape.com/en/products/cad) | 参数化零件与装配；从圆形底盘、轮组、LiDAR、主刷、尘盒、PCB 的基准面和接口尺寸开始。 |
| PCB/线束 | [KiCad](https://www.kicad.org/discover/) | 原理图、PCB、线束/连接器 pinout、3D PCB 装配校验；先做接口与电源板，不急于自研所有驱动板。 |
| MCU | STM32CubeMX + HAL/FreeRTOS + arm-none-eabi GCC | 以现有 `mecanum-robot` 的协议、SIL、看门狗和安全任务为基线，新增差速电机、悬崖、保险杠、风机/刷子控制。 |
| ROS 2/仿真 | ROS 2 Jazzy + RViz2 + Nav2 + `slam_toolbox`；Gazebo Harmonic | 先在差速 URDF 中验证 TF、传感器位姿、速度限制和导航；Harmonic 支持至 2029。 |
| 制造 | FDM 3D printer 或按件打样服务；OrcaSlicer/PrusaSlicer | PETG 先做底盘与夹具，PETG/ASA 做受热/受力件；用 M3 热熔螺母实现可反复拆装。 |
| 版本与验证 | Git + Git LFS（STEP/STL/PCB 输出）+ `colcon`/CTest + 现有 SIL | CAD 源文件、BOM、接线图和固件版本必须对应；每次机械改动记录尺寸与实测结果。 |

## 需要补齐的实体工具

- 数显卡尺、螺纹规、M3/M4 紧固件盒、热熔螺母 + 恒温烙铁、压接钳（JST/杜邦不作为整机长期方案）。
- 限流台式电源、万用表；电机/风机与电源调试阶段加入逻辑分析仪和示波器。
- 使用带 BMS 的成品电池包和独立的 CC/CV 充电模块；V0 不做自动回充与自制锂电充电/BMS。回充是后期单独的安全子项目。
- 清扫系统优先复用成熟的轮组、滚刷、风机、LiDAR、尘盒滤网等零件，3D 打印负责承力骨架、安装座、风道原型和外壳；不要一开始自研高转速风机、滚刷或电池包。

## 推荐实施顺序

1. **V0 导航底盘**：差速轮组 + Pi/STM32 + LiDAR + 保险杠，完成建图、导航和 10 m² 房间巡航；无吸尘、无回充。
2. **V1 干扫**：复用主刷、风机和滤网，验证风道、尘盒、续航、噪声和毛发缠绕；把吸尘系统与导航解耦为独立 MCU 执行器。
3. **V2 可靠性**：悬崖、轮悬空、堵转、过流、低电压、通信超时、急停和看门狗；记录每一项故障注入测试。
4. **V3 回充/拖地**：只在 V2 稳定后做。回充触点、对位、充电状态机和防火安全必须独立验收。

## 首个 CAD 交付物

不要从外观开始。第一份建模应为 `vacuum-v0-layout` 总装：外径、轮距、重心、LiDAR 视场、主刷/风机/尘盒的包络、PCB 与电池位置、前保险杠行程、螺柱与线束走向。输出装配 STEP、关键件 STL、接口尺寸图和 BOM；用一版低填充样件验证装配，再迭代强度与风道。

## 下一步

以 `mecanum-robot` 的差速变体作为软件/控制起点，并在新仓库或 `robot-vacuum-lab` 下建立 `cad/`、`hardware/`、`firmware/`、`ros2_ws/`、`bom/` 五个边界清晰的目录。第一个可验收目标是“无清扫模块的差速 LiDAR 车在单个房间自主巡航 30 分钟”，而不是先做一台外观完整的扫地机。
