# -*- coding: utf-8 -*-
"""
Created on Fri Feb  9 15:19:05 2024

@author: Michell
"""
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from ultralytics import YOLO
from ultralytics.solutions import heatmap
from collections import defaultdict
import numpy as np
import cv2
from utils import traclets, configure_model, run_yolo

 
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

#Mode selection options
MODE= "Inference"   #Training, validation, export, track
TASK="detection"    #"detection", "segmentation", "PE", "classification",OBB     
Verbose=False


#Inference arguments
tracker         =1             # Enable tracking   0- Disable,  1- BoT-SORT, 2- ByteTrack,
conf            =0.4           # Sets the minimum confidence threshold for detections. Objects detected with confidence below this threshold will be disregarded. Adjusting this value can help reduce false positives.
iou             =0.7           # Intersection Over Union (IoU) threshold for Non-Maximum Suppression (NMS). Lower values result in fewer detections by eliminating overlapping boxes, useful for reducing duplicates.
half            =False         # Enables half-precision (FP16) inference

#Visualization arguments:
Show            =True          # If True, displays the annotated images or videos in a window. Useful for immediate visual feedback during development or testing.
traclet         =True          # creates tracklets
display_traclets=False          # displays tracklets
Heatmap         =False         # Heatmap activation 
vis_Heatmap     =False         # Visualization 
persist         =True          #
visualize       =False         # Activates visualization of model features during inference, providing insights into what the model is "seeing". Useful for debugging and model interpretation.  

#Other settings       
imgsz           =640           # Defines the image size for inference. Can be a single integer 640 for square resizing or a (height, width) tuple. Proper sizing can improve detection accuracy and processing speed.
device          =None          # Specifies the device for inference (e.g., cpu, cuda:0 or 0). Allows users to select between CPU, a specific GPU, or other compute devices for model execution.
max_det         =20            # Maximum number of detections allowed per image. Limits the total number of objects the model can detect in a single inference, preventing excessive outputs in dense scenes.
vid_stride      =1             # Frame stride for video inputs. Allows skipping frames in videos to speed up processing at the cost of temporal resolution. A value of 1 processes every frame, higher values skip frames.
stream_buffer   =False         # Determines if all frames should be buffered when processing video streams (True), or if the model should return the most recent frame (False). Useful for real-time applications.
augment         =False         # Enables test-time augmentation (TTA) for predictions, potentially improving detection robustness at the cost of inference speed.
agnostic_nms    =False         # Enables class-agnostic Non-Maximum Suppression (NMS), which merges overlapping boxes of different classes. Useful in multi-class detection scenarios where class overlap is common.
classes         =None          # list[int] : Filters predictions to a set of class IDs. Only detections belonging to the specified classes will be returned. Useful for focusing on relevant objects in multi-class detection tasks.
retina_masks    =False         # Uses high-resolution segmentation masks if available in the model. This can enhance mask quality for segmentation tasks, providing finer detail.
embed=None                     # list[int] : Specifies the layers from which to extract feature vectors or embeddings. Useful for downstream tasks like clustering or similarity search.
Stream=False                   # Use stream=True for processing long videos or large datasets to efficiently manage memory. When stream=False, the results for all frames or data points are stored in memory, which can quickly add up 
                               #and cause out-of-memory errors for large inputs. In contrast, stream=True utilizes a generator, which only keeps the results of the current frame or data point in memory, significantly reducing memory consumption and preventing out-of-memory issues.


save		          =False	# Enables saving of the annotated images or videos to file. Useful for documentation, further analysis, or sharing results.
save_frames	      =False	# When processing videos, saves individual frames as images. Useful for extracting specific frames or for detailed frame-by-frame analysis.
save_txt	          =False	# Saves detection results in a text file, following the format [class] [x_center] [y_center] [width] [height] [confidence]. Useful for integration with other analysis tools.
save_conf	      =False	# Includes confidence scores in the saved text files. Enhances the detail available for post-processing and analysis.
save_crop	      =False	# Saves cropped images of detections. Useful for dataset augmentation, analysis, or creating focused datasets for specific objects.
show_labels	      =True	# Displays labels for each detection in the visual output. Provides immediate understanding of detected objects.
show_conf         =True	# Displays the confidence score for each detection alongside the label. Gives insight into the model's certainty for each detection.
show_boxes        =True	# Draws bounding boxes around detected objects. Essential for visual identification and location of objects in images or video frames.
line_width	      =None   # Specifies the line width of bounding boxes. If None, the line width is automatically adjusted based on the image size. Provides visual customization for clarity.

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





#Output
      
def main():
    cap = cv2.VideoCapture(0)
    
    
    if not cap.isOpened():
        print("Error al abrir el video")
        exit()

    model = configure_model(TASK)
    run_yolo(cap, model,tracker,traclet,display_traclets,Show,Stream,Verbose,Heatmap,vis_Heatmap,conf,iou,persist)

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()



# https://docs.ultralytics.com/modes/predict/#images