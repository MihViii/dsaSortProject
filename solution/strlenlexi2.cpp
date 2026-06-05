#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

inline int charAt(const string &s, int d) {
    if (d < (int)s.size()) 
        return (unsigned char)s[d];
    return -1;
}

void quicksort(vector<string> &a, int lo, int hi, int d) {
    if (hi <= lo) return;

    int mid = lo + (hi - lo) / 2;
    swap(a[lo], a[mid]);

    int lt = lo, gt = hi;
    int v = charAt(a[lo], d);
    int i = lo + 1;

    while (i <= gt) {
        int t = charAt(a[i], d);
        if (t < v) 
            swap(a[lt++], a[i++]);
        else if (t > v) 
            swap(a[i], a[gt--]);
        else i++;
    }

    quicksort(a, lo, lt - 1, d);
    if (v >= 0) 
        quicksort(a, lt, gt, d + 1);
    quicksort(a, gt + 1, hi, d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<string>> buckets(101);

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        buckets[s.size()].push_back(move(s));
    }

    cout << n << '\n';

    for (int len = 10; len <= 100; len++) {
        if (!buckets[len].empty()) {
            quicksort(buckets[len], 0, (int)buckets[len].size() - 1, 0);

            for (const string &s : buckets[len]) {
                cout << s << '\n';
            }
        }
    }

    return 0;
}
