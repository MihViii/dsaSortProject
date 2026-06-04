#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Hàm so sánh custom theo đúng 2 tiêu chí của đề bài
bool cmp(const string& a, const string& b) {
    if (a.length() != b.length()) {
        return a.length() < b.length(); // 1. So sánh độ dài trước
    }
    return a < b; // 2. Nếu độ dài bằng nhau, so sánh theo từ điển
}

int main() {
    // Tối ưu I/O để đua rank thời gian
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<string> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    // std::sort kết hợp custom cmp là an toàn tuyệt đối cho mọi test case
    sort(arr.begin(), arr.end(), cmp);
    
    cout << n << "\n";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << "\n";
    }
    
    return 0;
}
