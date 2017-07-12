import cv2

cap = cv2.VideoCapture(0)
fgbg =cv2.createBackgroundSubtractorMOG2()

while (1):
	ret, frame = cap.read()
	fgmask = fgbg.apply(frame)
	edges = cv2.Canny(fgmask,100,200)

	cv2.imshow('Original', frame)
	cv2.imshow('MOG2', fgmask)
	cv2.imshow('Output', edges)

	k = cv2.waitKey(30) & 0xff
	if k == 27:
		break

cap.release()
cv2.destroyAllWindows()
