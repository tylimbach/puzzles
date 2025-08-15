struct Node
    l::Union{Node,Nothing}
    r::Union{Node,Nothing}
end

mutable struct Latch
    count::Int
    cond::Threads.Condition
end

function Latch(n::Int)::Latch
    Latch(n, Threads.Condition())
end

function countDown(latch::Latch)
    lock(latch.cond) do
        latch.count -= 1
        notify(latch.cond)
    end
end

function await(latch::Latch)
    lock(latch.cond)
    try
        while latch.count != 0
            wait(latch.cond)
        end
    finally
        unlock(latch.cond)
    end
end

function make(n::Int)::Node
    # Preallocate space for all nodes in the tree
    total_nodes = 2^(n + 1) - 1
    pool = Vector{Node}(undef, total_nodes)

    # Helper function to construct the tree in the array
    function build_tree(idx::Int, depth::Int)::Int
        if depth == 0
            pool[idx] = Node(nothing, nothing)
            return idx + 1
        else
            left_idx = build_tree(idx + 1, depth - 1)
            right_idx = build_tree(left_idx, depth - 1)
            pool[idx] = Node(pool[idx + 1], pool[left_idx])
            return right_idx
        end
    end

    # Build the tree starting from the root
    build_tree(1, n)
    return pool[1]  # Return the root node
end

function check(node::Node)::Int
    node.l === nothing ? 1 : 1 + check(node.l) + check(node.r)
end

function binary_trees(io, n::Int)
    write(io, "stretch tree of depth $(n+1)\t check: $(check(make(n+1)))\n")

    long_tree = make(n)

    minDepth = 4
    resultSize = trunc(Int, (n - minDepth) / 2) + 1
    results = Vector{String}(undef, resultSize)
    latch = Latch(resultSize)
	
    Threads.@threads for depth = minDepth:2:n
        local_c = 0
        niter = 1 << (n - depth + minDepth)

        # Thread-local aggregation
        Threads.@threads for _ = 1:niter
            local_c += check(make(depth))
        end

        index = trunc(Int, (depth - minDepth) / 2) + 1
        results[index] = "$niter\t trees of depth $depth\t check: $local_c\n"
        countDown(latch)
    end

    await(latch)
    for i in results
        write(io, i)
    end

    write(io, "long lived tree of depth $n\t check: $(check(long_tree))\n")
end

isinteractive() || binary_trees(stdout, parse(Int, ARGS[1]))
