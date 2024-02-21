function slBusOut = Object(msgIn, slBusOut, varargin)
%#codegen
%   Copyright 2021-2022 The MathWorks, Inc.
    slBusOut.color = uint8(msgIn.color);
    slBusOut.x = int32(msgIn.x);
    slBusOut.y = int32(msgIn.y);
    slBusOut.angle = single(msgIn.angle);
end
