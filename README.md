# Tutzil - ATT: 
## Automated Target Tracking


It is a system that uses computer vision to identify and track targets in real-time. The robotic assistance adjusts the orientation of a camera or shooting device to keep the target centered in the frame. It has been built upon the YOLOv8 model(more archtectures will be added later)on an embedded board integrated with a user interface created in Qt Creator that controls a 2DOF system.



<p align="center">
  <img src="./Assets/concept.jpg" alt="Concept" width="400"/>
  <img src="./Assets/conceptscreen.jpg" alt="Concept Screen" width="380"/>
</p>




| Usage Concept                    | Display  First Concept                          




# Table of Contents

- [Tutzil - ATT: Automated Target Tracking](#tutzil---att-automated-target-tracking)
- [System Architecture](#system-architecture)
- [Vision Module - Jetson Orin/Nano](#vision-module---jetson-orinnan)
  - [Key Features](#key-features)
    - [YOLOv8 Integration](#yolov8-integration)
    - [Flexible Configuration](#flexible-configuration)
    - [Inputs & Outputs](#inputs--outputs)
    - [Modular Design](#modular-design)
    - [Main Loop](#main-loop)
    - [TCP/IP COMMS](#tcpip-comms)
  - [Example Configurations](#example-configurations)
- [UI Module](#ui-module)
- [Control Module](#control-module)
  - [Frameworks](#frameworks)
- [Getting Started](#getting-started)
  - [Clone the Repository](#clone-the-repository)
  - [Install Dependencies](#install-dependencies)
  - [Run the Application](#run-the-application)
- [Contribution](#contribution)
- [License](#license)


## System Architecture 

![Mi imagen](./Assets/System_arch.png)

## Vision Module - Jetson Orin/Nano




The vision module has been developed in Python using the PyTorch framework. Currently, it implements the YOLOv8 model from Ultralytics, though the adaptation of other models is underway. The following sections describe the features and composition of this module, as well as define its inputs and output

### Key Features:

- **YOLOv8 Integration**: 
   - Utilizes OpenCV to capture video from a webcam and feed frames into the YOLOv8 model for real-time inference.
   - Supports various computer vision tasks, including:
     - Object Detection
     - Segmentation
     - Pose Estimation (PE)
     - Classification
     - Oriented Object Detection (OBB)
   - Optionally enables object tracking using methods like BoT-SORT and ByteTrack.

- **Flexible Configuration**: 
   - Configurable through a `config` dictionary that allows users to adjust settings such as detection confidence, visualization options, image size, and output saving preferences.
   - The system supports adjustments for visualization, such as displaying annotated frames, heatmaps, tracklets, and saving results in various formats.

- **Inputs & Outputs**: 
   - **Inputs**: Takes video input from a connected camera and processes frames using the YOLOv8 model.
   - **Outputs**: Generates detection results, including bounding boxes, segmentation masks, and optional heatmaps. Results can be displayed, saved as images, or streamed over TCP/IP.

- **Modular Design**: 
   - Functions are encapsulated in `utils6`, which includes functions for model initialization, frame processing, starting the camera, and setting up a server for communication.
   - Easy to extend and adapt for new tasks by configuring the `config` dictionary.

- **Main Loop**: 
   - In the main function, the camera captures frames, which are processed and analyzed using YOLOv8. The processed results can be send over a network using the TCP/IP server.

     
## TCP/IP Communication and Packet Transmission

This module includes a TCP/IP communication system for transmitting processed image data and associated metadata between a vision module and a graphical interface module. Below is an overview of the key functions and processes involved:

### Data Encoding and Transmission

1. **Data Encoding**:
    - **`encode_image_to_jpeg(frame, quality=90)`**: Encodes a given image frame into JPEG format with a specified quality (default is 90).
    - **`convert_encoded_image_to_bytes(encoded_image)`**: Converts the encoded JPEG image into a stream of bytes for transmission.
    - **`enconde_data_to_json(all_data)`**: Encodes detection results (bounding boxes, class IDs, track IDs) into JSON format for easy transmission.

2. **Packet Construction**:
    - **`send_packet_over_tcp(connection, string_data, json_data)`**: Constructs and sends a data packet over a TCP/IP connection. The packet includes:
        - The size of the encoded image in bytes.
        - The encoded JPEG image.
        - JSON data containing bounding boxes, class IDs, and track IDs.

    Data is packed using the `struct` library to ensure consistent size and format, helping maintain synchronization between the sender and receiver.

3. **Timing Measurement**:
    - Throughout the transmission process, time is measured to track the time taken for various steps (e.g., image encoding, JSON serialization, packet creation, and transmission). This helps in diagnosing latency and optimizing the communication.

### TCP/IP Server

The server listens for incoming connections, processes frames through the YOLOv8 model, and sends the results over the established connection.

- **`start_server(model, device, config, camDevice)`**: This function initializes the YOLO model, starts the camera, and manages the communication loop:
    - Listens for incoming connections.
    - Receives commands to start or stop the vision module.
    - Processes frames through YOLO and tracks objects.
    - Encodes processed frames and metadata.
    - Sends data packets over the TCP/IP connection.

- **`process_frame`**: Handles YOLO inference on a frame, extracts tracking data, and prepares the image and metadata for transmission.

### Packet Structure

The packets sent over TCP/IP have the following structure:
   1. **Image Data**: The size of the JPEG image followed by the image bytes.
   2. **Metadata**: The size of the JSON data followed by the JSON string containing:
       - **Track IDs**: A list of tracking IDs for detected objects.
       - **Class IDs**: A list of class IDs corresponding to detected objects.
       - **Normalized Bounding Boxes**: The coordinates of bounding boxes for each detected object, normalized to the image dimensions.

### Error Handling and Timeout Management

- The server uses a timeout mechanism to handle connection delays and timeouts during the wait for client connections.
- If a connection is not established within a set number of attempts, the server terminates the communication.

### Example Usage

The following is an example of the server initialization:

```python
# Example server start with a YOLO model, camera device, and configuration parameters
start_server(model, device, config, camDevice)
```



### Example Configurations:

- **Mode**: Inference (only)
- **Task Options**: Segmentation, Detection, Classification, etc.
- **Tracker**: BoT-SORT or ByteTrack for enhanced object tracking.
- **Visualization**: Heatmap generation, tracklet display, and more.

<sub>Note: The vision module has been implemented on a separate device to maintain the autonomy of the UI system and to allocate the necessary resources for vision processing independently. Following this model, it will be easier to replace the embedded module with a more powerful system in the future, and it also allows for independent development of both the UI and vision modules</sub>
## UI Module
 

## Control Module


## Getting Started

To get started with the project, follow these steps:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/michells13/tutzil.git
   cd tutzil  
   
2. **Install Dependencies**:
Ensure you have Python and Qt Creator installed. Then, install the required Python packages:

pip install -r requirements.txt

3. **Run the Application**:
Launch the Qt interface and start the tracking system:
- launch.exe

## Contribution
Contributions are welcome! If you'd like to contribute, please fork the repository and submit a pull request.

## License
This project is licensed under the MIT License.
