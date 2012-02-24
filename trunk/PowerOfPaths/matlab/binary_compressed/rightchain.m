function [Q, T] = rightchain(size, rate)
%RIGHTCHAIN Summary of this function goes here
%   Detailed explanation goes here

	[S T C] = makestates(size);

    totalsize = 2^size;
    csize = length(S);
    Q = sparse(csize, csize);

    BITS = 2.^[0:size-1];
    
    for i=0:(totalsize-1)
        for b=1:size
		    j=bitxor(i, BITS(b));
		    if bitand(i, BITS(b))
				Q(T(i+1), T(j+1)) = Q(T(i+1), T(j+1))+1;
		    else
				r=rate;
				bt=b+1;
				while bitand(i, BITS(mod(bt-1, size)+1)) & (bt ~= (b))
				    bt=bt+1;
				    r = r + rate;
				end
				Q(T(i+1), T(j+1))=Q(T(i+1), T(j+1))+r;
	    	end
        end        
    end
    
    for i=1:csize
	%[i csize]
    	%t=0;
    	%for j=1:csize
    	%	t=t+Q(i,j);
    	%end
    	%Q(i,i) = -t;
	Q(i,i) = -sum(Q(i,:));
	Q(i,:) = Q(i,:)/C(i);
    end
    
end

