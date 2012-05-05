function [ Q ] = runvisitedchain( size, rate )
%RUNVISITEDCHAIN Generate a Markov Chain that forwards to an unvisited node

	rate = rate*size;

	Q = sparse(size+1, size+1);
	
	Q(1,2) = rate;
	Q(1,1) = -rate;
	
	Q(size+1, size) = size;
	Q(size+1, size+1) = -size;
	
	for i=2:size
		Q(i,i-1) = i-1;
		Q(i,i+1) = rate;
		Q(i,i) = -Q(i,i+1)-Q(i,i-1);
	end

end

