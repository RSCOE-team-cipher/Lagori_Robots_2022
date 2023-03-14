#!/usr/bin/env python3


from numpy import int32
import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from sensor_msgs.msg import Joy
from std_msgs.msg import Int32

#from lagori_robot_msgs.msg import GripperMsg
#from lagori_robot_msgs.msg import StepperMsg

class GripperSubscriber(Node):
	def __init__(self):
		super().__init__('gripper_subscriber')
		self.grip = Int32()
		
		self.msg = Joy()
		self.subscription = self.create_subscription(Joy, '/joy', self.listener_callback, 10)
		self.subscription  # prevent unused variable warning

		## experiment
		self.gripper_publisher_ = self.create_publisher(Int32, '/robot_2_gripper', 10)
		timer_period = 0.02  # seconds
		self.timer = self.create_timer(timer_period, self.timer_callback)
		self.i = 0
				
	def listener_callback(self, msg):
		global switch_state

		#G G G idle | open idle | close idle |
        #1,2,3, 4   |   1   0   |  1      0  |
    
		self.grip.data = 0
		if (msg.axes[6]==1):
			self.grip.data = self.grip.data*10 + 1
		elif (msg.axes[7] == 1):
			self.grip.data = self.grip.data*10 + 2
		elif (msg.axes[6] == -1):
			self.grip.data = self.grip.data*10 + 3
		elif (msg.axes[6] == 0 or msg.axes[7] == 0):
			self.grip.data = self.grip.data*10 + 4
		else:
			self.grip.data = self.grip.data*10 + 4

		self.grip.data = self.grip.data*10 + msg.buttons[1]
		self.grip.data = self.grip.data*10 + msg.buttons[3]
		
		switch_state = msg.buttons[7]

		
	def timer_callback(self):
		# print(self.grip.data)
		self.gripper_publisher_.publish(self.grip)
		self.i += 1	
	
def main(args=None):
	rclpy.init(args=args)
	
	gripper_subscriber = GripperSubscriber()

	rclpy.spin(gripper_subscriber)
    
	gripper_subscriber.destroy_node()
	rclpy.shutdown()


if __name__ == '__main__':
	main()

