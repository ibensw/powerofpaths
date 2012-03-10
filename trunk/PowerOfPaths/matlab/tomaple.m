function [ Q ] = tomaple(Q)
%Lambda MUST be 100, p MUST be 0.1

	[height width]=size(Q);
	fprintf('Q:=Matrix(%i,%i,[',height, width);

	for i=1:height
		fprintf('[');
		for j=1:width
			if j < i
				fprintf('%i', Q(i,j));
			end
			if j > i
				v=Q(i,j);
				l=floor(v/100);
				m=mod(v, 100);
				p=m/10;
				if Q(i,j)==0
					fprintf('0');
				else
					if p==0
						fprintf('%i*l', l);
					else
						fprintf('(%i+%i*p)*l', l, p);
					end
				end
			end
			if j == i
				v=-Q(i,j);
				fprintf('-%i*l-%i', floor(v/100), mod(v, 100));
			end

			if j<width
				fprintf(',');
			end
		end
		fprintf(']');
		if i<height
			fprintf(',');
		end
	end

	fprintf('])');

end

