function [Q] = rightchain(size, rate)
%RIGHTCHAIN Generate a Markov Chain that always forwards right
%Parameters:
%	size	The size of the ring
%	rate	The rate of arrivals

    totalsize = 2^size;
    Q = sparse(totalsize, totalsize);
    
    BITS = zeros(1, size);
    
    for i=1:size
        BITS(i) = 2^(i-1);
    end
    
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
		    r = r + rate;
		end
		Q(i+1, j+1)=r;
	    end
	    t=t + Q(i+1, j+1);
        end
	Q(i+1, i+1) = -t;
    end

end

