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
data = zeros(1,10000);
time = zeros(1,10000);
while true
    data(idx) = str2num(readline(arduinoObj));
    time(idx) = clock;

    plot(data,time, 'b', 'linewidth', 3);
    xlabel('Time');
    ylabel('Force (Nm)');
    idx = idx + 1;
end