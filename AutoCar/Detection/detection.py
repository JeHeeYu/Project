import cv2 as cv
from cv2 import line
import numpy as np
import math
import time


from common import *
from serialcomm import *

class DetectionOfLine(object):
    def __init__(self):
        print("Create DetectionOfLine Object!")
        
    def self_detection(self, frame):
        result, left, right = detection_lanes(frame)
        direction_control(left, right)
        return result
        

def canny_edge_detection(image):
    input_image = grayscale_converter(image)
    image_blur = cv.GaussianBlur(input_image, (5, 5), 0)
    canny_image = cv.Canny(image_blur, 50, 150)
    return canny_image

def yellow_mask(frame):
    hsv = hsv_converter(frame)
    lower = (20, 20, 100) 
    upper = (40, 255, 255)
    frame_mask = cv.inRange(hsv, lower, upper)
    result = cv.bitwise_and(frame, frame, mask = frame_mask)
    return result

def roi_detection(image):
    image_mask = np.zeros_like(image)
    image_height = image.shape[0]
    image_width = image.shape[1]
    
    points = np.array([[(0, image_height), (0, 250), (image_width, 250), (640, image_height)]])
    cv.fillPoly(image_mask, points, 255)
    
    line_image = cv.bitwise_and(image, image_mask)
    return line_image

def hough_line(frame):
    rho = 1
    theta = np.pi / 180
    threshold = 20
    minLineLength = 10
    maxLineGap = 20
    lines = cv.HoughLinesP(frame, rho, theta, threshold, minLineLength, maxLineGap)
        
    return lines

def steer_angle(lanes):
    right_line = np.empty((0, 5), int)
    left_line = np.empty((0, 5), int)
    if lanes is not None:
        line_arr2 = np.empty((len(lanes), 5), int)

        for i in range(0, len(lanes)):
            temp = 0
            l = lanes[i][0]
            line_arr2[i] = np.append(lanes[i], np.array((np.arctan2(l[1] - l[3], l[0] - l[2]) * 180) / np.pi))

            if line_arr2[i][1] > line_arr2[i][3]:
                temp = line_arr2[i][0], line_arr2[i][1]
                line_arr2[i][0], line_arr2[i][1] = line_arr2[i][2], line_arr2[i][3]
                line_arr2[i][2], line_arr2[i][3] = temp

                
            if line_arr2[i][0] < 320 and (abs(line_arr2[i][4]) < 170 and abs(line_arr2[i][4]) > 95):
                left_line = np.append(left_line, line_arr2[i])
            elif line_arr2[i][0] > 320 and (abs(line_arr2[i][4]) < 170 and abs(line_arr2[i][4]) > 95):
                right_line = np.append(right_line, line_arr2[i])

    left_line = left_line.reshape(int(len(left_line) / 5), 5)
    right_line = right_line.reshape(int(len(right_line) / 5), 5)

    return left_line, right_line

def draw_lanes(frame, left_line, right_line):
    copy_image = np.copy(frame)

    try:
        left_line = left_line[left_line[:, 0].argsort()[-1]]
        left_degree = left_line[4]
        cv.line(copy_image, (left_line[0], left_line[1]), (left_line[2], left_line[3]), (255, 0, 0), 10, cv.LINE_AA)
    except:
        left_degree = 0
    try:
        right_line = right_line[right_line[:, 0].argsort()[0]]
        right_degree = right_line[4]
        cv.line(copy_image, (right_line[0], right_line[1]), (right_line[2], right_line[3]), (255, 0, 0), 10, cv.LINE_AA)
    except:
        right_degree = 0    

    result_image = cv.addWeighted(frame, 1, copy_image, 1, 0)

    return result_image, left_degree, right_degree

def detection_lanes(frame):
    frame_yellow = yellow_mask(frame)
    canny = canny_edge_detection(frame_yellow)
    roi_image = roi_detection(canny)
    
    lines = hough_line(roi_image)
    left_line, right_line = steer_angle(lines)

    image, left, right = draw_lanes(frame, left_line, right_line)

    return image, left, right

def direction_control(left_line, right_line):
    serial_object = get_serial()
    if abs(left_line) == 0 and abs(right_line) == 0:
        data_send(serial_object, STOP)
        print("stop")
    elif abs(left_line) <= 155 or abs(right_line) <= 155:
        if (abs(left_line) <= 135 and abs(left_line) >= 110) or (abs(right_line) <= 135 and abs(right_line) >= 110):
            data_send(serial_object, STRAGIHT)
            print('go')
            print('left_line : ', left_line)
            print('right_line : ', right_line)
        elif left_line == 0 or right_line == 0:
            if left_line < 0 or right_line < 0:
                data_send(serial_object, LEFT)
                print('left')
                print('left_line : ', left_line)
                print('right_line : ', right_line)
            elif left_line > 0 or right_line > 0:
                data_send(serial_object, RIGHT)
                print('right')
                print('left_line : ', left_line)
                print('right_line : ', right_line)
        elif abs(left_line-15) > abs(left_line):  # 우회전 해야하는상황
            data_send(serial_object, RIGHT)
            print('right')
            print('left_line : ', left_line)
            print('right_line : ', right_line)
        elif abs(left_line+15) > abs(left_line):  # 좌회전 해야하는상황
            data_send(serial_object, LEFT)
            print('left')
            print('left_line : ', left_line)
            print('right_line : ', right_line)
        else:                                   # 직진
            data_send(serial_object, STOP)
            print('stop')
            print('left_line : ', left_line)
            print('right_line : ', right_line)
    else:
        if left_line > 155 or right_line > 155:
            data_send(serial_object, RIGHT)
            print('hard right')
            print('left_line : ', left_line)
            print('right_line : ', right_line)
        elif left_line < -155 or right_line < -155:
            data_send(serial_object, LEFT)
            print('hard left')
            print('left_line : ', left_line)
            print('right_line : ', right_line)
        else:
            print('back')
            print('left_line : ', left_line)
            print('right_line : ', right_line)