#include <iostream>
#include <vector>
#include <string>

using namespace std;

void lsdRadixSort(const vector<string>& arr, vector<int>& idx, int len) {
    int n = idx.size();
    if (n <= 1) return;
    
    vector<int> tempIdx(n);

    for (int d = len - 1; d >= 0; d--) {
        int count[256] = {0}; 
        
        for (int i = 0; i < n; i++) {
            count[(unsigned char)arr[idx[i]][d]]++;
        }
        
        for (int i = 1; i < 256; i++) {
            count[i] += count[i - 1];
        }
        
        for (int i = n - 1; i >= 0; i--) {
            tempIdx[--count[(unsigned char)arr[idx[i]][d]]] = idx[i];
        }
        
        idx.swap(tempIdx);
    }
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
        int bSize = buckets[len].size();
        if (bSize > 0) {
            vector<int> idx(bSize);
            for (int i = 0; i < bSize; i++) {
                idx[i] = i;
            }

            lsdRadixSort(buckets[len], idx, len);

            for (int i = 0; i < bSize; i++) {
                cout << buckets[len][idx[i]] << '\n';
            }
        }
    }

    return 0;
}
