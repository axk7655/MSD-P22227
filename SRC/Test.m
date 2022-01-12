%File: Test.m
%Date: 2022-01-12
%Description: Testing to get data from the Bluno to MATLAB using the USB dongle.  
%Author: Andy Keats

ListOfPorts = serialportlist("available");
arduinoObj = serialport("COM3",9600);
configureTerminator(arduinoObj,"CR/LF");
flush(arduinoObj);

while true
    data = readline(arduinoObj);

    disp(data);
end