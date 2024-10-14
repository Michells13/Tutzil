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



<sub>Note: The vision module has been implemented on a separate device to maintain the autonomy of the UI system and to allocate the necessary resources for vision processing independently. Following this model, it will be easier to replace the embedded module with a more powerful system in the future, and it also allows for independent development of both the UI and vision modules</sub>
## UI Module
 

## Control Module

### Frameworks



## Features

- **Object Detection**: Utilizes the YOLOv8 model (different architectures will be added later)for accurate and efficient object detection, pose estimation and segmentation.
- **Real-Time Tracking**: Tracks detected objects in real-time, ensuring smooth and responsive operation.
- **User Interface**: A user-friendly interface built with Qt Creator, providing easy control and visualization.
- **Pan and Tilt Control**: Integrates with a two-degree-of-freedom system for comprehensive tracking capabilities, allowing for precise control over pan (horizontal movement) and tilt (vertical movement) axes.



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
