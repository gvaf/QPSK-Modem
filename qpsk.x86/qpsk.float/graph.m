% The Scatter plot from the C implementation
% 
% The C implementation produces a 'plot.txt' file 
% This matlab script reads this file and plots the
% result.
%

function graph()

fid = fopen('plot.txt', 'rt');

a = fscanf(fid, '%g %g', [2 inf]);
a = a'
%a = fromQ15(a)

It = a(:,1);
Qt = a(:,2);
fclose(fid);

scatterplot(It + i*Qt);
