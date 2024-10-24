#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <string>
#include <algorithm>  // for sort

using namespace std;

// 圖書資料結構
struct Book {
    string title;
    string author;
    string id;

    // 比較函式，用於依照圖書編號排序
    bool operator<(const Book& other) const {
        return id < other.id;
    }
};

// 借閱者資料結構
struct Borrower {
    string name;
    vector<string> borrowedBooks;
};

// 驗證圖書編號格式
bool validateBookID(const string& id) {
    if (id.size() != 5 || !isalpha(id[0])) return false;
    for (int i = 1; i < 5; ++i) {
        if (!isdigit(id[i])) return false;
    }
    return true;
}

// 圖書管理類別
class Library {
private:
    list<Book> books;  // 使用雙向鏈結串列來管理圖書

public:
    // 添加圖書
    void addBook() {
        string title, author, id;
        cout << "輸入書名: ";
        cin.ignore();
        getline(cin, title);
        cout << "輸入作者: ";
        getline(cin, author);
        cout << "輸入圖書編號 (格式: A1234): ";
        cin >> id;

        if (validateBookID(id)) {
            books.push_back({ title, author, id });
            cout << "圖書已添加: " << title << " (" << id << ")" << endl;
        }
        else {
            cout << "圖書編號不符合規範！請重新輸入。" << endl;
        }
    }

    // 刪除圖書
    void deleteBook() {
        string id;
        cout << "輸入要刪除的圖書編號: ";
        cin >> id;
        books.remove_if([&](const Book& book) { return book.id == id; });
        cout << "圖書編號 " << id << " 已刪除。" << endl;
    }

    // 搜尋圖書
    void searchBook() {
        string id;
        cout << "輸入要搜尋的圖書編號: ";
        cin >> id;
        for (const auto& book : books) {
            if (book.id == id) {
                cout << "找到圖書: " << book.title << " by " << book.author << " (ID: " << book.id << ")" << endl;
                return;
            }
        }
        cout << "未找到圖書編號 " << id << " 的圖書。" << endl;
    }

    // 依圖書編號排序
    void sortBooks() {
        books.sort();  // 使用圖書的<運算符重載來排序
        cout << "圖書已依圖書編號排序。" << endl;
    }

    // 列出所有圖書
    void listBooks() const {
        if (books.empty()) {
            cout << "目前沒有圖書。" << endl;
            return;
        }
        for (const auto& book : books) {
            cout << book.title << " by " << book.author << " (ID: " << book.id << ")" << endl;
        }
    }
};

// 借閱者管理類別
class BorrowerManager {
private:
    forward_list<Borrower> borrowers;  // 使用單向鏈結串列來管理借閱者

public:
    // 添加借閱者
    void addBorrower() {
        string name;
        int bookCount;
        cout << "輸入借閱者姓名: ";
        cin.ignore();
        getline(cin, name);
        cout << "輸入借閱的圖書數量: ";
        cin >> bookCount;

        vector<string> borrowedBooks;
        for (int i = 0; i < bookCount; ++i) {
            string bookID;
            cout << "輸入圖書編號 (格式: A1234): ";
            cin >> bookID;
            borrowedBooks.push_back(bookID);
        }
        borrowers.push_front({ name, borrowedBooks });
        cout << "借閱者 " << name << " 已添加。" << endl;
    }

    // 刪除借閱者
    void deleteBorrower() {
        string name;
        cout << "輸入要刪除的借閱者姓名: ";
        cin.ignore();
        getline(cin, name);
        borrowers.remove_if([&](const Borrower& borrower) { return borrower.name == name; });
        cout << "借閱者 " << name << " 已刪除。" << endl;
    }

    // 搜尋借閱者
    void searchBorrower() {
        string name;
        cout << "輸入要搜尋的借閱者姓名: ";
        cin.ignore();
        getline(cin, name);
        for (const auto& borrower : borrowers) {
            if (borrower.name == name) {
                cout << "找到借閱者: " << borrower.name << endl;
                cout << "借閱圖書: ";
                for (const auto& bookID : borrower.borrowedBooks) {
                    cout << bookID << " ";
                }
                cout << endl;
                return;
            }
        }
        cout << "未找到借閱者 " << name << "。" << endl;
    }

    // 列出所有借閱者及其借閱的圖書
    void listBorrowers() const {
        if (borrowers.empty()) {
            cout << "目前沒有借閱者。" << endl;
            return;
        }
        for (const auto& borrower : borrowers) {
            cout << borrower.name << " 借閱的圖書: ";
            for (const auto& bookID : borrower.borrowedBooks) {
                cout << bookID << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Library library;
    BorrowerManager borrowerManager;
    int choice;

    do {
        cout << "\n========== 圖書館管理系統 ==========\n";
        cout << "1. 添加新圖書\n";
        cout << "2. 刪除圖書\n";
        cout << "3. 搜尋圖書\n";
        cout << "4. 排序並列出所有圖書\n";
        cout << "5. 添加新借閱者\n";
        cout << "6. 刪除借閱者\n";
        cout << "7. 搜尋借閱者\n";
        cout << "8. 列出所有借閱者及其借閱的圖書\n";
        cout << "9. 離開\n";
        cout << "請選擇功能: ";
        cin >> choice;

        switch (choice) {
        case 1:
            library.addBook();
            break;
        case 2:
            library.deleteBook();
            break;
        case 3:
            library.searchBook();
            break;
        case 4:
            library.sortBooks();
            library.listBooks();
            break;
        case 5:
            borrowerManager.addBorrower();
            break;
        case 6:
            borrowerManager.deleteBorrower();
            break;
        case 7:
            borrowerManager.searchBorrower();
            break;
        case 8:
            borrowerManager.listBorrowers();
            break;
        case 9:
            cout << "系統結束。" << endl;
            break;
        default:
            cout << "無效選擇，請重新選擇。" << endl;
        }
    } while (choice != 9);

    return 0;
}
