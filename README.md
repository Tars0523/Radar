
# Radar Mapping 

```c
>> catkin_make
>> rosrun beginner_tutorias trans.cpp
>> rviz
>> rosbag play ~/*data*
```


*Bag file* : Important Data topic is wheel odom and radar point cloud

*trans.cpp* : Create a map with Radar Point Cloud based on the position and orientaion information from the wheel odometry.

*rviz configuration* : frame_id "radar", topic add pointcloud1 , set DecayTime long.

# UMRR - type 132
![5F00F7D6-34E6-4EE0-8AF6-1D6228B0463F](https://user-images.githubusercontent.com/100289642/205299661-cc4d443d-4c2e-4f5a-ba80-ca9f14364b18.jpeg)
UMRR Radar for ROS provide 3 topic : <br/> 1. /radar/radar_data
                           <br/> 2. /radar/filtered_data
                           <br/> 3. /radar/target_list_cartesian

Fitering method : raw: /radar/radar_data -> /radar/filtered_data -> /radar/target_list_cartesian <br/> 
 1. RAW data from sensor <br/> 
 2. Filtering config , custom in rviz or configuration file <br/> 
 3. Filtered data , msg using pointcloud2 <br/> 

Important Featrue : range [], radial speed[] , azimuth angle[] , evelvation angle[], reflectivity [] <br/> 
<br/> 
Important Spec : <br/> 
 1.almost unaffedcted by weather, temperature and lighting codintion [2]
 
 2.ultra-high definition resolution <br/>
  i) A different radial speed value <br/>
  ii) A different range value <br/> 
  iii) A different azimuth angular position
   
 3. modulation FMCW [1] <br/> 
  i) *Range measurement* using frequecny difference and phase shift <br/> 
  ii) *Radial Velocity* using doppler freqeucny change <br/> 
  iii) *Angle measurement* using phase shift difference bettween two or more reciver(antena) <br/> 
                 
# Data pipeline
1. Just delete far points
2. z value less than 2m, delete
3. using speed radial, seperate Dynamic and Static
4. using intensity less than a threshold                 


# TODO
1. Find good paper about Radar SLAM, Radar Localization
2. Use MATLAB make environment for Analyis Data(Bagfile from Robot)
3. Why radar point cloud canoot detect Ground ?
4. Unit of features ? 
                 
# Reference <br/>                 
*RADAR/INS INTEGRATION FOR POSE ESTIMATION IN GNSS-DENIED ENVIRONMENTS[1] <br/> 
*smartmicro sensor UMRR-11 type 132 data spec[2] <br/> 
