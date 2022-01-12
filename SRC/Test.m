%File: Test.m
%Date: 2022-01-12
%Description: Testing to get data from the Bluno to MATLAB using the USB dongle.  
%Author: Andy Keats

try
    ListOfPorts = serialportlist("available");
    arduinoObj = serialport("COM3",9600);
    configureTerminator(arduinoObj,"CR/LF");
    flush(arduinoObj);
catch
    disp("Already configured");
end
idx = 0;
while true
    data = readline(arduinoObj);

    disp(data);
    disp(idx);
    idx = idx + 1;
end