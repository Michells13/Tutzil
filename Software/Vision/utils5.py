import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from ultralytics import YOLO
from ultralytics.solutions import heatmap
from collections import defaultdict
import numpy as np
import cv2
import socket
import time
import struct





def encode_image_to_jpeg(frame, quality=90):
    """
    Codifica una imagen en formato JPEG con la calidad especificada.

    Args:
        frame: La imagen en formato NumPy array.
        quality: La calidad de la imagen JPEG (por defecto es 90).

    Returns:
        encoded_image: La imagen codificada en formato JPEG.
    """
    encode_param = [int(cv2.IMWRITE_JPEG_QUALITY), quality]
    result, encoded_image = cv2.imencode('.jpg', frame, encode_param)
    return encoded_image

def convert_encoded_image_to_bytes(encoded_image):
    """
    Convierte la imagen codificada a un stream de bytes.

    Args:
        encoded_image: La imagen codificada en formato JPEG.

    Returns:
        string_data: La imagen en formato de bytes.
    """
    data = np.array(encoded_image)
    string_data = data.tobytes()
    return string_data

def send_image_over_tcp(connection, string_data):
    """
    Envía una imagen codificada a través de una conexión TCP/IP.

    Args:
        connection: El socket de la conexión TCP/IP.
        string_data: La imagen en formato de bytes.
    """
    connection.sendall(struct.pack(">L", len(string_data)) + string_data)
    
def start_camera(device):
    cap = cv2.VideoCapture(device)
    if not cap.isOpened():
        print("Error al abrir el video")
        exit()
    
    return cap

def createTextFile():
    # Escribimos en el archivo de texto
    with open('state.txt', 'w') as file:
        # Aquí puedes cambiar 'True' por cualquier otro contenido que desees escribir
        file.write('True')

def readTextFile():
    state=False
    # Abrimos el archivo en modo de lectura
    with open('state.txt', 'r') as file:
    # Leemos el contenido del archivo
        content = file.read().strip()  # Usamos strip() para eliminar cualquier espacio en blanco extra

# Evaluamos si el contenido es la palabra "True"
    if content == 'True':
        state= True
    else:
        state= False
    return state

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

## Initialize yolo and process_frame are the functions from run_yolo but splitted in order to implement it in the loop of start comunication
def initialize_yolo(cap, Heatmap, visHeatmap):
    ## Define heatmap variables
    track_history = defaultdict(lambda: [])
    w, h, fps = (int(cap.get(x)) for x in (cv2.CAP_PROP_FRAME_WIDTH, cv2.CAP_PROP_FRAME_HEIGHT, cv2.CAP_PROP_FPS))
    heatmap_obj = None
    if Heatmap:
        # Init heatmap
        heatmap_obj = heatmap.Heatmap()
        heatmap_obj.set_args(colormap=cv2.COLORMAP_PARULA,
                             imw=w,
                             imh=h,
                             view_img=visHeatmap,
                             shape="circle")
    return track_history, heatmap_obj

def process_frame(cap, model, tracker, traclet, display_traclets, Show, Stream, Verbose, Heatmap, heatmap_obj, conf, iou, persist, track_history):
    ret, frame = cap.read()
    if not ret:
        return False, None, None

    if tracker == 0:
        results = model.predict(source=frame, show=Show, stream=Stream, verbose=Verbose) 
    elif tracker == 1:
        results = model.track(source=frame, conf=conf, iou=iou, show=Show, persist=persist, stream=Stream, verbose=Verbose)
    elif tracker == 2:
        results = model.track(source=frame, conf=conf, iou=iou, show=Show, tracker="bytetrack.yaml", persist=persist, stream=Stream, verbose=Verbose)
    
    if tracker > 0 and traclet:
        frame = traclets(results, track_history)
        if display_traclets:
            cv2.imshow("YOLOv8 Traclets",frame)

    if Heatmap:
        im0 = heatmap_obj.generate_heatmap(frame, results)
        # cv2.imshow('heatmap', im0)

    if cv2.waitKey(25) & 0xFF == ord('q'):
        return False, frame, results

    return True, frame, results



def start_server(model,device,config):
    ## Before initialize and run comms, it has to initialize the camera and yolo,
    # then it run the communication loop when the process_frame funtion process a
    # frame with yolo
    ######YOLO pre stuff#################################################
    cap=start_camera(0)
    track_history, heatmap_obj=initialize_yolo(cap,config["Heatmap"] , config["vis_Heatmap"] )
    #######################################################################
    closeComms = False
    startStreaming = False
    cnt=0       # Counter for trying out 5 times reaching conection 
    cnt1=0      # Counter for reading the text file variables each 10 iterations 
    cnt2=0      # Counting total iterations
    createTextFile()
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.settimeout(10)  # Set a timeout for the socket operations
    server_address = ('localhost', 9999)
    print('Starting communication on {} port {}'.format(*server_address))
    server_socket.bind(server_address)
    server_socket.listen(1)

    try:
        while True:
            cnt1=cnt1+1   # each X iterations it will read the text file to see if it's gonna stop the loop
            if not closeComms:
                print('Waiting for a connection...')
            else:
                print('Closing comms...')
                break

            try:
                connection, client_address = server_socket.accept()
            except socket.timeout:
                if closeComms:
                    print('Close comms requested')
                else:
                    print('Timeout, no connection from UI')
                    cnt=cnt+1
                    if cnt==5:
                        closeComms=True
                            
                    
                continue

            try:
                print('Connection from', client_address)

                while True:
                    data = connection.recv(16)
                    if not data:
                        if closeComms:
                            closeComms = False
                            print("Closing comms...")
                            break
                        print('Waiting for data from', client_address)
                        continue

                    decoded_data = data.decode('utf-8')
                    print('Received', decoded_data)

                    if decoded_data == "0000":
                        print('Comms OK')
                        connection.sendall(data)

                    elif decoded_data == "0001":
                        closeComms = True
                        startStreaming = False
                        connection.sendall(data)
                        print("Close comms requested...")
                        break

                    elif decoded_data == "0010" and not startStreaming and not closeComms:
                        startStreaming = True
                        print("Starting vision module")
                        connection.sendall(b'0010')
                    
                    elif decoded_data == "0100" and startStreaming:
                        #Process the frame trhought the model
                        #loop_status, frame, results=process_frame(cap, model, tracker, traclet, display_traclets, Show, Stream, Verbose, Heatmap, heatmap_obj, conf, iou, persist, track_history)
                        loop_status, frame, results=process_frame(cap, model, config["tracker"],config["traclet"] ,config["display_traclets"] , config["Show"],config["Stream"],config["Verbose"] ,config["Heatmap"], heatmap_obj, config["conf"], config["iou"],config["persist"] , track_history)
                        # Codificar, convertir y enviar la imagen
                        #encoded_image = encode_image_to_jpeg(frame)
                        #string_data = convert_encoded_image_to_bytes(encoded_image)
                        #send_image_over_tcp(connection, string_data)

                        
                        if not loop_status:
                            cap.release()
                            cv2.destroyAllWindows()
                        
                        if cnt1>100:
                            closeComms=readTextFile()
                            connection.sendall(b'0001')
                            cnt1=0
                        else :
                            connection.sendall(b'0100')
                            

                    else:
                        print("Unknown command received")
                    
                        continue

            finally:
                cap.release()
                cv2.destroyAllWindows()
                connection.close()

    except KeyboardInterrupt:
        print('Server is shutting down...')
    finally:
        server_socket.close()
        print('Server socket closed.')

