# These scripts are used to parse CSV files and generate ROS bag files.
## The usage sequence is as follows and must be followed strictly:
1. Go to "others" folder; using *sync-data-one.py* script to integrate acclerometer and gyroscope messages.
2. Stil in the "others" folder; running *csv_T_tum.py* script to produce ground-truth file (a ".tum" file).
3. Go to "rosbag" folder; using *advio_to_rosbag.py* to yeild ROS bag file, which will be stored in the "iphone--" subfolder.
## Usage of each script
All abovementioned files have two appending parameters. The first one is target folder, and the second one is the sequence number.
Here is an example:
``python3 sync-data-one.py ../../sequences 03``
