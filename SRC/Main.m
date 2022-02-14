%File: Main.m
%Date: 2022-01-19
%Description: What should be the main file to run and get plots from the device.   
%Author: Andy Keats

MaxBufferSamp = 995;
AvgSampSize = 75;

Torque = zeros(1,10);
Time = zeros(1,10000);
AvgData = zeros(1,MaxBufferSamp); 


try
    ListOfPorts = serialportlist("available");
    arduinoObj = serialport("COM4",9600);
    configureTerminator(arduinoObj,"CR/LF");
    flush(arduinoObj);
catch
    disp("Already configured");
    flush(arduinoObj);
end
idx = 1;
while true
    data = readline(arduinoObj);

    Torque(idx) = data;
    %Time(idx) = clock;
    idx = idx + 1;
    disp(arduinoObj.NumBytesAvailable)
    
    subplot(2,1,1);
    plot(Torque, '-b');
    ylabel("ADC Value");
    xlabel("Samples");
    if (length(Torque) > MaxBufferSamp)
        %at max buffer size, shift data
        Torque = Torque(2:end);
        idx = length(Torque);
        AvgData(idx) = mean(Torque(MaxBufferSamp - AvgSampSize:end));
        subplot(2,1,2);
        plot(AvgData, 'r');
        AvgData = AvgData(2:end);
    end
        
end
