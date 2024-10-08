# Tutzil: Object Detection and Tracking System
Object detector for human assistance 

Tutzil is an advanced object detection and tracking system built upon the YOLOv8 model by Ultralytics, integrated with a user interface created in Qt Creator. This project aims to develop a tracking assistant that interfaces with a two-degree-of-freedom system, featuring pan and tilt axes as well as an extra actuator for multiple propuses.


## Objectives

Basically this is an artificial vision system controlling a two-degree-of-freedom robot, where the user selects an object on the screen, and the robotic system autonomously adjusts the camera to accurately point at the chosen object. The primary goal of this project is to create a reliable and efficient tracking assistant that can be used mainly in a security system with a 2 DOF robot but also as a camera stabilizer.

## System Architecture 

![Mi imagen](./Assets/System_arch.png)



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
