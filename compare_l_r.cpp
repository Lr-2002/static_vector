/*
 * @Author: Lr-2002 
 * @Date: 2022-01-11 11:15:40 
 * @Last Modified by: Lr-2002
 * @Last Modified time: 2022-01-11 11:25:04
 */

#include <iostream>
using namespace std;
template <class T>
void print(T & t)
{
    cout<< "lvalue"<< endl;
}
template<class T>
void print(T && t)
{   
    cout <<" rvalue"<< endl;
}

template<class T>
void test_forward(T && v)
{
    print(v);
    print(std::forward<T> (v));
    // print(std::move <T>(v));
}

int main(int argc, char *argv[])
{
    test_forward(1);

}