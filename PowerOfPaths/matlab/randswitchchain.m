function [Q] = randswitchchain(size, rate, p)
%RANDSWITCHCHAIN Generates a Markov Chain that randomly forward left or right
%Parameters:
%	size	The size of the Markov Chain
%	rate	The rate of arrivals
%	p		The probability a job is forwarded right
%			(Default: 0.5)	

	if nargin < 3
		p=0.5;
	end

    totalsize = 2^size;
    Q = sparse(totalsize, totalsize);
    
    BITS = 2.^[0:size-1];

    for i=0:(totalsize-1)
	t=0;
        for b=1:size
	    j=bitxor(i, BITS(b));
	    if bitand(i, BITS(b))
		Q(i+1, j+1)=1;
	    else
		r=rate;
		bt=b+1;
		while bitand(i, BITS(mod(bt-1, size)+1)) & (bt ~= (b))
		    bt=bt+1;
		    r = r + rate*p;
		end
		bt=b-1;
		while bitand(i, BITS(mod(bt-1, size)+1)) & (bt ~= (b))
		    bt=bt-1;
		    r = r + rate*(1-p);
		end
		Q(i+1, j+1)=r;
	    end
	    t=t + Q(i+1, j+1);
        end
	Q(i+1, i+1) = -t;
    end

end

