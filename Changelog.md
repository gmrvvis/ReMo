# v0.0.2 - (2018-02) 
1. Add WebStreamer input media, stream and flow:
* Basic examples using WebStreamer (Desktop and WebCam)
* API modification to be usable with ReMoToo and ReMoLON
* CMake configuration files improvements (optional dependencies and examples, configure with common)

# v0.0.1 - (2018-12) 
1. Initial framework functionality including:
* Media devices: Desktop and WebCam.
* Media palyers: Basic SDL player.
* Media File: Video file (mpeg video stream in a mp4 container).
* Streams: To process the input and output media (devices, video files, and a simple viewer).
* Flows: To connect input to output streams (Eg. in Device (Desktop or WebCam) to viewer or file).
* Pipeline: Some image processing infrastructure using pipeline.

2. Basic use examples:
* Desktop viewer
* Desktop to video file
* WebCam viewer
* WebCam to file
* Conceptual pipeline test.
