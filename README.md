# Thông tin chung

- Môn học: Cấu trúc dữ liệu và giải thuật
- Thời gian: Học kỳ 2 năm học 2025-2026
- Thông tin nhóm:

| STT | MSSV     | Họ và tên          |
| --- | -------- | ------------------ |
| 1   | 24122012 | Lê Minh Quân       |
| 2   |          | Trần Hoàng Minh Vĩ |
| 3   |          | Huỳnh Tiến Mạnh    |

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

<!-- Đây là comment. Cách thức sinh test case được cài đặt trong test_gen.cpp, các thuật toán mục tiêu mà bộ test này được sinh ra để tăng thời gian chạy, giải thích lý do chọn các thuật toán mục tiêu này cùng việc tại sao các test trên giúp tăng thời gian chạy của chúng. -->

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

---

## B3. Tối ưu Benchmark 2

---


# C. Length-aware Lexicographic Sort

## C1. Benchmark 1

---

## C2. Sinh test case

---

## C3. Tối ưu Benchmark 2
