function ros2msg = interfaces_msg_Object_1To2_Converter(message,ros2msg)
%interfaces_msg_Object_1To2_Converter passes data of ROS message to ROS 2 message.
% Copyright 2019 The MathWorks, Inc.
ros2msg.type = message.Type;
ros2msg.x = message.X;
ros2msg.y = message.Y;
end