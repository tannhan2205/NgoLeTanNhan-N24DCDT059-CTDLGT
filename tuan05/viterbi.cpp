#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

// ============================================================
// Mo hinh ngon ngu 2-tu (bigram): P(tu_sau | tu_truoc)
// ============================================================
map<string, map<string, double>> lm = {
    {"em",  {{"hoc", 0.52}, {"di", 0.48}}},
    {"hoc", {{"bai", 0.40}, {"toan", 0.35}, {"ve", 0.25}}},
    {"di",  {{"cho", 0.58}, {"boi", 0.22}, {"ngu", 0.20}}}
};

struct Candidate {
    vector<string> words;
    double prob;
};

// ============================================================
// 1. LIET KE TOAN BO: duyet het moi cau do dai 3 bat dau bang "em"
// ============================================================
void exhaustiveList() {
    cout << "=== 1. LIET KE TOAN BO CAU (do dai 3, bat dau bang \"em\") ===\n";
    string best_sentence;
    double max_p = -1;
    for (auto const& [w2, p1] : lm["em"]) {
        for (auto const& [w3, p2] : lm[w2]) {
            double p = p1 * p2;
            cout << "  em " << w2 << " " << w3 << "  | P = " << p << "\n";
            if (p > max_p) { max_p = p; best_sentence = "em " + w2 + " " + w3; }
        }
    }
    cout << "-> Cau tot nhat: \"" << best_sentence << "\"  P = " << max_p << "\n\n";
}

// ============================================================
// 2. GIAI MA THAM LAM: tai moi buoc chon tu co xac suat cao nhat
// ============================================================
void greedyDecode() {
    cout << "=== 2. GIAI MA THAM LAM ===\n";
    string curr = "em";
    string seq = "em";
    double prob = 1.0;
    while (lm.count(curr)) {
        string next_w;
        double max_prob = -1;
        for (auto const& [w, p] : lm[curr]) {
            if (p > max_prob) { max_prob = p; next_w = w; }
        }
        seq += " " + next_w;
        prob *= max_prob;
        curr = next_w;
    }
    cout << "  \"" << seq << "\"  P = " << prob << "\n\n";
}

// ============================================================
// 3. GIAI MA THEO CHUM (BEAM SEARCH) voi do rong k
// Cau co do dai co dinh = 3 tu, bat dau bang "em"
// ============================================================
Candidate beamSearch(int k) {
    vector<Candidate> beam = { { {"em"}, 1.0 } };

    // mo rong 2 buoc de duoc cau 3 tu
    for (int step = 0; step < 2; step++) {
        vector<Candidate> next_beam;
        for (auto const& cand : beam) {
            string last = cand.words.back();
            if (!lm.count(last)) continue; // khong con tu tiep theo
            for (auto const& [w, p] : lm[last]) {
                Candidate nc = cand;
                nc.words.push_back(w);
                nc.prob *= p;
                next_beam.push_back(nc);
            }
        }
        // sap xep giam dan theo xac suat, giu lai top-k
        sort(next_beam.begin(), next_beam.end(),
             [](const Candidate& a, const Candidate& b) { return a.prob > b.prob; });
        if ((int)next_beam.size() > k) next_beam.resize(k);
        beam = next_beam;
    }

    // tra ve ung vien tot nhat trong chum cuoi
    return *max_element(beam.begin(), beam.end(),
             [](const Candidate& a, const Candidate& b) { return a.prob < b.prob; });
}

void printBeam(int k) {
    Candidate best = beamSearch(k);
    string s;
    for (size_t i = 0; i < best.words.size(); i++) s += (i ? " " : "") + best.words[i];
    cout << "=== 3. GIAI MA THEO CHUM, k = " << k << " ===\n";
    cout << "  \"" << s << "\"  P = " << best.prob << "\n\n";
}

