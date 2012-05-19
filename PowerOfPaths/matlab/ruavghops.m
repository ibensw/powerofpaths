function [ avg,avgp ] = ruavghops( Q, d )
%RUAVGHOPS Calculate average number of times a job is forwarded for the random unvisited chain
%Parameters:
%	Q	The matrix representing a markov chain using the random unvisited forwarding algorithm
%Optional:
%	d	Debug mode, default=1, disable debug output=0
%Return:
%	avg		The average number of times a job is forwarded
%	avgp	The distribution

	if nargin < 2
		d=1;
	end

	steady=ctmcsteadystate(Q);
	
	len=length(Q);
	
	avg = 0;
	avgp = zeros(len,1);
	
	for i=0:len-2
		tmpavg = 0;
		for h=0:i
			c = prod(i-h+1:i) * (len-1-i) / prod(len-1-h:len-1);
			tmpavg = tmpavg + (c * h);
			avgp(h+1) = avgp(h+1) + (c*steady(i+1));
		end
		avg=avg + steady(i+1) * tmpavg;
	end
	
	avgp(len) = steady(len);
	
	loss=steady(len);
	avg=avg/(1-loss);
	if d
		avgp
		fprintf('Loss:\t%f\nAverage #hops:\t%f\n', loss, avg);
	end
	
end

