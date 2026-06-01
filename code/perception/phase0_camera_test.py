import cv2
import sys

def main():
    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        print("无法打开摄像头，尝试索引 1...")
        cap = cv2.VideoCapture(1)
        if not cap.isOpened():
            print("失败：找不到可用摄像头")
            sys.exit(1)

    print("摄像头已打开，按 q 退出")

    while True:
        ok, frame = cap.read()
        if not ok:
            print("读取帧失败")
            break

        cv2.imshow("Camera Test - Phase 0", frame)
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
