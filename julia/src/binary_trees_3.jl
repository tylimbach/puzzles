struct Node{T}
	l::UInt32
	r::UInt32
	value::T
end

function make(depth::UInt, max_depth::UInt, index::Ref{UInt32}, nodes::Vector{Node{UInt32}})::Node
	if depth == max_depth
		node = Node(UInt32(0), UInt32(0), index[])
		nodes[index[]] = node
		index[] += 1
		return node
	end
		
	left::Node{UInt32} = make(depth + 1, max_depth, index, nodes)
	right::Node{UInt32} = make(depth + 1, max_depth, index, nodes)

	node = Node(left.value, right.value, index[])
	nodes[index[]] = node
	index[] += 1
	return node
end

function binary_trees(max_depth::UInt)::Vector{Node{UInt32}}
	buffer = Vector{Node{UInt32}}(undef, 2 ^ max_depth - 1)
	node = make(UInt(1), max_depth, Ref(UInt32(1)), buffer)
	return buffer
end


res = binary_trees(UInt(3))
println(res)
