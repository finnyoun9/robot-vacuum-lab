"""
Phase 1 — 图像处理基础练习

运行：python code/phase1_basics.py
每按一次键切换到下一题，按 q 跳过当前题目
"""
import cv2
import numpy as np

cap = cv2.VideoCapture(0)
if not cap.isOpened():
    print("无法打开摄像头")
    exit(1)

exercises = [
    ("原始画面", lambda f: f),
    ("灰度图", lambda f: cv2.cvtColor(f, cv2.COLOR_BGR2GRAY)),
    ("高斯模糊", lambda f: cv2.GaussianBlur(f, (15, 15), 0)),
    ("Canny 边缘检测", lambda f: cv2.Canny(f, 80, 160)),
    ("HSV 色彩空间", lambda f: cv2.cvtColor(f, cv2.COLOR_BGR2HSV)),
    ("自适应阈值", lambda f: cv2.adaptiveThreshold(
        cv2.cvtColor(f, cv2.COLOR_BGR2GRAY), 255,
        cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 2)),
    ("颜色叠加（红色遮罩）", lambda f: cv2.addWeighted(f, 0.5,
        np.full_like(f, (0, 0, 255)), 0.5, 0)),
    ("水平翻转", lambda f: cv2.flip(f, 1)),
]

idx = 0
while True:
    ok, frame = cap.read()
    if not ok:
        break

    name, fn = exercises[idx]
    result = fn(frame)

    # 灰度图转回 BGR 以便显示
    if len(result.shape) == 2:
        result = cv2.cvtColor(result, cv2.COLOR_GRAY2BGR)

    # 标题
    cv2.putText(result, f"[{idx+1}/{len(exercises)}] {name}", (20, 40),
                cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2)

    cv2.imshow("Phase 1 - Image Processing Basics", result)
    key = cv2.waitKey(1) & 0xFF

    if key == ord("q"):
        break
    elif key != 255:  # 任意键切换下一题
        idx = (idx + 1) % len(exercises)

cap.release()
cv2.destroyAllWindows()
