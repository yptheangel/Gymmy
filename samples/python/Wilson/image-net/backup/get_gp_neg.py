import urllib
import urllib2
import cv2
import os
import sys
reload(sys)
sys.setdefaultencoding("utf-8")

def store_raw_images():
	neg_images_link = 'http://image-net.org/api/text/imagenet.synset.geturls?wnid=n07942152'
	proxy_support = urllib2.ProxyHandler({'http':'proxy.png.intel.com:911'})
	opener = urllib2.build_opener(proxy_support)
	urllib2.install_opener(opener)
	neg_images_urls = urllib2.urlopen(neg_images_link).read().decode()

	if not os.path.exists('neg'):
		os.makedirs('neg')

	pic_num = 1 

	for i in neg_images_urls.split('\n'):
		try:
			print(i)
			with open("neg/"+str(pic_num)+'.jpg','wb') as f:
				f.write(urllib2.urlopen(i).read())
				f.close()
				print (pic_num)

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
