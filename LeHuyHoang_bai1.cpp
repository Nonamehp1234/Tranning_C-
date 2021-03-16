#include <iostream>
#include <string>
#include <iomanip>

void Menu();
static int n;
using namespace std;

class SinhVien
{
private:
    string name, date, country, ID; // name : Ten , date : Nam Sinh , country : Que Quan , ID : Ma Sinh Vien.
    string name_phanten, name_phanho, name_phandem;
    // Example : "LE HUY HOANG" - name_phanten is: "HOANG" , name_phanho is : "LE" , name_phandem is : "HUY"
    float point; // point : diem Sinh Vien.
public:
    void Nhap();
    void In();
    friend void xoa(SinhVien* p, int n, int n1);
    friend void swap_diem(SinhVien* p, int n);
    friend void swap_ten(SinhVien* p, int n);
    friend void swap_quequan(SinhVien* p, int n);
    friend void swap_Masv(SinhVien* p, int n);
    friend void SVcungque(SinhVien* p, string s, int n);
    friend void swap(SinhVien* p, SinhVien* q);
    friend void swap_date(SinhVien* p, int n);
};
//
void SinhVien::Nhap()
{
    // Nhap Thong tin ten,tuoi, que quan, diem thi cua thi sinh.
    cin.ignore();
    cout << "Nhap ten Sinh Vien: ";
    getline(cin, name);
    cout << "Nhap Ngay Sinh Sinh vien: " ;
    getline(cin, date);
    cout << "Nhap Que Quan Sinh Vien: ";
    getline(cin, country);
    cout << "Nhap Ma SV: ";
    getline(cin, ID);
    cout << "Diem dau vao: ";
    cin >> point;
}
//
void SinhVien::In()
{
      // O day ta se dung cac ham de in ra thong tin Sinh Vien.
    cout << setw(5) << left << "----" << setw(25) << left << name << setw(12) << left << date << setw(15) << left << country << setw(10) << left << ID << setw(5) << left << point << endl ;
}
//
void swap(SinhVien* p, SinhVien* q)
{
    SinhVien temp;
    temp = *p;
    *p = *q;
    *q = temp;
}
//
void xoa(SinhVien* p,int n,int n1)
{
    if (n1 <= n && n1>= 0)
    {
        for (int i = 0; i < n; i++)
            if (i >= n1 - 1 && i < n-1)
                p[i] = p[i + 1];
 
    }
    else
        cout << " Yeu cau nhap lai Sinh Vien can xoa";
}
//
void SVcungque(SinhVien* p,string s,int n)
{
    for (int i = 0; i < n; i++)
        if (s == p[i].country)
            p[i].In();
}
//
void swap_diem(SinhVien *p,int n)
{
    SinhVien temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
            if (p[i].point < p[j].point)
                swap(p + i, p + j);
    }
}
//
void swap_ten(SinhVien* p, int n)
{
    int dem = 0, demkitu = 0, demkitu1 = 0, max;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p[i].name.length(); j++)
        {
            if (p[i].name[j] == ' ')
                dem++;
            //
        }
        //
        max = dem;
        dem = 0;
        for (int j = 0; j < p[i].name.length(); j++)
        {
            demkitu++;
            if (p[i].name[j] == ' ')
                dem++;
            //
            if (dem == max)
            {
                p[i].name_phanten = p[i].name.substr(demkitu, p[i].name.length() - 1);
                dem = 0;
                break;
            }
        }
       cout << p[i].name_phanten << " "; // In ra chuoi con cuoi cung cua string.
        //
        for (int j = 0; j < p[i].name.length(); j++)
        {
            demkitu1++;
            if (p[i].name[0] == ' ')
                dem = 0;
            if (p[i].name[j] == ' ')
                dem++;
            if (dem == 1)
            {
                p[i].name_phanho = p[i].name.substr(0, demkitu1);
                break;
            }
        }
        //
        cout << p[i].name_phanho << " ";
        // In ra chuoi con dau tien cua string.
        p[i].name_phandem = p[i].name.substr(demkitu1, demkitu - demkitu1);
        cout << p[i].name_phandem << " " <<endl;
        dem = 0;
        demkitu = 0;
        demkitu1 = 0;
    }
    // Sap xep theo thu tu : Ten -> Ho -> Phan dem.
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].name_phanten > p[j].name_phanten)
                    swap(p + i, p + j);
            if (p[i].name_phanten == p[j].name_phanten)
            {
                if (p[i].name_phanho > p[j].name_phanho)
                    swap(p + i, p + j);
                if (p[i].name_phanho == p[j].name_phanho)
                    if (p[i].name_phandem > p[j].name_phandem)
                        swap(p + i, p + j);
            }
        }
    }
}
//
void swap_date(SinhVien* p, int n)
{
    SinhVien temp;
    for (int i = 0; i < n - 1; i++)
    {
         for(int j=i+1;j<n;j++)
             if(p[i].date>p[j].date)
                    swap(p + i, p + j);
    }
}
//
void swap_quequan(SinhVien* p, int n)
{
    SinhVien temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
            if (p[i].country > p[j].country)
                    swap(p + i, p + j);
    }
}
//
void swap_Masv(SinhVien* p, int n)
{
    SinhVien temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
            if (p[i].ID > p[j].ID)
                   swap(p + i, p + j);
    }
}
//
void NhapLai()
{
    cout << "Yeu cau nhap lai yeu cau dau bai" << endl;
    cout << "Khong Co Du Lieu Trong Chuong Trinh" << endl;
}
//
void Menu()
{
    cout << "------------CHUONG TRINH QUAN LY SINH VIEN------------ " << endl;
    cout << "1. Nhap Thong Tin Sinh Vien " << endl;
    cout << "2. Xuat Danh Sach Sinh Vien Ra Man Hinh " << endl;
    cout << "3. Sap Xep Theo Diem " << endl;
    cout << "4. Sap xep theo Ten" << endl;
    cout << "5. Sap xep theo Ngay sinh" << endl;
    cout << "6. Sap xep theo Que Quan" << endl;
    cout << "7. Sap xep theo Ma SV" << endl;
    cout << "8. Hien Thi Cac Sinh Vien Cung Que " << endl;
    cout << "9. Xoa " << endl;
    cout << "0. Thoat " << endl;
}
//
int main()
{
    string s;
    int choose , n1,dem=0; // Chon nen lam gi ( Nhap , xuat , Sap xep hay Xoa ).
    bool DaNhap = false; // Tra ve kieu logic 0 va 1.
    Menu();
    cout << " Nhap So Luong Sinh Vien Can Nhap : ";
    cin >> n ;
    SinhVien* sv = new SinhVien[n];
    do
    {   
        cout << "Chon Yeu Cau: ";
        cin >> choose;
        switch (choose)
        {
         
             case 1: // Nhap Thong Tin Sinh Vien
                 if (dem == 0) {
                     cout << "-------- Nhap Thong Tin Sinh Vien --------" << endl;
                     DaNhap = true;
                     for (int i = 0; i < n; i++)
                     {
                         cout << "Nhap thong tin sinh vien thu " << i + 1 << ": " << endl;
                         sv[i].Nhap();
                     }
                     //
                     dem++;
                     break;
                 }
                 else
                 {
                     cout << "Danh sach sinh vien da co, khong nhap lai." << endl;
                     break;
                 }
              case 2:  // Xuat Thong Tin Sinh Vien
                  if (DaNhap)
                  {
                      cout << "------ Xuat thong tin Sinh Vien ------" << endl;
                      for (int i = 0; i < n; i++)
                          sv[i].In();
                      //
                      break;
                  }
                  else
                  {
                      NhapLai();
                      break;
                  }
              case 3:  // Sap xep theo diem
                  if (DaNhap)
                  {
                      cout << "Sap Xep theo diem cua Sinh Vien:" << endl;
                      swap_diem(sv, n);
                      for (int i = 0; i < n; i++)
                            sv[i].In();
                      //
                      break;
                  }
                  else
                  {
                      NhapLai();
                      break;
                  }
              case 4:   // Sap xep theo ten
                  if (DaNhap)
                  {
                      cout << "------  Sap xep theo Ten ------" << endl;
                      swap_ten(sv, n);
                      for (int i = 0; i < n; i++)
                          sv[i].In();
                      //
                      break;
                  }
                  else
                  {
                      NhapLai();
                      break;
                  }
              case 5:  // Sap xep theo ngay thang nam sinh ( VD: year/month/day se~ de~ dang` su dung.
                  if (DaNhap)
                  {
                      cout << "------  Sap xep theo Ngay Thang Nam Sinh ------" << endl;
                      swap_date(sv, n);
                      for (int i = 0; i < n; i++)
                          sv[i].In();
                      //
                      break;
                  }
                  else
                  {
                      NhapLai();
                      break;
                  }
              case 6:   // Sap xep theo que quan
                  if (DaNhap)
                  {
                      cout << "------   Sap xep theo Que Quan ------" << endl;
                      swap_quequan(sv, n);
                      for (int i = 0; i < n; i++)
                          sv[i].In();
                      //
                      break;
                  }
                  else
                  {
                      NhapLai();
                      break;
                  }
              case 7:   // Sap xep theo MSSV
                  if (DaNhap)
                  {
                      cout << "------   Sap xep theo Ma Sinh Vien   ------" << endl;
                      swap_Masv(sv, n);
                      for (int i = 0; i < n; i++)
                          sv[i].In();
                      //
                      break;
                  }
                  else
                  {
                      NhapLai();
                      break;
                  }
              case 8:     // In cac Sinh vien co cung que voi du lieu nhap.
                  if (DaNhap)
                  {
                      cin.ignore();
                      cout << "In ra nhung Sinh Vien co que la:" ;
                      getline(cin, s);
                      SVcungque(sv, s , n);
                      //
                      break;
                  }
                  else
                  {
                      NhapLai();
                      break;
                  }
              case 9:  // Xoa di 1 hoc sinh bat ki
                  if (DaNhap)
                  {
                      cout << "Muon xoa Sinh Vien thu may trong chuong trinh ???" << endl;
                      cin >> n1;
                      xoa(sv, n, n1);
                      n = n - 1;
                      break;
                  }
                  else
                  {
                      NhapLai();
                      break;
                  }
              default:
                  cout << "Yeu cau khong co trong chuong trinh" << endl;
                  break;
        }
    } while (choose!=0); // Bam so 0 de thoat , theo kieu int.
}
