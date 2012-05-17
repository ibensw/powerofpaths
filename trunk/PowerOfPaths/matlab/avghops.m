function [ avg,distribution ] = avghops(Q, d)
%AVGHOPS Calculate average number of times a job is forwarded
%Parameters:
%	Q	The matrix representing a markov chain
%Optional:
%	d	Debug mode, default=1, disable debug output=0
%Return:
%	avg	The average number of forwards
%	distribution	The distribution for each possible outcome

	if nargin < 2
		d=1;
	end

	steady=full(ctmcsteadystate(Q));
	distribution=zeros(1,d);

	len=length(Q);
	states=log2(len);
	avg=0;
	total=0;

	for i=0:(states-1)
		c=0;
		prefix=((2^i)-1) * 2^(states-i);
		for j=0:(2^(states-i-1))-1
			c=c+steady(prefix + j + 1);
		end
		total=total+c;
		if d
			fprintf('%d hops:\t%f\n', i, c);
		end
		distribution(i+1)=c;
		avg=avg+(c*i);
	end

	loss=steady(len);
	avg=avg/(1-loss);
	if d
		fprintf('Loss:\t%f\nTotal:\t%f\nAverage #hops:\t%f\n', loss, total + loss, avg);
	end
end

