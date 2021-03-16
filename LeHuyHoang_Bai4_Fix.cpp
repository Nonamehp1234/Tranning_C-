#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <vector>
#include <iomanip>
#include <fstream>
// LIBRARY : Khai báo các thư viện cần dùng trong chương trình
#define M_PI 3.14 
using namespace std;
class Shape  // Class cha
{
protected:
    string color,thickness;  // color : Màu sắc ,thickness : Độ dày
    float axis_X,axis_Y; // Axis at X : Tâm có hoành độ X, Axis at Y : Tâm có hoành độ Y
public:
    // In ra màn hình
    virtual void get()
    {
        cout <<"| "<< setw(13) << left << thickness <<"| " <<setw(8) << left << color;
    }
    // Nhập vào bàn phím theo yêu cầu
    virtual void set()
    {
        // Nhập các thuộc tính cho class cha : Shape.
        cin.ignore();
        cout << "Nhap do day: ";
        getline(cin, thickness);
        cout << "Nhap mau sac: ";
        getline(cin, color);
        cout << "Nhap hoanh do X:";
        cin >> axis_X;
        cout << "Nhap tung do Y:";
        cin >> axis_Y;
    }
    // Trả về diện tích của từng loại hình
    virtual double area() { return 0; }
    // Return value axis_X : trả về tọa độ có hoành độ là X
    virtual double X() { return axis_X; }
    // Return value axis_Y : trả về tọa độ có tung độ là Y
    virtual double Y() { return axis_Y; }
    // Trả về tên của Shape mà ta đang dùng.
    virtual string shape() { return ""; }
    // Doc file
    virtual void write_file(ostream &fileOutput) {}
    virtual void set(vector<string> s1)
    {
        axis_X = stof(s1[2]);
        axis_Y = stof(s1[3]);
    }
};
// Khai báo lớp Edge : lớp cạnh
class Edge // Không có sự kế thừa của lớp Shape hay lớp cha
{
private:
    string color1,thickness1; // color1 : Màu sắc của cạnh, thickness1 : Độ dày của cạnh
    Shape* p, * q; // 2 con trỏ trỏ đến 2 shape.
    int i, j; // i : shape one, j : shape two.
public:
    Shape *s() { return p; }
    Shape *s1() { return q; }
    // Nhập các thuộc tính của lớp Edge từ bàn phím.
    void set_edge(Shape *_p,Shape *_q,int _i,int _j)
    {
        p = _p;
        q = _q;
        i = _i;
        j = _j;
        cin.ignore();
        cout << "Nhap do day canh:";
        getline(cin, thickness1);
        cout << "Nhap mau sac canh: ";
        getline(cin, color1);
    }
    // In ra màn hình các thuộc tính của lớp Edge.
    void get_edge()
    {
        cout << p->shape() << " co tam (" << p->X() << "," << p->Y() << ") den " << q->shape()<< " co tam (" << q->X() << "," << q->Y() << ") co do dai canh la " << length() << " voi do day la " << thickness1 << " va mau sac la " << color1 <<"\n";
    }
    friend ostream& operator<<(ostream &os,const Edge &q)
    {
        os << "edge{" << q.i << "," << q.j << "," << q.color1 << "," << q.thickness1 << "}";
        return os;
    }
    // Độ dài của 2 tâm theo công thức toán học.
    double length() { return sqrt((p->X() - q->X()) * (p->X() - q->X()) + (p->Y() - q->Y()) * (p->Y() - q->Y())); }
    int get_shapeone() { return i; }
    int get_shapetwo() { return j; }
    void swap_edge(int _i, int _j)
    {
        i = _i;
        j = _j;
    }
    void decrease1()
    {
        i = i - 1;
    }
    void decrease2()
    {
        j = j - 1;
    }
    void set_edge(vector<string> s,vector<Shape*> &List)
    {
        i = stoi(s[1]);
        j = stoi(s[2]);
        p = List[stoi(s[1]) - 1];
        q = List[stoi(s[2]) - 1];
        color1 = s[3];
        thickness1 = s[4];
    }
};
// Khai báo lớp Circle là lớp con của lớp Shape.
class Circle : public Shape
{
private:
    float Radius;
    // Khai báo bán kính hình tròn.
public:
    // Nhập các thuộc tính trong lớp con và kế thừa từ lớp cha.
    void set()
    {
        Shape::set();
        do
        {
            cout << "Nhap ban kinh cua hinh tron: ";
            cin >> Radius;
            if (Radius <= 0)
                cout << "Nhap lai ban kinh cua hinh tron.\n";
        } while (Radius <= 0);
    }
    // In ra màn hình các thuộc tính trong lớp con và kế thừa từ lớp cha.
    void get()
    {
        cout << setw(15) << left << "| Circle";
        Shape::get();
        cout << "| " << setw(8) << left<< area()<<"| Circle co ban kinh la " << Radius <<" va tam la (" << axis_X <<","<< axis_Y <<")";
    }
    // Trả về diện tích hình tròn.
    double area() { return M_PI * Radius * Radius; }
    // Trả về tên của hình tròn theo tiếng anh.
    string shape() { return "Circle"; }
    void write_file(ostream &fileOutput)
    {
         fileOutput << "shape{circle," << axis_X << "," << axis_Y << "," << Radius << "," << color << "," << thickness << "}";
    }
    void set(vector<string> s)
    {
        Shape::set(s);
        Radius = stof(s[4]);
        color = s[5];
        thickness = s[6];
    }
};
// Khai báo lớp Line là lớp con của lớp Shape.
class Line : public Shape
{
private:
    float length;
    // Khai báo độ dài của đường thẳng.
public:
    // Nhập các thuộc tính trong lớp con và kế thừa từ lớp cha.
    void set()
    {
        Shape::set();
        do
        {
            cout << "Gia tri do dai cua doan thang:";
            cin >> length;
            if (length <= 0)
                cout << "Nhap lai do dai cua doan thang.\n";
        } while (length <= 0);
        // x,y mục đích để lưu trữ tọa độ từ lớp cha để làm yêu cầu 6,7,8 ở trong hàm main().
    }
    // In ra màn hình các thuộc tính trong lớp con và kế thừa từ lớp cha.
    void get()
    {
        cout << setw(15) << left << "| Line";
        Shape::get();
        cout << "| " << setw(8) << left << area() <<  "| Line co do dai " << length << " va tam la (" << axis_X << "," << axis_Y << ")";
    }
    // Trả về diện tích đường thẳng.
    double area() { return 0; } // Because line haven't area : Do đường thẳng không có diện tích.
    // Trả về tên đường thẳng theo tiếng anh.
    string shape() { return "Line"; }
    //
    void write_file(ostream& fileOutput)
    {
        fileOutput << "shape{line," << axis_X << "," << axis_Y << "," << length << "," << color << "," << thickness << "}";
    }
    void set(vector<string> s)
    {
        Shape::set(s);
        length = stof(s[4]);
        color = s[5];
        thickness = s[6];
    }
};
// Khai báo lớp Rectangle là lớp con của lớp Shape.
class Rectangle : public Shape
{
private:
    float width, length;
    // Khai báo chiều dài, chiều rộng của hình chữ nhật.
public:
    // Nhập các thuộc tính trong lớp con và kế thừa từ lớp cha.
    void set()
    {
        Shape::set();
        do
        {
            cout << "Nhap gia tri chieu rong : ";
            cin >> width ;
            cout << "Nhap gia tri chieu dai :";
            cin >> length;
            if (width >= length || width <= 0 || length <= 0)
                cout << "Nhap lai gia tri cua hinh chu nhat.\n";
        } while (width <= 0 || length <= 0 || width >= length);
    }
    // In ra màn hình các thuộc tính trong lớp con và kế thừa từ lớp cha.
    void get()
    {
        cout << setw(15) << left << "| Rectangle";
        Shape::get();
        cout << "| " << setw(8) << left << area() << "| Rectangle co chieu rong la " << width << " va chieu dai la " << length << " va tam la (" << axis_X << "," << axis_Y << ")";
    }
    // Trả về diện tích hình chữ nhật.
    double area() { return width * length; }
    // Trả về tên hình chữ nhật theo tiếng anh.
    string shape() { return "Rectangle"; }
    void write_file(ostream& fileOutput)
    {
        fileOutput << "shape{rect," << axis_X << "," << axis_Y << "," << length << "," << width << "," << color << "," << thickness << "}";
    }
    void set(vector<string> s)
    {
        Shape::set(s);
        length = stof(s[4]);
        width = stof(s[5]);
        color = s[6];
        thickness = s[7];
    }
};
// Khai báo lớp Square là lớp con của lớp Shape.
class Square : public Shape
{
private:
    float Edge;
    // Khai báo cạnh hình vuông.
public:
    // Nhập các thuộc tính trong lớp con và kế thừa từ lớp cha.
    void set()
    {
        Shape::set();
        do
        {
            cout << "Nhap gia tri canh cua hinh vuong:";
            cin >> Edge;
            if (Edge <= 0)
                cout << "Nhap lai gia tri canh.\n";
        } while (Edge <= 0);
    }
    // In ra màn hình các thuộc tính trong lớp con và kế thừa từ lớp cha.
    void get()
    {
        cout << setw(15) << left << "| Square";
        Shape::get();
        cout << "| " << setw(8) << left << area() << "| Square co canh la: "  <<  Edge << " va tam la (" << axis_X << "," << axis_Y << ")";
    }
    // Trả về diện tích hình vuông.
    double area() { return Edge * Edge; }
    // Trả về tên hình vuông theo tiếng anh.
    string shape() { return "Square"; }
    void write_file(ostream& fileOutput)
    {
        fileOutput << "shape{square," << axis_X << "," << axis_Y << "," << Edge << "," << color << "," << thickness << "}";
    }
    void set(vector<string> s)
    {
        Shape::set(s);
        Edge = stof(s[4]);
        color = s[5];
        thickness = s[6];
    }
};
// Khai báo lớp Triangle là lớp con của lớp Shape.
class Triangle : public Shape
{
private:
    float e1, e2, e3;
    // Khai báo các cạnh hình tam giác.
public:
    // Nhập các thuộc tính trong lớp con và kế thừa từ lớp cha.
    void set()
    {
        Shape::set();
        do
        {
            cout << "Nhap gia tri canh 1: ";
            cin >> e1;
            cout << "Nhap gia tri canh 2: ";
            cin >> e2;
            cout << "Nhap gia tri canh 3: ";
            cin >> e3;
            if (e1 <= 0 || e2 <= 0 || e3 <= 0 || (e1 + e2) <= e3 || (e2 + e3) <= e1 || (e1 + e3) <= e2)
                cout << "Nhap canh cua tam giac lan nua.\n";
        } while (e1 <= 0 || e2 <= 0 || e3 <= 0 || (e1 + e2) <= e3 || (e2 + e3) <= e1 || (e1 + e3) <= e2);
    }
    // In ra màn hình các thuộc tính trong lớp con và kế thừa từ lớp cha.
    void get()
    {
        cout << setw(15) << left << "| Triangle";
        Shape::get();
        cout << "| " << setw(8) << left << area() << "| Triangle co 3 canh la : (" << e1 << "," << e2 << "," << e3 << ")  va tam la (" << axis_X << "," << axis_Y << ")";
    }
    // Trả về diện tích hình tam giác.
    double area()
    {
        double h_c; // half circumference
        h_c = (e1 + e2 + e3) / 2;
        return sqrt(h_c * (h_c - e1) * (h_c - e2) * (h_c - e3));
    }
    // Trả về tên hình tam giác theo tiếng anh.
    string shape() { return "Triangle"; }
    void write_file(ostream& fileOutput)
    {
        fileOutput << "shape{tri," << axis_X << "," << axis_Y << "," << e1 << "," << e2 << "," << e3 << "," << color << "," << thickness <<"}";
    }
    void set(vector<string> s)
    {
        Shape::set(s);
        e1 = stof(s[4]);
        e2 = stof(s[5]);
        e3 = stof(s[6]);
        color = s[7];
        thickness = s[8];
    }
};
// Khai báo lớp Oval là lớp con của lớp Shape.
class Oval : public Shape
{
private:
    float large_shaft, small_shaft;
    // Khai báo trục lớn,trục nhỏ của hình ellip.
public:
    // Nhập các thuộc tính trong lớp con và kế thừa từ lớp cha.
    void set()
    {
        Shape::set();
        do
        {
            cout << "Nhap gia tri truc lon: ";
            cin >> large_shaft;
            cout << "Nhap gia tri truc be: ";
            cin >> small_shaft;
            if (large_shaft <= 0 || small_shaft <= 0 || large_shaft <= small_shaft)
                cout << "Yeu cau nhap lai truc lon,truc be.\n";
        } while (large_shaft <= 0 || small_shaft <= 0 || large_shaft <= small_shaft);
    }
    // In ra màn hình các thuộc tính trong lớp con và kế thừa từ lớp cha.
    void get()
    {
        cout << setw(15) << left << "| Oval";
        Shape::get();
        cout << "| " << setw(8) << left << area() << "| Oval co truc lon la " << large_shaft << " va truc nho la " << small_shaft << " va co tam la (" << axis_X << "," << axis_Y << ")";
    }
    // Trả về diện tích hình ellip.
    double area() { return M_PI * large_shaft * small_shaft; }
    // Trả về tên hình ellip theo tiếng anh.
    string shape() { return "Oval"; }
    double la() { return large_shaft; }
    double sm() { return small_shaft; }
    void write_file(ostream& fileOutput)
    {
        fileOutput << "shape{oval," << axis_X << "," << axis_Y << "," << large_shaft << "," << small_shaft << "," << color << "," << thickness << "}";
    }
    void set(vector<string> s)
    {
        Shape::set(s);
        large_shaft = stof(s[4]);
        small_shaft = stof(s[5]);
        color = s[6];
        thickness = s[7];
    }
};
class ShapeFactory
{
public:
    static Shape* Create_shape(string s)
    {
        Shape* shape = nullptr;
        if (s == "circle")
            shape = new Circle;
        if (s == "rect")
            shape = new Rectangle;
        if (s == "square")
            shape = new Square;
        if (s == "tri")
            shape = new Triangle;
        if (s == "oval")
            shape = new Oval;
        if (s == "line")
            shape = new Line;
        return shape;
    }
};
void Menu_shape()
{
    cout << "\n======== Cac hinh can them ========";
    cout << "\n\t 1. Tron";
    cout << "\n\t 2. Chu nhat";
    cout << "\n\t 3. Vuong";
    cout << "\n\t 4. Tam giac";
    cout << "\n\t 5. Bau duc";
    cout << "\n\t 6. Doan thang";
}
void Menu_swap()
{
    cout << "\n======== Chon kieu sap xep ========";
    cout << "\n\t 1. Sap xep theo dien tich tang dan.";
    cout << "\n\t 2. Sap xep theo dien tich giam dan.";
}
// Yeu cau 1.
void Add_shape(vector<Shape*>& List)
{
    int choose;
    Menu_shape();
    cout << "\nChon hinh:";
    cin >> choose;
    switch (choose)
    {
    case 1: List.push_back(ShapeFactory::Create_shape("circle")); break;
    case 2: List.push_back(ShapeFactory::Create_shape("rect")); break;
    case 3: List.push_back(ShapeFactory::Create_shape("square")); break;
    case 4: List.push_back(ShapeFactory::Create_shape("tri")); break;
    case 5: List.push_back(ShapeFactory::Create_shape("oval")); break;
    case 6: List.push_back(ShapeFactory::Create_shape("line")); break;
    default: cout << "Yeu cau nhap lai hinh."; break;
    }
    List.back()->set();
}
// Yêu cầu 2.
void Print(vector<Shape*>& List)
{
    if (List.empty())
        cout << "Khong co hinh nao.";
    else
    {
        cout << "======== Thong tin tat ca cac hinh =========\n";
        cout << setw(8) << left << "| STT" << setw(15) << left << "| Shape" << setw(15) << left << "| Thickness" << setw(10) << left << "| Color" << setw(10) << left << "| Area" << setw(50) << left << "| Special_properties";
        for (unsigned int i = 0; i < List.size(); i++)
        {
            cout << "\n| " << setw(6) << left << i + 1;
            List[i]->get();
        }
    }
}
// Yêu cầu 3.
void Delete_shape(vector<Shape*>& List,vector<Edge*>& List_one)
{
    unsigned int dlt,i,j; // dlt understand is delete.
    if (List.empty())
            cout << "Khong co hinh nao.";
    else
    {
            Express_again: cout << "\nChon hinh tu 1 den so phan tu hinh de xoa: ";
            cin >> dlt;  // dlt form 1 to List.size().
            if (dlt > 0 && dlt <= List.size())
            {
                if (List_one.size() < 1)
                    cout << "Khong co canh nao.";
                else
                {
                    j = 0;
                    do
                    {
                        if (List.at(dlt - 1) == List_one[j]->s() || List.at(dlt - 1) == List_one[j]->s1())
                        {
                            i = j;
                            List_one.erase(List_one.begin() + i);
                        }
                        else
                            j++;
                    } while (j != List_one.size());
                    for (unsigned int t = 0; t < List_one.size(); t++)
                    {
                        if (List_one[t]->get_shapeone() > dlt)
                              List_one[t]->decrease1();
                        if (List_one[t]->get_shapetwo() > dlt)
                              List_one[t]->decrease2();
                    }
                }
                cout << "======== Da xoa hinh thanh cong ========";
                List.erase(List.begin() + dlt - 1);
            }
            else
            {
                cout << "\nSo can xoa khong co trong cac phan tu hinh.";
                goto Express_again;
            }
    }
}
// Yêu cầu 4.
void Area(vector<Shape*>& List,vector<Edge*>& List_one)
{
    int choose;
    if (List.empty())
        cout << "Khong co hinh nao.";
    else
    {
        Menu_swap();
        cout << "\nChon sap xep theo dien tich ( tang dan hoac giam dan ) :";
        cin >> choose;
        switch (choose)
        {
        case 1:
            for (unsigned int i = 0; i < List.size() - 1; i++)
                for (unsigned int j = i + 1; j < List.size(); j++)
                    if (List[i]->area() > List[j]->area())
                        swap(List[i], List[j]);
            break;
        case 2:
            for (unsigned int i = 0; i < List.size() - 1; i++)
                for (unsigned int j = i + 1; j < List.size(); j++)
                    if (List[i]->area() < List[j]->area())
                        swap(List[i], List[j]);
            break;
        default:
            cout << "Chon yeu cau khong co.";
            break;
        }
        for (unsigned int i = 0; i < List.size() - 1; i++)
            for (unsigned int j = i + 1; j < List.size(); j++)
                for (unsigned int k = 0; k < List_one.size(); k++)
                {
                    if (List_one[k]->s() == List[j] && List_one[k]->s1() == List[i])
                        List_one[k]->swap_edge(i + 1, j + 1);
                    if (List_one[k]->s() == List[i] && List_one[k]->s1() == List[j])
                        List_one[k]->swap_edge(j + 1, i + 1);
                }
    }
}
// Yêu cầu 5.
void Search(vector<Shape*>& List)
{
    int j;
    float x, y; // Express axis_X and axis_Y to check.
    if (List.empty())
        cout << "Khong co hinh nao.";
    else
    {
        cout << "Tim kiem hinh voi toa do nhap tu ban phim." << endl;
        cout << "Nhap hoanh do X: ";
        cin >> x;
        cout << "Nhap tung do Y: ";
        cin >> y;
        j = 0;
        cout << setw(8) << left << "| STT" << setw(15) << left << "| Shape" << setw(15) << left << "| Thickness" << setw(10) << left << "| Color" << setw(10) << left << "| Area" << setw(50) << left << "| Special_properties";
        for (unsigned int i = 0; i < List.size(); i++)
        {
            if (x == List[i]->X() && y == List[i]->Y())
            {
                j++;
                cout << "\n| " << setw(6) << left << j;
                List[i]->get();
            }
        }
        if (j == 0)
            cout << "\n\t Khong tim thay hinh nao.";
    }
}
// Yêu cầu 6.
void Menu_add_edge(vector<Shape*>& List,vector<Edge*>& List_one)
{
    unsigned int i, j;
    if ( List.size() < 2)
        cout << "Khong the nhap canh nao.";
    else
    {
        do {
            cout << "Nhap 2 hinh de tao 1 canh.\n";
            cout << "Nhap hinh 1:";
            cin >> i;
            cout << "Nhap hinh 2:";
            cin >> j;
            if (i <= 0 || j <= 0 || i > List.size() || j > List.size() || i == j)
                cout << "Yeu cau nhap lai";
        } while (i <= 0 || j <= 0 || i > List.size() || j > List.size() || i == j);
        if (List[i - 1]->X() == List[j - 1]->X() && List[i - 1]->Y() == List[j - 1]->Y())
            cout << "Khong the tao canh giua 2 hinh trung tam.";
        else
        {
            List_one.push_back(new Edge);
            List_one.back()->set_edge(List[i - 1], List[j - 1], i, j);
        }
    }
}
// Yêu cầu 7.
void Print_display(vector<Edge*>& List_one)
{
    if (List_one.empty())
        cout << "Khong co canh nao.";
    else
    {
        for (unsigned int i = 0; i < List_one.size(); i++)
        {
                cout << i + 1 << ".";
                List_one[i]->get_edge();
        }
    }
}
// Yêu cầu 8.
void Print_display1(vector<Shape*>& List,vector<Edge*>& List_one)
{
    unsigned int k ,j = 0;
    if (List_one.empty())
        cout << "Not have edge.";
    else
    {
        nhaplai:  cout << "Nhap hinh ma cac canh di ra khoi hinh do: ";
        cin >> k;
        if (k > List.size() || k <= 0)
        {
            cout << "Yeu cau nhap lai .\n";
            goto nhaplai;
        }
        for (unsigned int i = 0; i < List_one.size(); i++)
            if (List[k - 1] == List_one[i]->s() || List[k - 1] == List_one[i]->s1())
            {
                    j++;
                    cout << j << ".";
                    List_one[i]->get_edge();
            }
        if (j == 0)
            cout << "Khong tim thay hinh nao.\n";
    }
}
// Yeu cau 9.
void delete_edge(vector<Edge*>& List_one)
{
    unsigned int dlt; // dlt understand is delete.
    if (List_one.empty())
        cout << "Khong co canh nao.";
    else
    {
    Express_again: cout << "\nChon canh de xoa ( trong khoang 1 den so phan tu canh ): ";
        cin >> dlt;  // dlt form 1 to List.size().
        if (dlt > 0 && dlt <= List_one.size())
        {
            cout << "======== Da xoa canh thanh cong ========";
            List_one.erase(List_one.begin() + dlt - 1);
        }
        else
        {
            cout << "So can xoa khong co trong so phan tu canh.";
            goto Express_again;
        }
    }
}
// Yêu cầu 10.
void write_file(string filePath, vector<Shape*>& List, vector<Edge*>& List_one)
{
    ofstream fileOutput(filePath);
    if (fileOutput.fail())
        cout << "Khong the mo tep de viet." << endl;
    else
    {
        cout << "======== Da ghi file thanh cong ========";
        for (unsigned int i = 0; i < List.size(); i++)
            if (i != List.size() - 1)
            {
                List[i]->write_file(fileOutput);
                fileOutput << endl;
            }
            else
                List[i]->write_file(fileOutput);
        if (List_one.size() >= 1)
            fileOutput << endl;
        for (unsigned int i = 0; i < List_one.size(); i++)
            if (i != List_one.size() - 1)
                fileOutput << *List_one.at(i) << endl;
            else
                fileOutput << *List_one.at(i);
    }
}
// Yeu cau 11.
void read_file(string filePath, vector<Shape*>& List, vector<Edge*>& List_one)
{
    char s[100];
    unsigned int i,j;
    ifstream fileInput(filePath,ios::in);
    if (fileInput.fail())
        cout << "Khong the mo tep de doc." << endl;
    else
    {
        cout << "======== Doc tep thanh cong ========\n";
        while (!fileInput.eof())
        {
            vector<string> s1;
            fileInput.getline(s, 100);
            string line = s;
            for (i = 0; i < line.size(); i++)
                if (line[i] == '{' || line[i] == '}' || line[i] == ',')
                    line[i] = ' ';
            j = 0;
            for (i = 0; i < line.size(); i++)
                if (line[i] == ' ')
                {
                    s1.push_back(line.substr(j, i - j));
                    j = i + 1;
                }
            if (s1[0] == "shape")
            {
                List.push_back(ShapeFactory::Create_shape(s1[1]));
                List.back()->set(s1);
            }
            if (List.size() >= 2 && s1[0] == "edge")
            {
                if (stoi(s1[1]) != stoi(s1[2]))
                {
                    List_one.push_back(new Edge);
                    List_one.back()->set_edge(s1, List);
                }
            }
        }
    }
}
class Graph
{
private:
    vector<Shape*> List;
    vector<Edge*> List_one;
    string filePath = "FileOfHoang.txt";
public:
    Graph()
    {
        List.resize(0);
        List_one.resize(0);
    }
    ~Graph()
    {
        delete& List;
        delete& List_one;
    }
    void Menu_program()
    {
        char k;
        cout << "\n======== File ========";
        cout << "\n\t 1. Doc file.";
        cout << "\n\t 2. Khong doc file.";
        cout << "\nCo muon doc file khong ?? Bam y de doc hoac bam pham bat ki nhung khong thuc hien doc  : ";
        cin >> k;
        if (k == 'y')
            read_file(filePath, List, List_one);
    }
    void Menu_request()
    {
        cout << "\n======== Cac yeu cau trong chuong trinh ========";
        cout << "\n\t 1. Them 1 hinh.";
        cout << "\n\t 2. In ra tat ca cac hinh.";
        cout << "\n\t 3. Xoa 1 hinh.";
        cout << "\n\t 4. Sap xep dien tich.";
        cout << "\n\t 5. Tim hinh tu tam nhap tu ban phim.";
        cout << "\n\t 6. Them 1 canh.";
        cout << "\n\t 7. In ra tat ca cac canh.";
        cout << "\n\t 8. In ra tat ca cac canh xuat phat tu hinh bat ki.";
        cout << "\n\t 9. Xoa 1 canh.";
    }
    void Menu()
    {
        int choose;
        char k;
        static int i = 0;
        if (i == 0)
        {
            Menu_program();
            i = 1;
        }
        cout << "\nBan da ghi vao file hay chua?? Neu chua ghi file thi chuong trinh se khong duoc luu vao file text.";
        Menu_request();
        cout << "\nChon yeu cau de thuc hien chuong trinh: ";
        cin >> choose;
        switch (choose)
        {
        case 1: Add_shape(List);
                break;
        case 2: Print(List);
                break;
        case 3: Delete_shape(List, List_one);
                break;
        case 4: Area(List, List_one);
                break;
        case 5: Search(List);
                break;
        case 6: Menu_add_edge(List, List_one);
                break;
        case 7: Print_display(List_one);
                break;
        case 8: Print_display1(List, List_one);
                break;
        case 9: delete_edge(List_one);
                break;
        default: cout << "Khong tim thay yeu cau." << endl;
                 break;
        }
        cout << "\nBan co muon ghi vao file khong?? (Bam Y/y de ghi file).";
        cin >> k;
        if (k == 'Y' || k == 'y')
            write_file(filePath, List, List_one);
        else
        {
            cout << "\n======== WARNING ========";
            cout << "\nNeu khong ghi file thi se khong luu lai du lieu co trong chuong trinh";
        }
    }
};
// Hàm chính.
int main()
{
    Graph g;
    char k;
    do
    {
        g.Menu();
        cout << "\nCo muon tiep tuc chon yeu cau hay khong??(Bam Y/y de tiep tuc)";
        k = _getch();
        system("cls");
    } while (k == 'y' || k == 'Y');
    return 0;
}