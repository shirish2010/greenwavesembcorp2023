#import library
from picamera import PiCamera
from time import sleep

camera = PiCamera()

for i in range (0,15):# Repeat the program under it for X-1
    camera.start_preview()#Starts taking pictures for Raspberry Pi Camera
    print("Creating image")
    camera.capture('/home/pi/drive/GrenwaveSentcorpProject/FishClassifierData/NewImages/img%s.jpeg' % i)#Capture picture
    print("Completed creating image")
    camera.stop_preview()#Stop taking pictures
    sleep(3600)#Delay for 1 hour
