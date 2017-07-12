import cv2
import numpy as np

dumbbell_cascade = cv2.CascadeClassifier('dumbbell_cascade.xml')
cap = cv2.VideoCapture(0)

while 1:
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
 
   # dumbbell = dumbbell_cascade.detectMultiScale(gray,50,50)
   #for koala settings. dumbbell = dumbbell_cascade.detectMultiScale(gray, scaleFactor=1.5, minNeighbors=5 ,minSize=(100,100))
    dumbbell = dumbbell_cascade.detectMultiScale(gray, scaleFactor=1.3, minNeighbors=5 ,minSize=(60,60))
  
    for (x,y,w,h) in dumbbell:
# 	font = cv2.FONT_HERSHEY_SIMPLEX
#  	cv2.putText(img,'Koala',(x-w, y-h), font, 0.5, (0,255,255), 2, cv2.LINE_AA)
	cv2.rectangle(img,(x,y),(x+w,y+h),(255,255,0),2)
	
    cv2.imshow('Gray',gray)
    cv2.imshow('Img',img)
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cap.release()
cv2.destroyAllWindows()
