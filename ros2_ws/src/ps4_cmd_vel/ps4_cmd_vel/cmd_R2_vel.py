from numpy import int32
import rclpy
from rclpy.node import Node

from std_msgs.msg import String
# from my_msgs.msg import Bull
from sensor_msgs.msg import Joy
from std_msgs.msg import Int32
from geometry_msgs.msg import Twist
from lagori_robot_msgs.msg import RobotOneControls

class MinimalSubscriber(Node):
	def __init__(self):
		super().__init__('robot_2')
		
		self.r1_cmd = Twist()
		
		self.msg = Joy()
		self.subscription = self.create_subscription(Joy, '/joy', self.listener_callback,10)
		self.subscription  # prevent unused variable warning

		## experiment
		self.publisher_ = self.create_publisher(Twist, '/robot_2/cmd_vel', 10)
		timer_period = 0.01  # seconds
		self.timer = self.create_timer(timer_period, self.timer_callback)
		self.i = 0
				
	def listener_callback(self, msg):
	  	
		if(msg.buttons[4] == 0):
			self.r1_cmd.linear.x = 2.0*msg.axes[4]
			self.r1_cmd.linear.y = 2.0*msg.axes[3]
			self.r1_cmd.linear.z = 0.0
			self.r1_cmd.angular.x = 0.0
			self.r1_cmd.angular.y = 0.0
			self.r1_cmd.angular.z = 0.9*msg.axes[0]
			
		else:
			self.r1_cmd.linear.x = 0.0
			self.r1_cmd.linear.y = 0.0
			self.r1_cmd.angular.z = 0.0
		
	def timer_callback(self):
		self.publisher_.publish(self.r1_cmd)
		self.i += 1	
	
def main(args=None):
	rclpy.init(args=args)
	
	robot_2 = MinimalSubscriber()
	rclpy.spin(robot_2)
	robot_2.destroy_node()
	rclpy.shutdown()


if __name__ == '__main__':
	main()
