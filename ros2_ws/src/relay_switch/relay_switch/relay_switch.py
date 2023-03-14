#/usr/lib/python3/dist-packages 
from numpy import int32
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy

import  RPi.GPIO as GPIO
PI_PIN = 10
GPIO.setmode(GPIO.BOARD)
GPIO.setup(PI_PIN, GPIO.OUT)

button_index = 9
class MinimalSubscriber(Node):
    def __init__(self):
        super().__init__('minimal_subscriber')

        self.msg = Joy()
        self.subscription = self.create_subscription(Joy, '/joy', self.listener_callback, 10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        if (msg.buttons[button_index] == 1):
            GPIO.setmode(GPIO.BOARD)
            GPIO.setup(PI_PIN, GPIO.OUT)
            GPIO.output(PI_PIN, GPIO.LOW)
            GPIO.cleanup()
            print("Pin high")
            #pin high
        else:
            GPIO.setmode(GPIO.BOARD)
            GPIO.setup(PI_PIN, GPIO.OUT)
            GPIO.output(PI_PIN, GPIO.HIGH)
            GPIO.cleanup()
            print("pin low")
            #pin low   


def main(args=None):
    rclpy.init(args=args)

    robot_2 = MinimalSubscriber()
    rclpy.spin(robot_2)
    robot_2.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

