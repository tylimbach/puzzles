function fibonacci(n::Int)::BigInt
	memo1 = 1
	memo2 = 0
	for _ in 1:n-1
		temp = memo2
		memo2 = memo1
		memo1 = memo2 + temp
	end

	return memo1
end

isinteractive() || fibonacci(parse(Int, ARGS[1]))
