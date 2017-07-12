import cv2



#img = cv2.imread("dumbellx.jpg",cv2.IMREAD_GRAYSCALE)
#img = cv2.imread("57.jpg",cv2.IMREAD_GRAYSCALE)
img = cv2.imread("image1.png",cv2.IMREAD_GRAYSCALE)
resized_img = cv2.resize(img, (50,50))
#cv2.imwrite("dumbbell5050.jpg",resized_img)
cv2.imwrite("dumbbell5050.png",resized_img)


