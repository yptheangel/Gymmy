import cv2
import numpy as np

#dumbbell_cascade = cv2.CascadeClassifier('dumbbell_cascade.xml')
#dumbbell_cascade = cv2.CascadeClassifier('dumbbellLv30.xml')
dumbbell_cascade = cv2.CascadeClassifier('db2020lv20cascade.xml')

#cap = cv2.VideoCapture(0)
cap = cv2.VideoCapture('output.avi')

counter = 0
flag0 = 0
flag1 = 0
complete =0

while 1:
	ret, img = cap.read()
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	font = cv2.FONT_HERSHEY_SIMPLEX
   #for koala settings. dumbbell = dumbbell_cascade.detectMultiScale(gray, scaleFactor=1.5, minNeighbors=5 ,minSize=(100,100))
#	dumbbell = dumbbell_cascade.detectMultiScale(gray, scaleFactor=1.2, minNeighbors=5 ,minSize=(90,90))
	dumbbell = dumbbell_cascade.detectMultiScale(gray, scaleFactor=1.2, minNeighbors=4,minSize=(90,90))

	cv2.line(img,(0,240),(640,240),(0,255,255),thickness=3)

	for (x,y,w,h) in dumbbell:
#	font = cv2.FONT_HERSHEY_SIMPLEX
#  	cv2.putText(img,'Koala',(x-w, y-h), font, 0.5, (0,255,255), 2, cv2.LINE_AA)
		cv2.rectangle(img,(x,y),(x+w,y+h),(255,255,0),2)

		if y > 240:
        		flag0 = 1
        
		if y < 240:
        		flag1 = 1 
        	
#		if (flag0 == 1) and (flag1 == 1):
#			counter+=1
#			flag0 = 0
#			flag1 = 0
	        if (flag0 == 1) and (flag1 == 1):
        	   	complete+=1
			flag0 = 0
			flag1= 0

		if (complete == 2):
       			counter+=1
			complete = 0
			#flag0 = 0
			#flag1 = 0
			print 'Counter= %d' %counter	

#    cv2.putText(img,'Counter = ',(15,25),font,1.0,(0,0,0),3)
 	
	#print 'Counter= %d' %counter	
	cv2.imshow('Gray',gray)
	cv2.imshow('Img',img)
	k = cv2.waitKey(30) & 0xff
	if k == 27:
		cv2.imwrite('test.jpg',img)
        	break
	elif k == 32:
		counter = 0

cap.release()
cv2.destroyAllWindows()
