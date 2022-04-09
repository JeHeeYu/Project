import cv2 as cv
import time

from common import *
from detection import *
#from server import *

class AutoCar(object):
    
    def __init__(self):
        print("Create AutoCar Object!")
        
        self.detection = DetectionOfLine()
    
    def detection_lanes(self, frame):
        result= self.detection.self_detection(frame)

        return result
        
    def start(self):
        cap = camera_read(camera_path)
        while cap.isOpened():
        #while True:
            time.sleep(0.1)
            ret, cam = cap.read()
            if ret:
                cam = cv.resize(cam, (640, 360))
                result_image = self.detection_lanes(cam)
                roi = roi_detection(cam)
                #gen_frames(cam)
                camera_on('cam', result_image)
                camera_on('roi', roi)
            
                if cv.waitKey(1) & 0xFF == 27:
                    break
        #cap.released()
        cv.destroyAllWindows()

            
    
    
    
