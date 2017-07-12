#Author : Choo, Wilson
#Last Edited : 14 June 2017

import cv2
import os
from shutil import copyfile
import numpy as np

max_num = 1201
img_folder_in = "neg_test/"
img_folder_out = "neg_test/"
perfect_img = "pos_test/99.jpg"

def convert_images():
	
	pic_num = 1
	add_num = 1202
	
	for pic_num in range(1,max_num+1):  
		try:
			img = cv2.imread(img_folder_in+str(pic_num)+".jpg", cv2.IMREAD_GRAYSCALE)
			resized_image = cv2.resize(img, (100,100))	
			cv2.imwrite(img_folder_out+str(add_num)+".jpg",resized_image)
			pic_num +=1
			add_num +=1
			print "%d.jpg was processed!" %pic_num 
		
		except Exception as e:
		#	os.remove(img_folder_in+str(pic_num)+".jpg")
		#	copyfile(perfect_img,img_folder_in+str(pic_num)+".jpg")
			print(str(e))
			
def find_uglies():
	for file_type in ['neg_test']:
		for img in os.listdir(file_type):
			for ugly in os.listdir('uglies'):
				try:
					current_image_path = str(file_type)+'/'+str(img)
                    			ugly = cv2.imread('uglies/'+str(ugly))
                    			question = cv2.imread(current_image_path)
                    			if ugly.shape == question.shape and not(np.bitwise_xor(ugly,question).any()):
                        			print('Deleting ugly picture! ')
                        			print(current_image_path)
                        			os.remove(current_image_path)
						copyfile(perfect_img,current_image_path)
                		except Exception as e:
                    			print(str(e))

def create_pos_n_neg():
	for file_type in ['neg_test']:
		for img in os.listdir(file_type):
			if file_type == 'pos_test':
				line = file_type+'/'+img+' 1 0 0 50 50\n'
				with open('info.dat','a') as f:
					f.write(line)

			elif file_type == 'neg_test':
				line = file_type+'/'+img+'\n'
				with open('bg.txt','a') as f:
					f.write(line)

def make_baby():

        pic_num = 919

        for pic_num in range(919,1800):
                try:
			copyfile(perfect_img,img_folder+str(pic_num)+".jpg")
			pic_num+1
                except Exception as e:
                        print(str(e))
			
#make_baby()				
#convert_images()
#find_uglies()
create_pos_n_neg()
