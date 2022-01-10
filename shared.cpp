/*
 * @Author: Lr-2002 
 * @Date: 2022-01-08 23:46:13 
 * @Last Modified by: Lr-2002
 * @Last Modified time: 2022-01-09 00:06:13
 */

#include <iostream>
#include <memory>

void del(void(*) ()) {}
void fun() {}

void tt()
{
    std::unique_ptr<int> p(new int);
    // int *p = new int;
}



int main()
{
    std::shared_ptr<void()> ee(fun, del);
    (*ee)();

    int * a = new int;
    *a = 3;
    std::shared_ptr<int> ae(a);
    *a = 4;
    // delete a;
    std::cout << "the value of ae is "<< *ae << std::endl; 

    auto p = std::make_shared<int> (52);
    std::weak_ptr<int> wp(p);

    if(std::shared_ptr<int> np = wp.lock())
    {
        std::cout<< " the same ";
    }

}