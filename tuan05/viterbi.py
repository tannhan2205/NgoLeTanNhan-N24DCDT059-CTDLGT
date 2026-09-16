import itertools

# ============================================================
# Mo hinh ngon ngu 2-tu (bigram): P(tu_sau | tu_truoc)
# ============================================================
lm = {
    "em": {"hoc": 0.52, "di": 0.48},
    "hoc": {"bai": 0.40, "toan": 0.35, "ve": 0.25},
    "di": {"cho": 0.58, "boi": 0.22, "ngu": 0.20}
}

class Candidate:
    def __init__(self, words, prob):
        self.words = list(words)
        self.prob = prob

# ============================================================
# 1. LIET KE TOAN BO: duyet het moi cau do dai 3 bat dau bang "em"
# ============================================================
def exhaustive_list():
    print('=== 1. LIET KE TOAN BO CAU (do dai 3, bat dau bang "em") ===')
    best_sentence = ""
    max_p = -1.0
    for w2, p1 in lm["em"].items():
        for w3, p2 in lm[w2].items():
            p = p1 * p2
            print(f"   em {w2} {w3}   | P = {p:.6f}")
            if p > max_p:
                max_p = p
                best_sentence = f"em {w2} {w3}"
    print(f'-> Cau tot nhat: "{best_sentence}"  P = {max_p:.6f}\n')

# ============================================================
# 2. GIAI MA THAM LAM: tai moi buoc chon tu co xac suat cao nhat
# ============================================================
def greedy_decode():
    print("=== 2. GIAI MA THAM LAM ===")
    curr = "em"
    seq = ["em"]
    prob = 1.0
    while curr in lm:
        next_w, max_prob = max(lm[curr].items(), key=lambda x: x[1])
        seq.append(next_w)
        prob *= max_prob
        curr = next_w
    print(f'  "{" ".join(seq)}"  P = {prob:.6f}\n')

# ============================================================
# 3. GIAI MA THEO CHUM (BEAM SEARCH) voi do rong k
# ============================================================
def beam_search(k):
    beam = [Candidate(["em"], 1.0)]
    for step in range(2):
        next_beam = []
        for cand in beam:
            last = cand.words[-1]
            if last not in lm:
                continue
            for w, p in lm[last].items():
                nc = Candidate(cand.words + [w], cand.prob * p)
                next_beam.append(nc)
        next_beam.sort(key=lambda x: x.prob, reverse=True)
        if len(next_beam) > k:
            next_beam = next_beam[:k]
        beam = next_beam
    return max(beam, key=lambda x: x.prob)

def print_beam(k):
    best = beam_search(k)
    s = " ".join(best.words)
    print(f"=== 3. GIAI MA THEO CHUM, k = {k} ===")
    print(f'  "{s}"  P = {best.prob:.6f}\n')

# ============================================================
# 4. VITERBI GAN NHAN TU LOAI + VET CAN 2^4 DE DOI CHIEU
# ============================================================
words4 = ["em", "hoc", "bai", "toan"]
states = ["N", "V"]
pi = {"N": 0.6, "V": 0.4}
A = {
    "N": {"N": 0.35, "V": 0.65},
    "V": {"N": 0.70, "V": 0.30}
}
B = {
    "N": {"em": 0.35, "hoc": 0.10, "bai": 0.40, "toan": 0.30},
    "V": {"em": 0.05, "hoc": 0.45, "bai": 0.05, "toan": 0.02}
}

def sequence_prob(tags):
    p = pi[tags[0]] * B[tags[0]][words4[0]]
    for i in range(1, len(tags)):
        p *= A[tags[i-1]][tags[i]] * B[tags[i]][words4[i]]
    return p

def viterbi_and_brute_force():
    n = len(words4)
    f = [{} for _ in range(n)]
    bp = [{} for _ in range(n)]

    for s in states:
        f[0][s] = pi[s] * B[s][words4[0]]

    for i in range(1, n):
        for s in states:
            max_val = -1.0
            best_p = ""
            for ps in states:
                val = f[i-1][ps] * A[ps][s] * B[s][words4[i]]
                if val > max_val:
                    max_val = val
                    best_p = ps
            f[i][s] = max_val
            bp[i][s] = best_p

    last = "N" if f[n-1]["N"] > f[n-1]["V"] else "V"
    viterbi_prob = f[n-1][last]
    path = [last]
    for i in range(n - 1, 0, -1):
        last = bp[i][last]
        path.insert(0, last)

    print("=== 4a. VITERBI (quy hoach dong) ===")
    print(f"  Nhan: {'-'.join(path)}   | P = {viterbi_prob:.6f}\n")

    print("=== 4b. VET CAN CA 2^4 = 16 DAY NHAN (doi chieu Viterbi) ===")
    best_brute_path = []
    best_brute_prob = -1.0
    for mask in range(16):
        tags = ["V" if ((mask >> j) & 1) else "N" for j in range(4)]
        p = sequence_prob(tags)
        print(f"  {'-'.join(tags)}   | P = {p:.6f}")
        if p > best_brute_prob:
            best_brute_prob = p
            best_brute_path = tags

    print(f"\n  -> Day nhan tot nhat (vet can): {'-'.join(best_brute_path)}   P = {best_brute_prob:.6f}")
    match = (best_brute_path == path)
    print(f"  -> Trung khop voi ket qua Viterbi? {'CO (dung)' if match else 'KHONG (co loi!)'}\n")

if __name__ == "__main__":
    exhaustive_list()
    greedy_decode()
    print_beam(1)
    print_beam(2)
    print_beam(3)
    viterbi_and_brute_force()