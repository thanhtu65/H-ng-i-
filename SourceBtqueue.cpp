#include<iostream>
#include <queue>
#include <string>
using namespace std;

// Khai báo cấu trúc node cho hàng đợi
struct Node {
    string tenKhachHang; // Tên khách hàng
    string tenSanPham;   // Tên sản phẩm
    int soLuong;         // Số lượng sản phẩm
    float giaTien;       // Giá tiền của một sản phẩm
    Node* next;          // Con trỏ đến node tiếp theo
};

// Khai báo cấu trúc hàng đợi
struct Queue {
    Node* front; // Phần tử đầu hàng đợi
    Node* rear;  // Phần tử cuối hàng đợi
};

// Khởi tạo hàng đợi rỗng
void initQueue(Queue* queue) {
    queue->front = nullptr;
    queue->rear = nullptr;
}

// Kiểm tra hàng đợi có rỗng không
bool isEmpty(Queue* queue) {
    return queue->front == nullptr;
}

// Thêm một giỏ hàng (node) vào hàng đợi
void enqueue(Queue* queue, string tenKhachHang, string tenSanPham, int soLuong, float giaTien) {
    Node* newNode = new Node;
    newNode->tenKhachHang = tenKhachHang;
    newNode->tenSanPham = tenSanPham;
    newNode->soLuong = soLuong;
    newNode->giaTien = giaTien;
    newNode->next = nullptr;

    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Xóa một giỏ hàng (node) khỏi hàng đợi sau khi thanh toán xong
Node* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        cout << "Hang doi rong!" << endl;
        return nullptr;
    }

    Node* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == nullptr) { // Nếu hàng đợi trở thành rỗng
        queue->rear = nullptr;
    }

    return temp;
}

// Tính tổng số tiền thu được tại quầy
float tinhTongTien(Queue* queue) {
    float tongTien = 0;
    Node* current = queue->front;

    while (current != nullptr) {
        tongTien += current->soLuong * current->giaTien;
        current = current->next;
    }

    return tongTien;
}

// Đếm số lượng một sản phẩm A đã được bán
int demSanPham(Queue* queue, string tenSanPham) {
    int soLuong = 0;
    Node* current = queue->front;

    while (current != nullptr) {
        if (current->tenSanPham == tenSanPham) {
            soLuong += current->soLuong;
        }
        current = current->next;
    }

    return soLuong;
}

// Hiển thị danh sách các giỏ hàng trong hàng đợi
void printQueue(Queue* queue) {
    Node* current = queue->front;

    if (isEmpty(queue)) {
        cout << "Hang doi rong!" << endl;
        return;
    }

    cout << "Danh sach cac gio hang trong hang doi:" << endl;
    while (current != nullptr) {
        cout << "Ten khach hang: " << current->tenKhachHang << endl;
        cout << "San pham: " << current->tenSanPham << endl;
        cout << "So luong: " << current->soLuong << endl;
        cout << "Gia tien: " << current->giaTien << " VND" << endl;
        cout << endl;
        current = current->next;
    }
}

int main() {
    Queue queue;
    initQueue(&queue);

    int n;
    cout << "Nhap so luong khach hang trong hang doi: ";
    cin >> n;

    // Nhập thông tin từng khách hàng
    for (int i = 0; i < n; i++) {
        string tenKhachHang, tenSanPham;
        int soLuong;
        float giaTien;

        cout << "Nhap thong tin cho khach hang thu " << i + 1 << ":" << endl;
        cin.ignore(); // Loại bỏ ký tự xuống dòng
        cout << "Ten khach hang: ";
        getline(cin, tenKhachHang);
        cout << "Ten san pham: ";
        getline(cin, tenSanPham);
        cout << "So luong: ";
        cin >> soLuong;
        cout << "Gia tien: ";
        cin >> giaTien;

        enqueue(&queue, tenKhachHang, tenSanPham, soLuong, giaTien);
    }
    // Hiển thị danh sách giỏ hàng
    cout << "Danh sach gio hang trong hang doi" << endl;
    printQueue(&queue);


    // Tính tổng số tiền thu được tại quầy trước khi xóa hàng đợi
    float tongTien = tinhTongTien(&queue);
    cout << "\nTong so tien thu duoc tai quay: " << tongTien << " VND" << endl;

    // Đếm số lượng một sản phẩm A đã bán trước khi xóa hàng đợi
    string tenSanPhamCanDem;
    cout << "\nNhap ten san pham can dem: ";
    cin.ignore();
    getline(cin, tenSanPhamCanDem);
    int soLuongSanPham = demSanPham(&queue, tenSanPhamCanDem);
    cout << "So luong san pham \"" << tenSanPhamCanDem << "\" da ban: " << soLuongSanPham << endl;

    // Thực hiện thanh toán cho từng khách hàng
    cout << "\nBat dau thanh toan..." << endl;
    while (!isEmpty(&queue)) {
        Node* processedNode = dequeue(&queue);
        cout << "Da thanh toan cho khach hang: " << processedNode->tenKhachHang << endl;
        delete processedNode; // Giải phóng bộ nhớ của node đã xử lý
    }

    return 0;
}
