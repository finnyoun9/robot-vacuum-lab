"""
Phase 1 — 轮廓检测与物体定位

步骤：灰度 → 高斯模糊 → 阈值二值化 → 找轮廓 → 画外接矩形
找个对比度高的物体（硬币、笔、杯子）放摄像头前试试
"""
import cv2

cap = cv2.VideoCapture(0)
if not cap.isOpened():
    print("无法打开摄像头")
    exit(1)

mode_names = ["原始 + 轮廓框", "二值化（阈值分割）", "轮廓填充"]
mode = 0

print("按 1/2/3 切换显示模式，按 q 退出")

while True:
    ok, frame = cap.read()
    if not ok:
        break

    # ----- 预处理流水线 -----
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)      # 灰度
    blur = cv2.GaussianBlur(gray, (7, 7), 0)             # 去噪
    _, thresh = cv2.threshold(blur, 127, 255, cv2.THRESH_BINARY_INV)  # 暗色物体变白

    # ----- 找轮廓 -----
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # 过滤太小的噪点（面积 < 500 像素的忽略）
    contours = [c for c in contours if cv2.contourArea(c) > 500]

    # ----- 显示 -----
    if mode == 0:
        display = frame.copy()
        for c in contours:
            x, y, w, h = cv2.boundingRect(c)
            area = cv2.contourArea(c)
            cv2.rectangle(display, (x, y), (x + w, y + h), (0, 255, 0), 2)
            cv2.putText(display, f"{area:.0f}px", (x, y - 5),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 1)
        cv2.putText(display, f"找到 {len(contours)} 个物体", (20, 40),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2)

    elif mode == 1:
        display = cv2.cvtColor(thresh, cv2.COLOR_GRAY2BGR)
        cv2.putText(display, "二值化结果（暗像素 → 白色）", (20, 40),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)

    elif mode == 2:
        display = frame.copy()
        cv2.drawContours(display, contours, -1, (0, 255, 0), -1)  # 填充轮廓
        cv2.putText(display, "轮廓填充", (20, 40),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)

    cv2.imshow("Phase 1 - Contour Detection", display)
    key = cv2.waitKey(1) & 0xFF
    if key == ord("q"):
        break
    elif key == ord("1"):
        mode = 0
    elif key == ord("2"):
        mode = 1
    elif key == ord("3"):
        mode = 2

cap.release()
cv2.destroyAllWindows()
