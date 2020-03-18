import numpy as np
import cv2

cap = cv2.VideoCapture(0)
flag = 1

while cap.isOpened():
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Our operations on the frame come here
    if cv2.waitKey(20) & 0xFF == ord('1'):
        flag = 1
    elif cv2.waitKey(20) & 0xFF == ord('2'):
        flag = 2
    elif cv2.waitKey(20) & 0xFF == ord('3'):
        flag = 3

    if flag == 1:
        cv2.imshow('frame', frame)
    if flag == 2:
        frame = cv2.flip(frame, 0)
        cv2.imshow('frame', frame)
    if flag == 3:
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        cv2.imshow('frame', gray)

    # Display the resulting frame
    if cv2.waitKey(20) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
