#import urllib.request
import urllib
import urllib2
#import cv2
#import numpy as np
import os
#from stopit import SignalingTimeout as Timeout

def store_raw_images():
#	neg_images_link = 'http://image-net.org/api/text/imagenet.synset.geturls?wnid=n07942152'
#	neg_images_link = 'http://image-net.org/api/text/imagenet.synset.geturls?wnid=n03255030'
#	proxy_support = urllib2.ProxyHandler({'http':'proxy.png.intel.com:911'})
#	opener = urllib2.build_opener(proxy_support)
#	urllib2.install_opener(opener)
	neg_images_urls = urllib2.urlopen(neg_images_link).read().decode()

	if not os.path.exists('neg'):
		os.makedirs('neg')

	pic_num = 1 

	for i in neg_images_urls.split('\n'):
		try:
			print(i)
			urllib.urlretrieve(i,"neg/"+str(pic_num)+'.jpg')
			
		#		with open("neg/"+str(pic_num)+'.jpg','wb') as f:
		#			f.write(urllib2.urlopen(i).read())
		#			f.close()
			print (pic_num)

#			img = cv2.imread("neg/"+str(pic_num)+'.jpg', cv2.IMREAD_GRAYSCALE)
#			resized_image = cv2.resize(img, (100,100))	
#			cv2.imwrite("neg/"+str(pic_num)+'.jpg'.resized_image)
			pic_num +=1
		
		except ImportError as e:
			print(str(ie))

#		except urllib2.URLError as e:
#			print(str(e))

#		except urllib2.HTTPError as he:
#			print(str(he))
	
#		except urllib2.URLError as ue:
#			print(str(ue))

		else:
			print "next!"
store_raw_images()
