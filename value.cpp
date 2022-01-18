#include<iostream>
#include<type_traits>
using namespace std;

void push_back(const int &num)
{
    // because of the const reference can point to a r-value so this func works
    cout << num << endl;
}

void change(int && value_type)
{
    value_type = 3;
}

class A
{
    int i =3 ;
    public:
    A(){}
    A(int a): i(a) {
        cout<<"calling the constructor"<<endl;
    }
    ~A() {
        cout<<"using delete function" <<endl;
    }
};
struct B
{
    B() {}
};
struct C
{
    int m;
};


int main() {
    int a = 5;
    int & ref_a  = a;
    const int & ref_c = 3; // const reference can point at r-value
    int && ref_b =  3;// r-value-reference
    int && ref_d = std::move(3); // convert a value to r-value // value include r-value and l-value
    cout << ref_d << endl;
    change(std::forward<int>(a));
    // change(a);

    A dd(5);
    dd.~A();


    cout << is_trivial<int>::value << endl;
    cout << is_trivial<char>::value << endl;

}