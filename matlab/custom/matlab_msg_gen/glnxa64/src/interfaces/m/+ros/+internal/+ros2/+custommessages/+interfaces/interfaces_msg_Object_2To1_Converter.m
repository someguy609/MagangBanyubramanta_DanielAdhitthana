function ros1msg = interfaces_msg_Object_2To1_Converter(message,ros1msg)
%interfaces_msg_Object_2To1_Converter passes data of ROS 2 message to ROS message.
% Copyright 2019 The MathWorks, Inc.    
ros1msg.Type = message.type;
ros1msg.X = message.x;
ros1msg.Y = message.y;
end