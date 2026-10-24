using Printf

# ============================================================
# Mo hinh ngon ngu 2-tu (bigram): P(tu_sau | tu_truoc)
# ============================================================
const lm = Dict{String, Dict{String, Float64}}(
    "em" => Dict("hoc" => 0.52, "di" => 0.48),
    "hoc" => Dict("bai" => 0.40, "toan" => 0.35, "ve" => 0.25),
    "di" => Dict("cho" => 0.58, "boi" => 0.22, "ngu" => 0.20)
)

struct Candidate
    words::Vector{String}
    prob::Float64
end

# ============================================================
# 1. LIET KE TOAN BO: duyet het moi cau do dai 3 bat dau bang "em"
# ============================================================
function exhaustiveList()
    println("=== 1. LIET KE TOAN BO CAU (do dai 3, bat dau bang \"em\") ===")
    best_sentence = ""
    max_p = -1.0
    for (w2, p1) in lm["em"]
        for (w3, p2) in lm[w2]
            p = p1 * p2
            @printf("   em %s %s   | P = %.6f\n", w2, w3, p)
            if p > max_p
                max_p = p
                best_sentence = "em " * w2 * " " * w3
            end
        end
    end
    @printf("-> Cau tot nhat: \"%s\"  P = %.6f\n\n", best_sentence, max_p)
end

# ============================================================
# 2. GIAI MA THAM LAM: tai moi buoc chon tu co xac suat cao nhat
# ============================================================
function greedyDecode()
    println("=== 2. GIAI MA THAM LAM ===")
    curr = "em"
    seq = ["em"]
    prob = 1.0
    while haskey(lm, curr)
        next_w = ""
        max_prob = -1.0
        for (w, p) in lm[curr]
            if p > max_prob
                max_prob = p
                next_w = w
            end
        end
        push!(seq, next_w)
        prob *= max_prob
        curr = next_w
    end
    @printf("  \"%s\"  P = %.6f\n\n", join(seq, " "), prob)
end

# ============================================================
# 3. GIAI MA THEO CHUM (BEAM SEARCH) voi do rong k
# ============================================================
function beamSearch(k::Int)
    beam = [Candidate(["em"], 1.0)]
    
    for step in 1:2
        next_beam = Candidate[]
        for cand in beam
            last = cand.words[end]
            if !haskey(lm, last)
                continue
            end
            for (w, p) in lm[last]
                nc_words = copy(cand.words)
                push!(nc_words, w)
                push!(next_beam, Candidate(nc_words, cand.prob * p))
            end
        end
        
        sort!(next_beam, by = c -> c.prob, rev = true)
        if length(next_beam) > k
            next_beam = next_beam[1:k]
        end
        beam = next_beam
    end
    
    return argmax(c -> c.prob, beam)
end

function printBeam(k::Int)
    best = beamSearch(k)
    s = join(best.words, " ")
    @printf("=== 3. GIAI MA THEO CHUM, k = %d ===\n", k)
    @printf("  \"%s\"  P = %.6f\n\n", s, best.prob)
end

# ============================================================
# 4. VITERBI GAN NHAN TU LOAI + VET CAN 2^4 DE DOI CHIEU
# ============================================================
const words4 = ["em", "hoc", "bai", "toan"]
const states = ["N", "V"]
const pi_dist = Dict("N" => 0.6, "V" => 0.4)
const A = Dict(
    "N" => Dict("N" => 0.35, "V" => 0.65),
    "V" => Dict("N" => 0.70, "V" => 0.30)
)
const B = Dict(
    "N" => Dict("em" => 0.35, "hoc" => 0.10, "bai" => 0.40, "toan" => 0.30),
    "V" => Dict("em" => 0.05, "hoc" => 0.45, "bai" => 0.05, "toan" => 0.02)
)

function sequenceProb(tags::Vector{String})
    p = pi_dist[tags[1]] * B[tags[1]][words4[1]]
    for i in 2:length(tags)
        p *= A[tags[i-1]][tags[i]] * B[tags[i]][words4[i]]
    end
    return p
end

function viterbiAndBruteForce()
    n = length(words4)
    f = [Dict{String, Float64}() for _ in 1:n]
    bp = [Dict{String, String}() for _ in 1:n]

    for s in states
        f[1][s] = pi_dist[s] * B[s][words4[1]]
    end

    for i in 2:n
        for s in states
            max_val = -1.0
            best_p = ""
            for ps in states
                val = f[i-1][ps] * A[ps][s] * B[s][words4[i]]
                if val > max_val
                    max_val = val
                    best_p = ps
                end
            end
            f[i][s] = max_val
            bp[i][s] = best_p
        end
    end

    last_state = f[n]["N"] > f[n]["V"] ? "N" : "V"
    viterbi_prob = f[n][last_state]
    path = String[last_state]
    
    curr = last_state
    for i in n:-1:2
        curr = bp[i][curr]
        pushfirst!(path, curr)
    end

    println("=== 4a. VITERBI (quy hoach dong) ===")
    @printf("  Nhan: %s   | P = %.6f\n\n", join(path, "-"), viterbi_prob)

    println("=== 4b. VET CAN CA 2^4 = 16 DAY NHAN (doi chieu Viterbi) ===")
    best_brute_path = String[]
    best_brute_prob = -1.0

    for mask in 0:15
        tags = String[]
        for j in 0:3
            push!(tags, ((mask >> j) & 1) == 1 ? "V" : "N")
        end
        p = sequenceProb(tags)
        @printf("  %s   | P = %.6f\n", join(tags, "-"), p)
        if p > best_brute_prob
            best_brute_prob = p
            best_brute_path = tags
        end
    end

    @printf("\n  -> Day nhan tot nhat (vet can): %s   P = %.6f\n", join(best_brute_path, "-"), best_brute_prob)
    match = (best_brute_path == path)
    @printf("  -> Trung khop voi ket qua Viterbi? %s\n\n", match ? "CO (dung)" : "KHONG (co loi!)")
end

function main()
    exhaustiveList()
    greedyDecode()
    printBeam(1)
    printBeam(2)
    printBeam(3)
    viterbiAndBruteForce()
end

main()