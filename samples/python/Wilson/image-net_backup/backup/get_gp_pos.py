import urllib
import urllib2
import cv2
#import numpy as np
import os
import sys
reload(sys)
sys.setdefaultencoding("utf-8")

def store_raw_images():
#	neg_images_link = 'http://image-net.org/api/text/imagenet.synset.geturls?wnid=n07942152'
	pos_images_link = 'http://image-net.org/api/text/imagenet.synset.geturls?wnid=n03255030'
	proxy_support = urllib2.ProxyHandler({'http':'proxy.png.intel.com:911'})
	opener = urllib2.build_opener(proxy_support)
	urllib2.install_opener(opener)
	pos_images_urls = urllib2.urlopen(pos_images_link).read().decode()

	if not os.path.exists('pos'):
		os.makedirs('pos')

	pic_num = 1 

	for i in pos_images_urls.split('\n'):
		try:
			print(i)
			#urllib.urlretrieve(i,"neg/"+str(pic_num)+'.jpg')
			
			with open("pos/"+str(pic_num)+'.jpg','wb') as f:
				f.write(urllib2.urlopen(i).read())
				f.close()
				print (pic_num)

#			img = cv2.imread("pos/"+str(pic_num)+'.jpg', cv2.IMREAD_GRAYSCALE)
#			resized_image = cv2.resize(img, (50,50))	
#			cv2.imwrite("pos/"+str(pic_num)+'.jpg',resized_image)
			pic_num +=1

		except urllib2.URLError as e:
			print(str(e))
		except urllib2.HTTPError as he:
			print(str(he))
		except urllib2.URLError as ue:
			print(str(ue))
		else:
			print "next!"
store_raw_images()
