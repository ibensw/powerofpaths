function [ Q ] = rprimechain( size, rate )

	totalsize=2^size;
	rprimes=[];
	
	for i=1:(size-1)
		if gcd(size, i) == 1
			rprimes=[rprimes i];
		end
	end
	
	rpcount = length(rprimes);
	
	Q=zeros(totalsize);
	
	for i=0:totalsize-1
		tot=0;
		for j=0:size-1
			k=2^j;
			if bitand(i,k)
				Q(i+1, i-k+1) = 1.0;
				tot=tot+1.0;
			else
				c=0;
				for p=rprimes
					current=mod(j-p, size);
					while (bitand(i,2^current))
						current=mod(current-p, size);
						c=c+1;
					end
				end
				Q(i+1, i+k+1) = rate + c*rate/rpcount;
				tot=tot+Q(i+1, i+k+1);
			end
		end
		Q(i+1, i+1) = -tot;
	end

end

