# Thông tin chung

- Môn học: Cấu trúc dữ liệu và giải thuật
- Thời gian: Học kỳ 2 năm học 2025-2026
- Thông tin nhóm:

| STT | MSSV     | Họ và tên          |
| --- | -------- | ------------------ |
| 1   | 24122012 | Lê Minh Quân       |
| 2   | 24122026 | Trần Hoàng Minh Vĩ |
| 3   | 24122042 | Huỳnh Tiến Mạnh    |

# A. Integer Sort

## A1. Benchmark 1

Thuật toán sử dụng là LSD Radix Sort kết hợp Counting Sort với cơ số $2^{16} = 65536$.
#### Các tối ưu chính

- Sử dụng radix sort thay vì comparison sort để đạt độ phức tạp $O(N)$.
- Chọn base $65536$ giúp giảm số pass từ 4 xuống còn 2 so với radix sort theo byte.
- Dùng phép XOR `x ^ 0x80000000` để ánh xạ miền signed integer sang unsigned integer, tránh xử lý số âm bằng `if`.
- Trích xuất digit bằng `>>` và  `&`, thay cho phép chia và modulo.
- Đảo pointer giữa hai buffer để tránh cấp phát lại bộ nhớ sau mỗi pass.

Phiên bản này đạt thời gian 46ms ở Benchmark 1 và 78ms ở Benchmark 2.

---

## A2. Sinh test case

Cách thức sinh test case đối kháng trong `test_gen.cpp` nhằm ép thuật toán của đối thủ rơi vào trường hợp xấu nhất (Worst-case), kích nổ lỗi quá thời gian (TLE) hoặc tràn RAM (MLE).

**Các thuật toán mục tiêu:**
- **QuickSort (Nhóm 7):** Thiếu phân hoạch 3 hướng, dễ suy biến với dữ liệu trùng lặp.
- **Merge Sort (Nhóm 5):** Lạm dụng cấp phát `vector` động trong đệ quy gây nghẽn RAM.
- **IntroSort (`std::sort`):** Thiếu tối ưu cho mảng có độ phân tán dữ liệu dị biệt.

**Chi tiết 5 test case làm chậm đối thủ:**
1. **`test001.in` (Nghịch thế tuyệt đối):** $10^5$ số giảm dần từ kịch trần. Ép QuickSort suy biến thành $O(N^2)$, gây TLE.
2. **`test002.in` (Đồng nhất):** $10^5$ phần tử giống hệt nhau (`424242`). Gây tràn Stack hoặc TLE cho QuickSort phân hoạch 2 hướng.
3. **`test003.in` (Ngẫu nhiên toàn dải):** Số ngẫu nhiên từ $-2^{31}$ đến $2^{31}-1$. Bắt Merge Sort gọi hàng triệu lệnh cấp phát vùng nhớ Heap, làm nghẽn hệ thống.
4. **`test004.in` (Zigzag biên cực đoan):** Số âm sát biên dưới đan xen số dương sát biên trên. Gây Cache Miss liên tục bẻ gãy Radix Sort.
5. **`test005.in` (Ít phần tử độc bản):** $10^5$ phần tử nhưng chỉ gồm 3 giá trị $\{-2^{31}, 0, 2^{31}-1\}$. Ép các hàm so sánh mặc định hoán vị vô ích.

---

## A3. Tối ưu Benchmark 2

Vấn đề hiện tại nằm ở thao tác nhập/xuất chuẩn của iostream, số lần duyệt mảng và chi phí sao chép dữ liệu cuối mỗi pass.

#### Các cải tiến

- Thay `cin/cout` bằng buffered I/O sử dụng `fread` và `fwrite`.
- Gộp việc đếm tần suất cho 16-bit thấp và 16-bit cao vào cùng một vòng lặp.
- Viết hai pass radix sort thay cho vòng `for(pass)` để loại bỏ overhead của loop control.
- Loại bỏ hoàn toàn bước copy mảng cuối cùng bằng cách sắp xếp trực tiếp quay về buffer gốc ở pass thứ hai.
- Thay `vector<int>` bằng raw array để tránh chi phí khởi tạo mặc định của STL container.

Sau tối ưu, thời gian thực thi giảm từ 78ms xuống còn khoảng 62ms.

---


# B. Lexicographic Sort

## B1. Benchmark 1

---

## B2. Sinh test case

## B2. Sinh test case

Dữ liệu chuỗi ($10 \le L \le 100$) mở ra lỗ hổng lớn về chi phí so sánh từ điển và chi phí sao chép vùng nhớ Heap (Deep Copy).

**Các thuật toán mục tiêu:**
- **So sánh mặc định (`std::sort`, `strcmp`):** Tốn $O(L)$ cho mỗi lần so sánh nếu các chuỗi có tiền tố giống nhau.
- **Radix Sort lỗi (Nhóm 10):** Khai báo mảng tạm thời bên trong vòng lặp quét ký tự.
- **Bucket Sort nông (Nhóm 4):** Phân xô dựa trên 2 ký tự đầu, mất tác dụng nếu mọi chuỗi bắt đầu giống hệt nhau.

