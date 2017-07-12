import cv2
import timeit
import time

cap = cv2.VideoCapture(0)

while True: 
	ret , frame = cap.read()
	cv2.imshow('frame',frame)
	cv2.imwrite("testvideo.mp4",frame)
	if cv2.waitKey(1) & 0xFF == ord('q'):
	#	i=1
	#	for i in range(1,10):
	#		ret, frame1 = cap.read()
	#		cv2.imwrite("capture"+str(i)+".jpg",frame1)
	#		print "Photo %d printed!" %i
	#		time.sleep(1)	
	#		i+=1
		break


cap.release
cv2.destroyAllWindows()








