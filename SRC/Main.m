%File: Main.m
%Date: 2022-01-19
%Description: What should be the main file to run and get plots from the device.   
%Author: Andy Keats

MaxBufferSamp = 195;
AvgSampSize = 125;

Torque = zeros(1,1);
Time = datetime('now');
AvgData = zeros(1,MaxBufferSamp); 
%subplot(2,1,1);
plot(Time, Torque, '-b');
ylabel("ADC Value");
xlabel("Time");
%subplot(2,1,2);
%plot(Time, AvgData, 'r');
%ylabel("ADC Value");
%xlabel("Time");


try
    ListOfPorts = serialportlist("available");
    arduinoObj = serialport("COM3",9600);
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
    %Time(idx) = datetime('now');
    idx = idx + 1;
    disp(arduinoObj.NumBytesAvailable)
    
    %subplot(2,1,1);
    %plot(Time, Torque, '-b');
    plot(Torque, '-b');
%    ylabel("ADC Value");
%    xlabel("Samples");
    if (length(Torque) > MaxBufferSamp)
        %max buffer size so shift data
        Torque = Torque(2:end);
        %Time = Time(2:end);
        idx = length(Torque);
%        AvgData(idx) = mean(Torque(MaxBufferSamp - AvgSampSize:end));
%        subplot(2,1,2);
%        plot(Time, AvgData, 'r');
%        AvgData = AvgData(2:end);
    end
end
