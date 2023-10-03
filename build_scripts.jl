using Printf

function scan_code(r::AbstractString, dpath::AbstractString,
    postfix::Vector{<:AbstractString}=[".c", ".h"],
    exclude::Vector{<:AbstractString}=String[])
    fs = setdiff(readdir(joinpath(r, dpath)), exclude)
    res = String[]
    for f in fs
        if isfile(joinpath(r, dpath, f))
            for p in postfix
                if endswith(f, p)
                    push!(res, joinpath(dpath, f))
                end
            end
        end
    end
    for d in fs
        if isdir(joinpath(r, dpath, d))
            append!(res, scan_code(r, joinpath(dpath, d), postfix, exclude))
        end
    end
    return res
end

srcfiles = scan_code(pwd(), "", [".c", ".h"], ["cmake-build-debug", ".git", ".idea"])
srcfiles = abspath.(pwd(), srcfiles)
tags = map(x->splitext(x)[1], srcfiles) |> unique
ftypenum = zeros(Int, length(tags))
for i = eachindex(ftypenum)
    if (tags[i]*".c" in srcfiles) && (tags[i]*".h" in srcfiles)
        ftypenum[i] = 1
    end
    if (tags[i]*".c" in srcfiles) && !(tags[i]*".h" in srcfiles)
        ftypenum[i] = 2
    end
    if !(tags[i]*".c" in srcfiles) && (tags[i]*".h" in srcfiles)
        ftypenum[i] = 3
    end
end

function get_included_file(fpath::AbstractString)
    buffer = filter(startswith("#include"), readlines(fpath))
    bfiles1 = map(buffer) do l
        i = findfirst(c->(c=='<')||(c=='"'), collect(l))
        j = findlast(c->(c=='>')||(c=='"'), collect(l))
        abspath(splitdir(fpath)[1], String(l[i+1:j-1]))
    end
    return intersect(bfiles1, srcfiles)
end

include_files = Vector{Vector{String}}(undef, length(tags))
for i = eachindex(tags)
    if ftypenum[i] == 1
        include_files[i] = get_included_file(tags[i]*".h")
    elseif ftypenum[i] == 2
        include_files[i] = get_included_file(tags[i]*".c")
    elseif ftypenum[i] == 3
        include_files[i] = get_included_file(tags[i]*".h")
    end
end

include_tag_id = Vector{Vector{Int}}(undef, length(tags))
for i = eachindex(tags)
    include_tag_id[i] = Int[]
    for ic = include_files[i]
        _t = splitext(ic)[1]
        push!(include_tag_id[i], findfirst(==(_t), tags))
    end
end

update_flag = true
while update_flag
    global update_flag
    update_flag = false
    for i = eachindex(include_tag_id)
        tids = deepcopy(include_tag_id[i])
        for j = include_tag_id[i]
            append!(tids, include_tag_id[j])
        end
        unique!(tids)
        if length(tids) != length(include_tag_id[i])
            include_tag_id[i] = tids
            update_flag = true
            break
        end
    end
end

compile_range = zeros(Int, length(tags))
is_compiled = falses(length(tags))
i_compile = 1
while !all(is_compiled)
    global is_compiled, i_compile
    itag = findfirst(eachindex(include_tag_id)) do inc_id
        (!is_compiled[inc_id]) && all(is_compiled[include_tag_id[inc_id]])
    end
    compile_range[itag] = i_compile
    is_compiled[itag] = true
    i_compile += 1
end

CFLAG = "-g"

open("compile_script.sh", "w") do io
    println(io, "# compile")
    for i = sortperm(compile_range)
        if ftypenum[i] == 1
            @printf(io, "gcc -c %s %s.c -o %s.a\n", CFLAG, tags[i], tags[i])
        elseif ftypenum[i] == 2
            @printf(io, "gcc -c %s %s.c -o %s.o\n", CFLAG, tags[i], tags[i])
        end
    end
    println(io, "# link")
    for i = eachindex(tags)
        if ftypenum[i] == 2
            println(io, "gcc ", CFLAG, " \\")
            for j = include_tag_id[i]
                if ftypenum[j] == 1
                    println(io, "    ", tags[j]*".a \\")
                elseif ftypenum[j] == 3
                    println(io, "    ", tags[j]*".o \\")
                end
            end
            println(io, " -o ", tags[i])
        end
    end
end
