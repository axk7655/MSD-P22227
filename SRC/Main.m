%File: Main.m
%Date: 2022-01-19
%Description: What should be the main file to run and get plots from the device.   
%Author: Andy Keats

Torque = zeros(1,10000);
Time = zeros(1,10000);


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

    Torque(idx) = data;
    Time(idx) = clock;
    idx = idx + 1;
    
    plot(Torque, Time);
    drawnow
    
end

%%
