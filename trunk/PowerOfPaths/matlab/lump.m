function [Ql S] = lump(Q)
%LUMP Summary of this function goes here
%   Detailed explanation goes here

	[S R C] = makestates(log2(length(Q)));

	Ql=sparse(length(S), length(S));

	[i j s] = find(Q);

	for x=1:length(i)
		%[i(x) j(x) s(x); R(i(x)) R(j(x)) 0; S(R(i(x))) S(R(j(x))) 0];
		Ql(R(i(x)),R(j(x)))=Ql(R(i(x)),R(j(x)))+s(x);
	end

	for x=1:length(S)
		Ql(x,:)=Ql(x,:)/C(x);
	end

end