**Chi tiết 5 test case làm chậm đối thủ:**
1. **`test001.in` (Ngẫu nhiên kịch trần $L=100$):** Đánh sập RAM của thuật toán có cơ chế sao chép chuỗi (Nhóm 5, 10).
2. **`test002.in` (Tiền tố trùng lặp siêu dài - Tăng dần):** $10^5$ chuỗi chung 95 ký tự đầu, khác 5 ký tự cuối. Đẩy chi phí của `std::sort` lên $O(95 \times N \log N)$, gây TLE.
3. **`test003.in` (Tiền tố trùng lặp - Giảm dần):** Đảo ngược test 002. Phá vỡ cài đặt Insertion Sort lai khi ép số lần dịch chuyển ký tự đạt cực đại.
4. **`test004.in` (Đồng nhất tuyệt đối):** $10^5$ chuỗi chứa toàn ký tự `"z"`. Dồn tất cả dữ liệu vào 1 xô duy nhất, vô hiệu hóa hoàn toàn thuật toán chia bucket của Nhóm 4.
5. **`test005.in` (Lệch nhịp Cache):** Đan xen chuỗi dài 100 và chuỗi ngắn 10 chung tiền tố `"aa"`. Gây nhiễu bộ đệm CPU khi con trỏ nhảy vùng nhớ không đồng đều.
## B3. Tối ưu Benchmark 2

---


# C. Length-aware Lexicographic Sort

## C1. Benchmark 1

Thuật toán cài đặt tốt nhất ở lần chạy đầu tiên: **Bucket Sort (Sắp xếp theo xô) kết hợp 3-way Radix Quicksort**.

**Các phương thức tối ưu hóa:**
* **Phân xô theo độ dài:** Dựa vào giới hạn độ dài ($10 \le L \le 100$), khởi tạo 101 xô tĩnh. Việc này đưa chi phí sắp xếp độ dài từ $O(N \log N)$ về $O(N)$.
* **3-way Radix Quicksort:** Áp dụng cho từng xô để phân mảng thành 3 khu vực (`<`, `==`, `>`) theo từng ký tự `d`.
* Dùng hàm `charAt` inline ép kiểu an toàn và thiết lập Fast I/O (`cin.tie`).

**Lý giải (Tại sao tốt nhất ở lần 1):** Phương pháp này loại bỏ hoàn toàn việc dùng hàm so sánh `<` cơ bản. 3-way Radix Quicksort cực kỳ vượt trội so với Quicksort truyền thống khi xử lý các chuỗi có nhiều tiền tố (prefix) giống nhau, giúp hệ thống không phải lặp lại việc so sánh các ký tự đã được phân loại đúng trước đó.

---

## C2. Sinh test case

---

## C3. Tối ưu Benchmark 2

Thuật toán cài đặt tốt nhất ở lần thứ hai: Vẫn duy trì kiến trúc **Bucket Sort kết hợp 3-way Radix Quicksort** từ Benchmark 1, nhưng tích hợp tối ưu **Move Semantics** và **hoán vị con trỏ (Pointer Swapping)**.

**Lý do nhóm tiếp tục giữ lại thuật toán của Benchmark 1 để xử lý các chuỗi cùng độ dài:**
* Thứ nhất, đảm bảo tính học thuật và tuân thủ ràng buộc của đồ án là không sử dụng các hàm sắp xếp lai có sẵn như `std::sort`.
* Thứ hai, 3-way Radix Quicksort mang tính chất phân hoạch theo từng ký tự độc lập (character-by-character) thay vì so sánh nguyên chuỗi. Khi đối mặt với các bộ test case ác ý chứa các chuỗi có tiền tố giống hệt nhau cực dài, thuật toán này sẽ gom cụm và bỏ qua các ký tự đã phân loại thành công, triệt tiêu hoàn toàn các phép so sánh thừa. Đặc tính này giúp thuật toán miễn nhiễm với bẫy tiền tố và hiệu quả hơn hẳn việc dùng các thuật toán Quicksort truyền thống.

**Phương thức tối ưu tiếp tục so với lần 1:**
* **Áp dụng Move Semantics (C++11):** Ở lần 1, thao tác nạp chuỗi vào phân xô `buckets[s.size()].push_back(s)` tạo ra hành vi Deep Copy (sao chép cấp phát động) gây tốn chi phí $O(L)$ với $L$ là chiều dài chuỗi. Ở lần 2, nâng cấp lệnh này thành `push_back(std::move(s))`. Cú pháp `move` giúp chuyển giao thẳng quyền sở hữu vùng nhớ thay vì sao chép từng ký tự, đưa chi phí phân xô về chuẩn $O(1)$.
* **Triệt tiêu thắt nút cổ chai ở hàm hoán vị (`swap`):** Hàm `swapStr` tự cài đặt ở lần 1 sử dụng biến tạm (`string t = a; a = b; b = t;`) bắt bộ nhớ Heap phải sao chép dữ liệu liên tục hàng triệu lần. Nhóm thay thế bằng hàm `std::swap` của C++. Vì bản chất `std::string` quản lý dữ liệu qua con trỏ, `std::swap` sẽ chỉ thực hiện đổi chéo 2 địa chỉ con trỏ ($O(1)$) thay vì bê nguyên nội dung chuỗi ($O(L)$), giúp cắt giảm hơn 60% thời gian chạy thực tế.
