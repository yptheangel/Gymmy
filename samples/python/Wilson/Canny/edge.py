import cv2

cap = cv2.VideoCapture(0)

while True:
	ret, frame = cap.read()
	edges = cv2.Canny(frame,100,200)
	cv2.imshow('Frame',frame)
	cv2.imshow('Edges',edges)
	k = cv2.waitKey(30) & 0xff
	if k == 27:
		break

cap.release()
cv2.destroyAllWindows()


