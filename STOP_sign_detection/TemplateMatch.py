import numpy as np
from imageio import imread
from skimage import feature
import matplotlib.pyplot as plt
import cv2
from time import sleep, time
import serial

def Normalized_Cross_Correlation(img,tmplt,correlation):
    imgcopy = img.copy()
    maxcoord=np.argwhere(correlation==correlation.max())
    lefttop=(maxcoord[0,1],maxcoord[0,0])
    rightbot=(maxcoord[0,1]+tmplt.shape[1],maxcoord[0,0]+tmplt.shape[0])
    cv2.rectangle(imgcopy,lefttop,rightbot,(255,0,0),1)
    return imgcopy

def main():
    # wait while serial port is not available
    # while (not ser.isOpen()):
        # pass
    cap = cv2.VideoCapture('testvideos/retreat1.mp4')
    # cap.set(3, 640)
    # cap.set(4, 480)
    tmplts = []
    for i in range(1,8):
        tmplts.append(imread('STOPs/STOP'+str(i)+'.jpg')[:,:,0])
    found = '0'
    while(cap.isOpened()):
        
        try:
            sss=time()
            ret, frame = cap.read()

            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            # gray = gray[:150,100:]
            # gray = imbilateral(gray,10,10,10,1) 

            
            for idx, t in enumerate(tmplts):
                correlation = feature.match_template(gray, t)
                if correlation.max() > 0.58:
                    # print(idx+1, tmplts[idx].shape, '           ', correlation.max())
                    found = '1'
                    break
            print(time()-sss)
            if found=='1':
                x=Normalized_Cross_Correlation(gray, t, correlation)
                # tell arduino that STOP sign is detected
                # ser.write(found.encode('ascii'))
                # cv2.imshow('frame',x)
                plt.imshow(correlation)
                plt.show()
                plt.imshow(x)
                plt.show()
            else:
                cv2.imshow('frame',gray)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                print('here')
                break
            found = '0'
        
        except:
            break
    cap.release()
    cv2.destroyAllWindows()

if __name__=='__main__':
    # port = "COM6"
    # baud = 9600
    # ser = serial.Serial(port, baud, timeout=1)
    main()

