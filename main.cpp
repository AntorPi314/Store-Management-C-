#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
string page_id="";
int page_width=30;
void addSpace(string *str, int n);
string getDate();
void setColor(int fgColor, int bgColor);
void PageShow(string id, string str, int size);
void PageControl(string page_id);
void PageReset();

void addSpace(string *str, int n) {
    int add = n - str->length();
    for(int j=1; j<=add; j++) {
        *str = *str + " ";
    }
}

string getDate() {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
    return buffer;
}

void setColor(int foreground, int background) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorCode = foreground + (background << 4);
    SetConsoleTextAttribute(hConsole, colorCode);
}

class Product {
public:
    string name, price, addedDate;
    int space=20;

    Product(string n, string p, string d) : name(n), price(p), addedDate(d) {}

    void Display() const {
        cout << setw(20) << left << name;
        cout << setw(10) << left << price;
        cout << setw(11) << left << addedDate <<endl;
    }
};

class ProductManager {
private:
    vector<Product> products;
    string fileName="products.txt";
public:
    void AddProduct() {
        string name, price;
        cout << " Product Name: ";
        cin >> name;
        cout << " Product Price: ";
        cin >> price;
        Product product(name, price, getDate());
        products.push_back(product);
        cout << " Product Added Successfully!" << endl;
        SaveToFile();
    }
    void UpdateProduct() {
        int index;
        cout << " Enter Index to update: ";
        cin >> index;
        if (index >= 0 && index < products.size()) {
            cout << " Updated Product Name: ";
            cin >> products[index].name;
            cout << " Updated Product Price: ";
            cin >> products[index].price;
            cout << " Product Updated Successfully!" << endl;
            SaveToFile();
        } else {
            cout << " Invalid Index! " << index << endl;
        }
    }
    void DeleteProduct() {
        int index;
        cout << " Enter Index to Delete: ";
        cin >> index;
        if (index >= 0 && index < products.size()) {
            products.erase(products.begin() + index);
            cout << " Product Deleted Successfully!" << endl;
            SaveToFile();
        } else {
            cout << " Invalid Index! " << index << endl;
        }
    }
    void ShowAllProducts() {
        if (products.empty()) {
            cout << "\n No Products to Display.\n" << endl;
        } else {
            setColor(15, 1);
            cout <<"\n "<< setw(10) << left << "Index";
            cout << setw(20) << left << "Product";
            cout << setw(10) << left << "Price";
            cout << setw(11) << left << "Date"<<endl;
            for (size_t i = 0; i < products.size(); ++i) {
                if(i%2==0) {
                    setColor(0, 7);
                } else {
                    setColor(0, 11);
                }
                cout <<" "<< setw(10) << left << i;
                products[i].Display();
            }
            setColor(7, 0);
            cout<<endl;
        }
    }
    void SaveToFile() {
        ofstream outfile(fileName);
        for (const Product& product : products) {
            outfile << product.name << "," << product.price << "," << getDate() << endl;
        }
        outfile.close();
    }
    void LoadFromFile() {
        products.clear();
        ifstream infile(fileName);
        string line;
        while (getline(infile, line)) {
            string name, price, date;
            size_t pos1 = line.find(',');
            if (pos1 != string::npos) {
                name = line.substr(0, pos1);
                size_t pos2 = line.find(',', pos1 + 1);
                if (pos2 != string::npos) {
                    price = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    date = line.substr(pos2 + 1);
                    Product product(name, price, date);
                    products.push_back(product);
                }
            }
        }
        infile.close();
    }
};

class Product2 {
public:
    string customer, order, status, addedDate;
    Product2(string c, string o, string s, string d) : customer(c), order(o), status(s), addedDate(d) {}

    void Display() const {
        cout << setw(20) << left << customer;
        cout << setw(20) << left << order;
        if(status == "1") {
            cout << setw(14) << left << "Complete";
        } else {
            cout << setw(14) << left << "Pending";
        }
        cout << setw(11) << left << addedDate <<endl;
    }
};

class ProductManager2 {
private:
    vector<Product2> products2;
    string fileName="orders.txt";
public:
    void AddProduct() {
        string customer, order, status="0";
        cout << " Enter Customer: ";
        cin >> customer;
        cout << " Enter Order: ";
        cin >> order;
        Product2 product2(customer, order, status, getDate());
        products2.push_back(product2);
        cout << " Product Added Successfully!" << endl;
        SaveToFile();
    }
    void UpdateProduct() {
        int index;
        cout << " Enter Index to Change Status: ";
        cin >> index;
        if (index >= 0 && index < products2.size()) {
            if(products2[index].status == "0") {
                products2[index].status = "1";
            } else {
                products2[index].status = "0";
            }
            cout << " Order Status Change Successfully!" << endl;
            SaveToFile();
        } else {
            cout << " Invalid Index! " << index << endl;
        }
    }
    void DeleteProduct() {
        int index;
        cout << " Enter Index to Delete: ";
        cin >> index;
        if (index >= 0 && index < products2.size()) {
            products2.erase(products2.begin() + index);
            cout << " Order Deleted Successfully!" << endl;
            SaveToFile();
        } else {
            cout << " Invalid Index! " << index << endl;
        }
    }
    void ShowAllProducts() {
        if (products2.empty()) {
            cout << "\n No Order to Display.\n" << endl;
        } else {
            setColor(15, 1);
            cout <<"\n "<< setw(10) << left << "Index";
            cout << setw(20) << left << "Customer";
            cout << setw(20) << left << "Order";
            cout << setw(14) << left << "Status";
            cout << setw(11) << left << "Date"<<endl;
            for (size_t i = 0; i < products2.size(); ++i) {
                if(i%2==0) {
                    setColor(0, 7);
                } else {
                    setColor(0, 11);
                }
                cout <<" "<< setw(10) << left << i;
                products2[i].Display();
            }
            setColor(7, 0);
            cout<<endl;
        }
    }
    void SaveToFile() {
        ofstream outfile(fileName);
        for (const Product2& product2 : products2) {
            outfile << product2.customer << "," << product2.order << "," << product2.status << "," << product2.addedDate << endl;
        }
        outfile.close();
    }
    void LoadFromFile() {
        products2.clear();
        ifstream infile(fileName);
        string line;
        while (getline(infile, line)) {
            string customer, order, status, date;
            size_t pos1 = line.find(',');
            if (pos1 != string::npos) {
                customer = line.substr(0, pos1);
                size_t pos2 = line.find(',', pos1 + 1);
                if (pos2 != string::npos) {
                    order = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    size_t pos3 = line.find(',', pos2 + 1);
                    if (pos3 != string::npos) {
                        status = line.substr(pos2 + 1, pos3 - pos2 - 1);
                        date = line.substr(pos3 + 1);

                        Product2 product2(customer, order, status, date);
                        products2.push_back(product2);
                    }
                }
            }
        }
        infile.close();
    }

};



