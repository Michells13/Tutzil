# -*- coding: utf-8 -*-
"""
YOLO con utils y parametros funcionando y comunicacion tcp/ip

@author: Michell
"""
import socket
import time
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from ultralytics import YOLO
from ultralytics.solutions import heatmap
from collections import defaultdict
import numpy as np
import cv2
import time
from utils6 import traclets, configure_model, run_yolo, initialize_yolo, process_frame,createTextFile, readTextFile, start_camera,start_server
import time
 




'''
YOLO V8  implementation (Ultralitics): 
        it uses opencv webcam caputure to feed the network
        there exist three methods to use YOLO V8, object detection, segmentation,
        clasification, all of them can be applied within this code by selecting
        the task  and there is also an option to perform traking by turning True 
        that option ..
        
        
        -Inputs:   
            MODE SELECTION OPTIONS 
                    MODE:   Inference       @This code only can be used to perform inference@
                    TASK:
                        "detection"     - Object detection
                        "segmentation"  - Segmentation
                        "PE"            - Pose estimation
                        "classification'- Clasification
                        "obb"           - Oriented object detection 
                        
             INFERENCE ARGUMENTS:       ...............
             VIZUALIZATION ARGUMENTS:   ...............
             OUTPUTS:                   ...............

'''




config = {
    "MODE": "Inference",  # Training, validation, export, track
    "TASK": "segmentation",  # detection, segmentation, PE, classification, OBB
    "Verbose": False,

    # Inference arguments
    "tracker": 1,  # 0- Disable, 1- BoT-SORT, 2- ByteTrack
    "conf": 0.4,  # Minimum confidence threshold
    "iou": 0.7,  # IoU threshold for Non-Maximum Suppression (NMS)
    "half": False,  # Enables half-precision (FP16) inference

    # Visualization arguments
    "Show": True,  # Display annotated images or videos
    "traclet": False,  # Creates tracklets
    "display_traclets": False,  # Displays tracklets
    "Heatmap": False,  # Heatmap activation
    "vis_Heatmap": False,  # Visualization of Heatmap
    "persist": True,
    "visualize": False,  # Visualization of model features

    # Other settings
    "imgsz": 640,  # Image size for inference
    "device": 0,  # Device for inference (e.g., cpu, cuda:0)
    "max_det": 20,  # Maximum number of detections per image
    "vid_stride": 1,  # Frame stride for video inputs
    "stream_buffer": False,  # Buffer all frames when processing video streams
    "augment": False,  # Enables test-time augmentation (TTA)
    "agnostic_nms": False,  # Class-agnostic Non-Maximum Suppression (NMS)
    "classes": None,  # Filters predictions to a set of class IDs
    "retina_masks": False,  # Uses high-resolution segmentation masks
    "embed": None,  # Specifies layers to extract feature vectors
    "Stream": False,  # Use stream=True for processing large datasets

    # Saving settings
    "save": False,  # Save annotated images or videos
    "save_frames": False,  # Save individual frames as images
    "save_txt": False,  # Save detection results in a text file
    "save_conf": False,  # Include confidence scores in saved text files
    "save_crop": False,  # Save cropped images of detections
    "show_labels": True,  # Display labels for each detection
    "show_conf": True,  # Display confidence scores
    "show_boxes": True,  # Draw bounding boxes around detected objects
    "line_width": None  # Line width of bounding boxes
}
''' Results objects have the following attributes:

Attribute |     Type      | Description

orig_img	numpy.ndarray	The original image as a numpy array.
orig_shape	tuple	        The original image shape in (height, width) format.
boxes	    Boxes,          optional	A Boxes object containing the detection bounding boxes.
masks	    Masks,          optional	A Masks object containing the detection masks.
probs	    Probs,          optional	A Probs object containing probabilities of each class for classification task.
keypoints	Keypoints,      optional	A Keypoints object containing detected keypoints for each object.
obb	        OBB,            optional	 An OBB object containing oriented bounding boxes.
speed	    dict	        A dictionary of preprocess, inference, and postprocess speeds in milliseconds per image.
names	    dict	        A dictionary of class names.
path	    str	            The path to the image file.'''

'''Results objects have the following methods:

Method	   Return Type	      Description
update()	None	      Update the boxes, masks, and probs attributes of the Results object.
cpu()	    Results	      Return a copy of the Results object with all tensors on CPU memory.
numpy()	    Results	         Return a copy of the Results object with all tensors as numpy arrays.
cuda()	    Results	      Return a copy of the Results object with all tensors on GPU memory.
to()	    Results	      Return a copy of the Results object with tensors on the specified device and dtype.
new()	    Results	      Return a new Results object with the same image, path, and names.
plot()	    numpy.ndarray Plots the detection results. Returns a numpy array of the annotated image.
show()	    None	      Show annotated results to screen.
save()	    None	      Save annotated results to file.
verbose()	str	         Return log string for each task.
save_txt()	None	     Save predictions into a txt file.
save_crop()	None	     Save cropped predictions to save_dir/cls/file_name.jpg.
tojson()	str	        Convert the object to JSON format.'''





#Main for testing some functions  without the communication       
def main(config):
    cap = cv2.VideoCapture(0)
    
    
    if not cap.isOpened():
        print("Error al abrir el video")
        exit()

    model = configure_model(config["TASK"])    
    
    #Run yolo has the initialize_yolo() and process_frame() functions merged  
    #run_yolo(cap, model,config["tracker"],config["traclet"],config["display_traclets"],config["Show"],config["Stream"],config["Verbose"],config["Heatmap"],config["vis_Heatmap"],config["conf"],config["iou"],config["persist"])  
   
    
   
    track_history, heatmap_obj=initialize_yolo(cap,config["Heatmap"] , config["vis_Heatmap"] )
    while True:
 
        loop_status, frame, results=process_frame(cap, model, config["tracker"],config["traclet"] ,config["display_traclets"] , config["Show"],config["Stream"],config["Verbose"] ,config["Heatmap"], heatmap_obj, config["conf"], config["iou"],config["persist"] , track_history)
        if not loop_status:
            break

    cap.release()
    cv2.destroyAllWindows()

"""
comms codes :
--------------------------------
-0000: Comms OK                -
-0001: Close Comms requested   -
-0010: Start streaming         -
--------------------------------
"""


activateUiUse=True



if __name__ == "__main__":
    if activateUiUse:
        
        device=0
        model = configure_model(config["TASK"])
        start_server(model,0,config,device)
        
        
    else:
        main(config)



# https://docs.ultralytics.com/modes/predict/#images