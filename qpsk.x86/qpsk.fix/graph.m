% The Scatter plot from the C implementation
% 
% The C implementation produces a 'plot.txt' file 
% This matlab script reads this file and plots the
% result.
%

function graph()

fid = fopen('plot.txt', 'rt');

a = fscanf(fid, '%d %d', [2 inf]);
a = a'

It = a(:,1) / 2^15;
Qt = a(:,2) / 2^15;

fclose(fid);

scatterplot(It + i*Qt);
