from numpy import int32
import rclpy
from rclpy.node import Node

from std_msgs.msg import String
from sensor_msgs.msg import Joy
from std_msgs.msg import Int32

import sys
#import  Rpi.GPIO as GPIO
import time

#PI_PIN = 16
#GPIO.setmode(GPIO.BCM)
#GPIO.setup(PI_PIN, GPIO.OUT)

switch_state = 0

class MinimalSubscriber(Node):
	def __init__(self):
		super().__init__('minimal_subscriber')
		# self.grip = Bull()
		self.grip = Int32()
		
		self.msg = Joy()
		self.subscription = self.create_subscription(Joy, '/joy', self.listener_callback, 10)
		self.subscription  # prevent unused variable warning

		## experiment
		self.publisher_ = self.create_publisher(Int32, '/robot_2', 10)
		timer_period = 0.1  # seconds
		self.timer = self.create_timer(timer_period, self.timer_callback)
		self.i = 0
				
	def listener_callback(self, msg):
		global switch_state

		self.grip.data = 0
		if (msg.buttons[4] == 0):
			if (msg.axes[6]==1):
				self.grip.data = self.grip.data*10 + 1
			elif (msg.axes[7] == 1):
				self.grip.data = self.grip.data*10 + 2
			elif (msg.axes[6] == -1):
				self.grip.data = self.grip.data*10 + 3
			else:
				self.grip.data = self.grip.data*10 + 4
			# grip.num = msg.axes[6]
			# global grip
			self.grip.data = self.grip.data*10 + msg.buttons[3]
			self.grip.data = self.grip.data*10 + msg.buttons[0]
			self.grip.data = self.grip.data*10 + msg.buttons[2]
			self.grip.data = self.grip.data*10 + msg.buttons[1]
		
		switch_state = msg.buttons[7]
		#if switch_state==1:
		#	#press safety switch
		#	GPIO.output(PI_PIN, GPIO.HIGH)
		#	GPIO.cleanup()


	def timer_callback(self):
		#data = Bull()
		#data = grip
		#global grip
		print(self.grip.data)
		self.publisher_.publish(self.grip)
		#self.get_logger().info('Publishing: "%s"' % msg.data)
		self.i += 1	
	
def main(args=None):
	rclpy.init(args=args)
	
	minimal_subscriber = MinimalSubscriber()
	# minimal_publisher = MinimalPublisher()

	rclpy.spin(minimal_subscriber)
	# rclpy.spin(minimal_publisher)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
	minimal_subscriber.destroy_node()
	rclpy.shutdown()


if __name__ == '__main__':
	main()
