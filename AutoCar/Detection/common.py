import cv2 as cv

#camera_path = "/home/jhy/workstation/object_detection/video/video.avi"
camera_path = '/dev/video0'
#camera_path = 0

IMAGE_SHOW = True

yellow_upper = (30+10, 255, 255)
yellow_lower = (30-10, 30, 30)

def camera_read(camera_path):
    cap = cv.VideoCapture(camera_path)
    if (cap == False):
        print("Video Read Failed!")
    else:
        print("Video Start!")
    return cap

def camera_on(dst, src):
    if IMAGE_SHOW:
        return cv.imshow(dst, src)

def grayscale_converter(frame):
    return cv.cvtColor(frame, cv.COLOR_RGB2GRAY)

def hsv_converter(frame):
    return cv.cvtColor(frame, cv.COLOR_BGR2HSV)

def add_image(frame1, alpha, frame2, beta, gamma, dtype=cv.CV_32F):
    return cv.addWeighted(frame1, alpha, frame2, beta, gamma)
    
def gaussian_blur(frame, kernel_size, sigma_x, sigma_y):
    return cv.GaussianBlur(frame, kernel_size, sigma_x, sigma_y)

