# c-basic

Kho lưu trữ 

## Cấu trúc thư mục

- `tomaudothi.c`: Chương trình tô màu đồ thị bằng BFS kết hợp tô màu tham lam và xuất đồ thị đã tô màu ra file `.dot` (tương thích Graphviz).
- `README.md`: Tài liệu mô tả repository và hướng dẫn sử dụng.

## Hướng dẫn chạy `tomaudothi.c`

1. Chuẩn bị file đầu vào `dothi.txt` cùng thư mục chạy chương trình (nếu không có file, chương trình sẽ báo lỗi mở file):
   - Dòng đầu gồm hai số nguyên `n` và `m` (số đỉnh và số cạnh).
   - `m` dòng tiếp theo, mỗi dòng gồm hai số nguyên `u` và `v` biểu diễn một cạnh nối giữa đỉnh `u` và đỉnh `v`.
2. Biên dịch và chạy file `tomaudothi.c` bằng Code::Blocks hoặc trình biên dịch `gcc`:

   ```bash
   gcc tomaudothi.c -o tomaudothi
   ./tomaudothi
