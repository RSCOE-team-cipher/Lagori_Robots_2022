#!/usr/bin/env python3

from numpy import int32
import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from sensor_msgs.msg import Joy
from std_msgs.msg import Int32
# from lagori_robot_msgs.msg import StepperMsg
# from lagori_robot_msgs.msg import StepperMsg

class StepperSubscriber(Node):
	def __init__(self):
		super().__init__('stepper_subscriber')
		self.stepper = Int32()
		
		self.msg = Joy()
		self.subscription = self.create_subscription(Joy, '/joy', self.listener_callback, 10)
		self.subscription  # prevent unused variable warning

		## experiment
		self.stepper_publisher_ = self.create_publisher(Int32, '/robot_2_stepper', 10)
		timer_period = 0.02  # seconds
		self.timer = self.create_timer(timer_period, self.timer_callback)
		self.i = 0
				
	def listener_callback(self, msg):
		global switch_state

		#S S S idle |  up idle  | down idle  |
        #1,2,3, 4   |   1   0   |  1      0  |
    
		self.stepper.data = 0
		if (msg.axes[6]==1):
			self.stepper.data = self.stepper.data*10 + 1
		elif (msg.axes[7] == 1):
			self.stepper.data = self.stepper.data*10 + 2
		elif (msg.axes[6] == -1):
			self.stepper.data = self.stepper.data*10 + 3
		elif (msg.axes[6] == 0 or msg.axes[7] == 0):
			self.stepper.data = self.stepper.data*10 + 4
		else:
			self.stepper.data = self.stepper.data*10 + 4

		self.stepper.data = self.stepper.data*10 + msg.buttons[2]
		self.stepper.data = self.stepper.data*10 + msg.buttons[0]
		
		switch_state = msg.buttons[7]
		
	def timer_callback(self):
		# print(self.grip.data)
		self.stepper_publisher_.publish(self.stepper)
		self.i += 1	
	
def main(args=None):
	rclpy.init(args=args)
	
	stepper_subscriber = StepperSubscriber()

	rclpy.spin(stepper_subscriber)
    
	stepper_subscriber.destroy_node()
	rclpy.shutdown()


if __name__ == '__main__':
	main()
