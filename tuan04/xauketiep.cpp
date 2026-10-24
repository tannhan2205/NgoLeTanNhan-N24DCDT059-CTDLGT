#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool xau_ke_tiep(vector<int> &x) {
    int i = (int)x.size() - 1;
    while (i >= 0 && x[i] == 1) { 
        x[i] = 0; 
        i--; 
    }   // quet tu phai sang
    if (i < 0) return false;                         // het: moi chu so deu la 1
    x[i] = 1;
    return true;
}

vector<string> liet_ke_xau(int n) {
    vector<int> x(n, 0);
    vector<string> ds;
    
    // Tối ưu: Cấp phát trước bộ nhớ cho 2^n phần tử
    if (n < 30) ds.reserve(1 << n);

    auto ghi = [&]{ 
        string s; 
        for (int v : x) s += char('0' + v); 
        ds.push_back(s); 
    };
    
    ghi();
    while (xau_ke_tiep(x)) ghi();
    return ds;
}

int main() {
    int n = 3; 
    vector<string> ket_qua = liet_ke_xau(n);

    for (const string &s : ket_qua) {
        cout << s << "\n";
    }
    return 0;
}