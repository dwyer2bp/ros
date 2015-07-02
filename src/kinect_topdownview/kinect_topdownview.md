#README

This small project is an example of how to write a nodelet to receive kinect pointclouds for processing
along with how to launch the nodelet into a nodelet manager who has the kinect driver's nodelet also operating in it.
My example nodelet subscribes to "/camera/depth/points", runs a PCL-Passthrough filter, and outputs a sensor_msgs/image
to show a "top down" view of just a slice of kinect data points. The code is not perfect, but runs fine on my laptop and 
the NVidia Jetson. If you run on an NVidia Jetson, you will need to use this nodelet method because using a node will bottleneck
due to the TCP data transfer that has to happen (practically un-noticable on a laptop i7 processor).

To use:
  1. Download the "/kinect_topdownview" directory into your ros/src/ directory
  2. cd to your ros workspace
  3. run 'catkin_make --pkg kinect_topdownview'
  4. As long as this builds, move on to "to Run"
  
To run:
  1. Run your favorite 'launch' file for the kinect driver in a terminal (assuming either openni_launch openni.launch or freenect_launch freenect.launch)
  2. Open another terminal, and type 'roslaunch kinect_topdownview kinect_topdownview.launch'
  3. Open another terminal, and run rqt by typing 'rqt'. Open up an image viewer (Plugins/Visualization/Image_View)
  4. Find and select the kinect topdown image ("/camera/kinect_topdown_img")
  
Dependencies: (after installing ros-<distro>-ros-base, tested on ros-indigo)
You need to have installed:
  1. ros-<distro>-libpcl-ros (to compile and run my processing code)
  2. ros-<distro>-rqt (to view the image in rqt)
  3. ros-<distro>-rqt-common-plugins (to view the image in rqt)
  4. ros-<distro>-freenect-launch or ros-<distro>-openni-launch
  5. ros-<distro>-laser-geometry (I have this as a dependency in the cmakefile, so either install or remove from CMakelists.txt)
  6. 
Hopefully this is complete. If not, I'll work withyou.

If you have any issues, you can make a post @ devtalk.nvidia.com 
(https://devtalk.nvidia.com/default/topic/848006/embedded-systems/speeding-up-pointcloud-delivery-to-ros-subscriber-kinect-data-/)