// ============================================================
// 4. VITERBI GAN NHAN TU LOAI + VET CAN 2^4 DE DOI CHIEU
// ============================================================
vector<string> words4 = {"em", "hoc", "bai", "toan"};
vector<string> states  = {"N", "V"};
map<string, double> pi = {{"N", 0.6}, {"V", 0.4}};
map<string, map<string, double>> A = {
    {"N", {{"N", 0.35}, {"V", 0.65}}},
    {"V", {{"N", 0.70}, {"V", 0.30}}}
};
map<string, map<string, double>> B = {
    {"N", {{"em", 0.35}, {"hoc", 0.10}, {"bai", 0.40}, {"toan", 0.30}}},
    {"V", {{"em", 0.05}, {"hoc", 0.45}, {"bai", 0.05}, {"toan", 0.02}}}
};

double sequenceProb(const vector<string>& tags) {
    double p = pi[tags[0]] * B[tags[0]][words4[0]];
    for (size_t i = 1; i < tags.size(); i++) {
        p *= A[tags[i-1]][tags[i]] * B[tags[i]][words4[i]];
    }
    return p;
}

void viterbiAndBruteForce() {
    int n = words4.size();
    vector<map<string, double>> f(n);
    vector<map<string, string>> bp(n);

    for (string s : states) f[0][s] = pi[s] * B[s][words4[0]];

    for (int i = 1; i < n; i++) {
        for (string s : states) {
            double max_val = -1;
            string best_p;
            for (string ps : states) {
                double val = f[i-1][ps] * A[ps][s] * B[s][words4[i]];
                if (val > max_val) { max_val = val; best_p = ps; }
            }
            f[i][s] = max_val;
            bp[i][s] = best_p;
        }
    }

    string last = (f[n-1]["N"] > f[n-1]["V"]) ? "N" : "V";
    double viterbi_prob = f[n-1][last];
    vector<string> path = {last};
    for (int i = n - 1; i >= 1; i--) {
        last = bp[i][last];
        path.insert(path.begin(), last);
    }

    cout << "=== 4a. VITERBI (quy hoach dong) ===\n";
    cout << "  Nhan: ";
    for (size_t i = 0; i < path.size(); i++) cout << path[i] << (i + 1 < path.size() ? "-" : "");
    cout << "  | P = " << viterbi_prob << "\n\n";

    // Vet can toan bo 2^4 = 16 day nhan de doi chieu
    cout << "=== 4b. VET CAN CA 2^4 = 16 DAY NHAN (doi chieu Viterbi) ===\n";
    vector<string> best_brute_path;
    double best_brute_prob = -1;
    for (int mask = 0; mask < 16; mask++) {
        vector<string> tags(4);
        for (int j = 0; j < 4; j++) {
            // bit j: 0 = N, 1 = V  (j=0 la tu dau tien)
            tags[j] = ((mask >> j) & 1) ? "V" : "N";
        }
        double p = sequenceProb(tags);
        cout << "  ";
        for (size_t i = 0; i < tags.size(); i++) cout << tags[i] << (i + 1 < tags.size() ? "-" : "");
        cout << "  | P = " << p << "\n";
        if (p > best_brute_prob) { best_brute_prob = p; best_brute_path = tags; }
    }

    cout << "\n  -> Day nhan tot nhat (vet can): ";
    for (size_t i = 0; i < best_brute_path.size(); i++)
        cout << best_brute_path[i] << (i + 1 < best_brute_path.size() ? "-" : "");
    cout << "  P = " << best_brute_prob << "\n";

    bool match = (best_brute_path == path);
    cout << "  -> Trung khop voi ket qua Viterbi? " << (match ? "CO (dung)" : "KHONG (co loi!)") << "\n\n";
}

// ============================================================
int main() {
    cout << fixed << setprecision(6);

    exhaustiveList();
    greedyDecode();
    printBeam(1);
    printBeam(2);
    printBeam(3);
    viterbiAndBruteForce();

    return 0;
}