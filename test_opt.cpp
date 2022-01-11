/*
 * @Author: Lr-2002 
 * @Date: 2022-01-11 14:16:07 
 * @Last Modified by: Lr-2002
 * @Last Modified time: 2022-01-11 14:23:46
 */

#include <iostream>
#include <array>
#include <type_traits>

template <typename... Us> void f(Us... args)
{


}

template <typename ...Ps> void g(Ps... args)
{
    // how to expand ellipses args ?
    // use initialize list
    // for the args is a list? non ,it must be changed by {}
    int size = sizeof...(args);
    int a[size] = {args...};
    for(auto i : a)
    {
        std::cout << i << std::endl;
    }

    f(&args...);
}


template<typename... Ts> // ... accept not only one argument
constexpr auto make_array(Ts&&... ts)
    -> std::array<std::common_type_t<Ts...>,sizeof...(Ts)>
{
    // description 
    // parameter
    // 1. common_type_t<Ts...> is the type of the array ,like int
    // 2. sizeof...(Ts) is the size of the array, it's the length of the array
    std::cout<< sizeof(std::common_type_t<Ts...>) <<std::endl;
 
    // turn the args list into a array
    return { std::forward<Ts>(ts)... };
}
 
int main(int argc, char **argv)
{
    auto b = make_array(1, 2, 3);
    auto c = make_array('c', 'd', 'e');
    std::cout << b.size() << std::endl;
    for (auto i : b) 
        std::cout << i << std::endl;
    

    g(0,0,2);

}