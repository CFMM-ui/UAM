
clear, clc, close all

folder = 'Data Inspection\m=0.25';

vidread = VideoReader(strcat(folder, '\0_25kg.mp4'));

numFrames = vidread.NumFrames;
tf = 200;
ratio = tf/numFrames;

vidwrite = VideoWriter('video');
vidWrite.FileFormat = 'mp4';
vidwrite.Quality = 100;
open(vidwrite);

for i = 1:1:numFrames
    frame = read(vidread, i);
    ti = round(ratio*(i-1),2);
    frame = insertText(frame, [50 100], strcat('t = ', string(ti)), ...
           FontSize=30, TextColor="black", BoxColor='w');
    imshow(frame)
    writeVideo(vidwrite, frame);
end
i = numFrames;
frame = read(vidread, i);
ti = round(ratio*i,2);
frame = insertText(frame, [50 100], strcat('t = ', string(ti)), ...
       FontSize=30, TextColor="black", BoxColor='w');
imshow(frame)
writeVideo(vidwrite, frame);
close(vidwrite);