void PageShow(string id, vector<string>& str, int size) {
    string space1=" ", space2="  ", txt="", space22="";
    for(int i=1; i<=page_width; i++) {
        space22 = space22 + space1;
    }
    page_id=id;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_GREEN);
    cout<<endl<<endl;
    for(int i=0; i<size; i++) {
        cout<<"\t"<<space22<<"\t"<<endl;
        txt = txt + space2;
        txt = txt + str[i];
        int add = page_width - txt.length();
        for(int j=1; j<=add; j++) {
            txt = txt + space1;
        }
        cout<<"\t"<<txt<<"\t"<<endl;
        txt="";
        if(i==0) {
            cout<<"\t"<<space22<<"\t"<<endl;
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
        }
    }
    cout<<"\t"<<space22<<"\t"<<endl<<endl;
    PageReset();
    page_width=30;
}

void PageReset() {
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void PageCall(string page_id, int i) {
    if(i == 1) {
        system("cls");
    }
    vector<string> str;
    if (page_id == "home") {
        str = {"Home", "1. Products", "2. Orders", "3. Sells", "4. Tools", "5. Help", "0. Exit"};
    }
    if (page_id == "products") {
        str = {"<Products", "1. Add", "2. Update", "3. Delete", "4. Show All", "0. Back"};
    }
    if (page_id == "orders") {
        str = {"<Orders", "1. Add", "2. Change Status", "3. Delete", "4. Show All", "0. Back"};
    }
    if (page_id == "sells") {
        str = {"<Sells", "1. Add (Daily)", "2. Show All", "0. Back"};
    }
    if (page_id == "tools") {
        str = {"<Tools", "1. Customers Info", "2. Note", "0. Back"};
    }
    if (page_id == "help") {
        page_width=50;
        str = {"<Help", "Welcome to Store Management! Navigate through", "product management, order processing, sales", "tracking, and useful tools. For assistance,", "consult our FAQs or reach out to our support", "team. Enjoy streamlined store management!", "", "0. Back"};
    }
    int size = str.size();
    PageShow(page_id, str, size);
    PageControl(page_id);
}

void PageControl(string page_id) {
    int input;
    if(page_id=="home") {
        cout<<" Type your choice: ";
        cin>>input;
        switch(input) {
        case 1:
            PageCall("products", 1);
            break;
        case 2:
            PageCall("orders", 1);
            break;
        case 3:
            PageCall("sells", 1);
            break;
        case 4:
            PageCall("tools", 1);
            break;
        case 5:
            PageCall("help", 1);
            break;
        default :
            exit(0);
            break;
        }
    }

    if(page_id=="products") {
        ProductManager productManager;
        productManager.LoadFromFile();
        cout<<" Type your choice: ";
        cin>>input;
        switch (input) {
        case 1:
            productManager.AddProduct();
            Sleep(1000);
            PageCall("products", 1);
            break;
        case 2:
            productManager.UpdateProduct();
            Sleep(1000);
            PageCall("products", 1);
            break;
        case 3:
            productManager.DeleteProduct();
            Sleep(1000);
            PageCall("products", 1);
            break;
        case 4:
            productManager.ShowAllProducts();
            PageControl("products");
            break;
        default:
            PageCall("home", 1);
        }
    }

    if(page_id=="orders") {
        ProductManager2 productManager2;
        productManager2.LoadFromFile();
        cout<<" Type your choice: ";
        cin>>input;
        switch (input) {
        case 1:
            productManager2.AddProduct();
            Sleep(1000);
            PageCall("orders", 1);
            break;
        case 2:
            productManager2.UpdateProduct();
            Sleep(1000);
            PageCall("orders", 1);
            break;
        case 3:
            productManager2.DeleteProduct();
            Sleep(1000);
            PageCall("orders", 1);
            break;
        case 4:
            productManager2.ShowAllProducts();
            PageControl("orders");
            break;
        default:
            PageCall("home", 1);
        }
    }

    if(page_id=="sells") {
        cout<<" Type your choice: ";
        cin>>input;
        switch(input) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default :
            PageCall("home", 1);
            break;
        }
    }

    if(page_id=="tools") {
        cout<<" Type your choice: ";
        cin>>input;
        switch(input) {
        case 1:
            break;
        case 2:
            break;
        default :
            PageCall("home", 1);
            break;
        }
    }

    if(page_id=="help") {
        cout<<" Type your choice: ";
        cin>>input;
        switch(input) {
        default :
            PageCall("home", 1);
            break;
        }
    }
}

int main() {
    SetConsoleTitle("Store Management");
    PageCall("home", 1);
    getch();
    return 0;
}
