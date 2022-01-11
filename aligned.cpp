#include<type_traits>
#include<iostream>

using namespace std;

struct A
{
    A(int a, char b) : a(a), b(b) {}
    void con(int x1, char x2)
    {
        a = x1;
        b = x2;
    }
    int a= 3;
    char b = 'c';
};

template <typename T, size_t N>
class Value
{
public:
    Value() {}
    Value(int x)
    {

    }
    T call()
    {
        // change storage to pointer and then de-pointer to get the object
        return *reinterpret_cast<T*>(&storage[0]);
    }
    void construct(int a, char b)
    {
        reinterpret_cast<T*>(&storage[0])->con(a, b); 
    }
    ~Value() {}

private:
    typename aligned_storage<sizeof(T), alignof(T)>::type storage[N];
};

int main()
{
    Value<A,3> value;
    value.construct(3, 'd');
    cout<< value.call().b << endl;
    return 0;
}