import serial
import cv2 as cv
import time
import numpy as np

def main():
    cap = cv.VideoCapture('./bad_apple.mp4')
    ser = serial.Serial('/dev/ttyACM0', 250000, timeout=.1)
    fps = cap.get(cv.CAP_PROP_FPS)
    delta = 1 / fps
    previous = time.perf_counter()
    print(fps)
    try:
        while cap.isOpened():
            ret, frame = cap.read()
            if not ret:
                break
            gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
            small = cv.resize(gray, (8, 8))

            ser.write(small.tobytes())

            cv.imshow('frame', gray)

            current = time.perf_counter()
            expected = previous + delta
            previous = expected
            if cv.waitKey(max(round((expected - current) * 1000), 1)) & 0xFF == ord('q'):
                break
    except KeyboardInterrupt: pass
    finally:
        ser.close()
        cap.release()
        cv.destroyAllWindows()

if __name__ == '__main__':
    main()
