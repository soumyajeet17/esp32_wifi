#!/usr/bin/env python3

import rospy
from std_msgs.msg import String

def callback(data):
    # Print the received message from the ESP32
    rospy.loginfo("Received message: %s", data.data)

def listener():
    # Initialize the ROS node named 'esp32_listener'
    rospy.init_node('esp32_listener', anonymous=True)

    # Subscribe to the 'chatter' topic and specify the callback function
    rospy.Subscriber("chatter", String, callback)

    # Spin to keep the node running and handling callbacks
    rospy.spin()

if __name__ == '__main__':
    try:
        listener()
    except rospy.ROSInterruptException:
        pass

