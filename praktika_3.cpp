#include <iostream>


using namespace std;

class A1 {
    protected:
        int a1;

    public:
        A1 (int _a1 = 0) { a1 = _a1; cout << "\nClass A1 constructor"; }
        virtual void print() { cout << "\nVariable of A1 class"; }
        virtual void show() { cout << "\na1 = " << a1; }
};

class B1: virtual public A1 {
    protected:
        int b1;
    public:
        B1 (int _b1 = 0, int a1 = 0) : A1(a1) { b1 = _b1; cout << "\nClass B1 constructor"; }
        virtual void print() { cout << "\nVariable of B1 class"; }
        virtual void show() { cout << "\nb1 = " << b1 << ", a1 = " << a1; }
};

class B2: virtual public A1 {
    protected:
        int b2;
    public:
        B2 (int _b2 = 0, int a1 = 0) : A1(a1) { b2 = _b2; cout << "\nClass B2 constructor"; }
        virtual void print() { cout << "\nVariable of B2 class"; }
        virtual void show() { cout << "\nb2 = " << b2 << ", a1 = " << a1; }
};

class B3: virtual public A1 {
    protected:
        int b3;
    public:
        B3 (int _b3 = 0, int a1 = 0) : A1(a1) { b3 = _b3; cout << "\nClass B3 constructor"; }
        virtual void print() { cout << "\nVariable of B3 class"; }
        virtual void show() { cout << "\nb3 = " << b3 << ", a1 = " << a1; }
};


class C1:  public B1,  public B2,  public B3 {
    protected:
        int c1;
    public:
        C1 (int _c1 = 0, int b1 = 0, int b2 = 0, int b3 = 0, int a1 = 0) : B1(b1, a1), B2(b2, a1), B3(b3, a1)
        {
            c1 = _c1;
            cout << "\nClass C1 constructor";
        }
        void print() { cout << "\nVariable of C1 class"; }
        void show() {
            cout << "\nc1 = " << c1 << ", b1 = " << b1 << ", b2 = " << b2 << ", b3 = " << b3 << ", a1 = " << a1;
        }

};

class C2:  virtual public B1,  virtual public B2,  virtual public B3 {
    protected:
        int c2;
    public:
        C2 (int _c2 = 0, int b1 = 0, int b2 = 0, int b3 = 0, int a1 = 0) : B1(b1, a1), B2(b2, a1), B3(b3, a1)
        {
            c2 = _c2;
            cout << "\nClass C2 constructor";
        }
        virtual void print() { cout << "\nVariable of C2 class"; }
        virtual void show() {
            cout << "\nc2 = " << c2 << ", b1 = " << b1 << ", b2 = " << b2 << ", b3 = " << b3 << ", a1 = " << a1;
        }

};

int main() 
{
    A1 a1(1);
    a1.print();
    a1.show();

    cout << "\n";

    B1 b1(2, 3);
    b1.print();
    b1.show();

    cout << "\n";
    
    B2 b2(4, 5);
    b2.print();
    b2.show();

    cout << "\n";
    
    B3 b3(6, 7);
    b3.print();
    b3.show();

    cout << "\n";
    
    C1 c1(8, 9, 10, 11, 12);
    c1.print();
    c1.show();

    cout << "\n";
    
    C2 c2(13, 14, 15, 16, 17);
    c2.print();
    c2.show();

    cout << "\n";

    A1* ptr = &a1;
	ptr->show();
	ptr = &b1;
	ptr->show();
	ptr = &c1;
	ptr->show();
    return 0;
}