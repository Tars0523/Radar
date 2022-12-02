# Radar Mapping 

*Bag file* : Important Data topic is wheel odom and radar point cloud

*trans.cpp* : Create a map with Radar Point Cloud based on the position and orientaion information from the wheel odometry.

*rviz configuration* : frame_id "radar", topic add pointcloud1 , set DecayTime long.

# UMRR - type 132

UMRR ROS provide 3 topic : 1. /radar/radar_data
                           2. /radar/filtered_data
                           3. /radar/target_list_cartesian

Fitering method : raw: /radar/radar_data -> /radar/filtered_data -> /radar/target_list_cartesian
1. RAW data from sensor
2. Filtering config , custom in rviz or configuration file
3. Filtered data , msg using pointcloud2

Important Featrue : range [], radial speed[] , azimuth angle[] , evelvation angle[], reflectivity []
Important Spec : 1.almost unaffedcted by weather, temperature and lighting codintion[2]
                 2.ultra-high definition resolution, 
                      i) A different radial speed value
                      ii) A different range value
                      iii) A different azimuth angular position
                 3. modulation FMCW[1] 
                 
# Data pipeline

                 
                 
                 
# Reference                 
RADAR/INS INTEGRATION FOR POSE ESTIMATION IN GNSS-DENIED ENVIRONMENTS[1] 
smartmicro sensor UMRR-11 type 132 data spec[2]
