/*
 * @Author: Lr-2002 
 * @Date: 2022-01-09 20:45:19 
 * @Last Modified by: Lr-2002
 * @Last Modified time: 2022-01-09 21:32:51
 */

#include<array>
#include<iostream>
// #include<memory>
#include<vector>

class A
{
    A() {std::cout << "construct a new A" << std::endl;}
    // A(int ){std::cout << "construct a new A using int "<< std::endl;}
    ~A() {}
};

int main()
{
    std::vector<A> a;
    A c();
    a.push_back(c);
    std::cout << std::endl;

    // std::array<A, 2> b=  {1, 2};

}
