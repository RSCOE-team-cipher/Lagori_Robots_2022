from numpy import int32
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
# from my_msgs.msg import Bull
from sensor_msgs.msg import Joy
from std_msgs.msg import Int32
from geometry_msgs.msg import Twist
from lagori_robot_msgs.msg import RobotOneControls

import time

rotor_index = 3
feeder_up_index = 2 
feeder_down_index = 0
angle_up_index = 7
angle_down_index = 7 
servo_index = 1
shoot_index = 10

executed = False

class MinimalSubscriber(Node):
	def __init__(self):
		super().__init__('minimal_subscriber')
		
		self.bot = RobotOneControls()
		
		self.msg = Joy()
		self.subscription = self.create_subscription(Joy, '/joy', self.listener_callback, 10)
		self.subscription  # prevent unused variable warning

		## experiment
		self.publisher_ = self.create_publisher(RobotOneControls, '/robot_1_controls', 10)
		timer_period = 0.01  # seconds
		self.timer = self.create_timer(timer_period, self.timer_callback)
		self.i = 0
				
	def listener_callback(self, msg):
		if (msg.buttons[4] == 1):
			self.bot.rotor = msg.buttons[rotor_index]
			self.bot.feeder_up = msg.buttons[feeder_up_index]
			self.bot.feeder_down = msg.buttons[feeder_down_index]
			
			if msg.buttons[servo_index] :
				time.sleep(1)
				self.bot.servo = 1
			else:
				self.bot.servo = 0	

			if(msg.axes[angle_up_index] == 1):
				self.bot.angle_up = 1
			else: 
				self.bot.angle_up = 0

			if(msg.axes[angle_down_index] == -1):	
				self.bot.angle_down = 1
			else:
				self.bot.angle_down = 0
				
		else:
			self.bot.servo = 0
			self.bot.angle_up = 0
			self.bot.angle_down = 0
			self.bot.rotor = 0
			self.bot.feeder_up = 0
			self.bot.feeder_down = 0

	def timer_callback(self):
		self.publisher_.publish(self.bot)
		self.i += 1	
	
def main(args=None):
	rclpy.init(args=args)
	
	minimal_subscriber = MinimalSubscriber()
	rclpy.spin(minimal_subscriber)
	minimal_subscriber.destroy_node()
	rclpy.shutdown()


if __name__ == '__main__':
	main()
		
