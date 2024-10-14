# Tutzil - ATT: 
## Automated Target Tracking


It is a system that uses computer vision to identify and track targets in real-time. The robotic assistance adjusts the orientation of a camera or shooting device to keep the target centered in the frame. It has been built upon the YOLOv8 model(more archtectures will be added later)on an embedded board integrated with a user interface created in Qt Creator that controls a 2DOF system.


<p align="center">
  <img src="./Assets/concept.jpg" alt="Concept" width="400"/>
  <img src="./Assets/conceptscreen.jpg" alt="Concept Screen" width="380"/>
</p>




| Usage Concept                    | Display  First Concept                          


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

     
- **TCP/IP COMMS**: 
### Example Configurations:

- **Mode**: Inference (only)
- **Task Options**: Segmentation, Detection, Classification, etc.
- **Tracker**: BoT-SORT or ByteTrack for enhanced object tracking.
- **Visualization**: Heatmap generation, tracklet display, and more.

<sub>Note: The vision module has been implemented on a separate device to maintain the autonomy of the UI system and to allocate the necessary resources for vision processing independently. Following this model, it will be easier to replace the embedded module with a more powerful system in the future, and it also allows for independent development of both the UI and vision modules</sub>
## UI Module
 

## Control Module

### Frameworks







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
