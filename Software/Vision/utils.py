import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from ultralytics import YOLO
from ultralytics.solutions import heatmap
from collections import defaultdict
import numpy as np
import cv2





def traclets(results,track_history):
        # Get the boxes and track IDs
    boxes = results[0].boxes.xywh.cpu()
    track_ids = results[0].boxes.id.int().cpu().tolist()

    # Visualize the results on the frame
    annotated_frame = results[0].plot()

    # Plot the tracks
    for box, track_id in zip(boxes, track_ids):
        x, y, w, h = box
        track = track_history[track_id]
        track.append((float(x), float(y)))  # x, y center point
        if len(track) > 30:  # retain 90 tracks for 90 frames
            track.pop(0)
            
            
        # Draw the tracking lines
        points = np.hstack(track).astype(np.int32).reshape((-1, 1, 2))
        cv2.polylines(annotated_frame, [points], isClosed=False, color=(230, 230, 230), thickness=10)
    return annotated_frame

def configure_model(task):
    if task == "detection":
        return YOLO('yolov8n.pt')
    elif task == "segmentation":
        return YOLO('yolov8n-seg.pt')
    elif task == "PE":
        return YOLO('yolov8n-pose.pt')
    elif task == "classification":
        return YOLO('yolov8n-cls.pt')
    elif task == "obb":
        return YOLO('yolov8n-obb.pt')

def run_yolo(cap, model,tracker,traclet,display_traclets,Show,Stream,Verbose,Heatmap,visHeatmap,conf,iou,persist):
    
    ##Define heatmap variables
    track_history = defaultdict(lambda: [])
    w, h, fps = (int(cap.get(x)) for x in (cv2.CAP_PROP_FRAME_WIDTH, cv2.CAP_PROP_FRAME_HEIGHT, cv2.CAP_PROP_FPS))
    if Heatmap:
    # Init heatmap
        heatmap_obj = heatmap.Heatmap()
        heatmap_obj.set_args(colormap=cv2.COLORMAP_PARULA,
                             imw=w,
                             imh=h,
                             view_img=visHeatmap,
                             shape="circle")

    
    while True:
        ret, frame = cap.read()

        if not ret:
            break
        if tracker==0 :
          results = model.predict(source=frame, show=Show, stream=Stream, verbose=False) 
        if tracker==1 :
           results = model.track(source=frame, conf=conf, iou=iou,show=Show,persist=persist, stream=Stream, verbose=False)  # Tracking with default tracker
        if tracker==2 :
           results = model.track(source=frame, conf=conf, iou=iou,show=Show, tracker="bytetrack.yaml", persist=persist, stream=Stream, verbose=False)  # Tracking with ByteTrack tracker
        
       

        if tracker > 0 and traclet:
            annotated_frame = traclets(results, track_history)
            if display_traclets:
                cv2.imshow("YOLOv8 Traclets", annotated_frame)

        if Heatmap==True:
            im0 = heatmap_obj.generate_heatmap(frame, results)
            #cv2.imshow('heatmap', im0)

        if cv2.waitKey(25) & 0xFF == ord('q'):
            break
'''
def main():
    cap = cv2.VideoCapture(0)
    track_history = defaultdict(lambda: [])
    
    if not cap.isOpened():
        print("Error al abrir el video")
        exit()

    model = configure_model(TASK)
    run_yolo(cap, model, track_history)

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
'''