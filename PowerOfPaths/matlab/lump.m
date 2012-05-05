function [Ql S] = lump(Q)
%LUMP Lump a matrix representing a Markov Chain
%   The states of the matrix Q must represent the availability of the the servers

	[S R C] = makestates(log2(length(Q)));

	Ql=sparse(length(S), length(S));

	[i j s] = find(Q);

	for x=1:length(i)
		Ql(R(i(x)),R(j(x)))=Ql(R(i(x)),R(j(x)))+s(x);
	end

	for x=1:length(S)
		Ql(x,:)=Ql(x,:)/C(x);
	end

end

