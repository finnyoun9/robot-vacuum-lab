"""
Phase 1 小实战 — 文档扫描仪

拿一张纸对着摄像头。把纸放在深色背景上效果最好（比如深色桌面）。
按 s 保存扫描结果，按 q 退出。
"""
import cv2
import numpy as np

cap = cv2.VideoCapture(0)
if not cap.isOpened():
    print("无法打开摄像头")
    exit(1)

print("把纸放在深色背景上，让纸和背景有清晰对比")
print("按 s 保存扫描结果，按 q 退出")

while True:
    ok, frame = cap.read()
    if not ok:
        break

    h, w = frame.shape[:2]
    frame_area = h * w
    orig = frame.copy()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (5, 5), 0)

    # 用自适应阈值代替 Canny——白色纸在深色背景上更明显
    thresh = cv2.adaptiveThreshold(blur, 255,
                                    cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
                                    cv2.THRESH_BINARY, 11, 2)

    # 找轮廓
    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contours = sorted(contours, key=cv2.contourArea, reverse=True)

    doc_contour = None
    for c in contours:
        area = cv2.contourArea(c)
        peri = cv2.arcLength(c, True)
        approx = cv2.approxPolyDP(c, 0.02 * peri, True)

        # 面积比例：纸应该占画面的 5% ~ 70%
        area_ratio = area / frame_area
        if not (0.05 < area_ratio < 0.70):
            continue

        if len(approx) == 4:
            doc_contour = approx
            break

    # 如果没找到四边形，放宽条件试一次：取面积最大的四边形
    if doc_contour is None:
        for c in contours:
            peri = cv2.arcLength(c, True)
            approx = cv2.approxPolyDP(c, 0.02 * peri, True)
            if len(approx) == 4:
                doc_contour = approx
                break

    if doc_contour is not None:
        cv2.drawContours(frame, [doc_contour], -1, (0, 255, 0), 3)

        pts = doc_contour.reshape(4, 2)
        s = pts.sum(axis=1)
        tl = pts[np.argmin(s)]
        br = pts[np.argmax(s)]
        diff = np.diff(pts, axis=1)
        tr = pts[np.argmin(diff)]
        bl = pts[np.argmax(diff)]

        w_out = max(int(np.linalg.norm(br - bl)), int(np.linalg.norm(tr - tl)))
        h_out = max(int(np.linalg.norm(tr - br)), int(np.linalg.norm(bl - tl)))

        dst = np.array([[0, 0], [w_out - 1, 0], [w_out - 1, h_out - 1], [0, h_out - 1]], dtype=np.float32)
        M = cv2.getPerspectiveTransform(np.float32([tl, tr, br, bl]), dst)
        warped = cv2.warpPerspective(orig, M, (w_out, h_out))

        cv2.imshow("Scanned Document", warped)
        cv2.putText(frame, "Document found!", (20, 40),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2)
    else:
        # 同时显示二值化结果，帮助理解为什么没检测到
        cv2.imshow("Scanned Document", cv2.cvtColor(thresh, cv2.COLOR_GRAY2BGR))
        cv2.putText(frame, "No document - put paper on dark surface", (20, 40),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

    cv2.imshow("Document Scanner", frame)

    key = cv2.waitKey(1) & 0xFF
    if key == ord("q"):
        break
    elif key == ord("s") and doc_contour is not None:
        cv2.imwrite("code/scan_output.jpg", warped)
        print("已保存: code/scan_output.jpg")

cap.release()
cv2.destroyAllWindows()
