/*
 * @Author: Lr-2002 
 * @Date: 2022-01-07 18:40:34 
 * @Last Modified by: Lr-2002
 * @Last Modified time: 2022-01-07 20:55:42
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
class Box{
public:
    //default constructor 
    Box() {}
    //initialize a box with equal dimensions
    explicit Box(int i) : m_width(i), m_length(i), m_height(i) {}
    
    //initialize a box with custom dimensions
    Box(int x, int y ,int z): m_width(x), m_length(y), m_height(z) {
        std::cout << "initialize" << std::endl;
    }

    Box(Box& other) : m_width(other.m_width), m_length(other.m_length), m_height(other.m_height)
    {
        std::cout<<"Copy constructor" << std::endl;
    }

    Box(Box&& other) : m_width(other.m_width), m_length(other.m_width), m_height(other.m_height)
    {
        m_contents = std::move(other.m_contents);
        std::cout<<"Move constructor" <<std::endl;
    }

    Box(std::initializer_list<std::string> list, int x, int y, int z) : m_contents(list), m_width(x), m_length(y), m_height(z)
    {
        std::cout << "Initializer_list construct" << std::endl;
    }

    int Volume() { return m_width * m_length * m_height; }

    void Add_Item(std::string item) { m_contents.push_back(item); }

    void Print_Contents()
    {
        for (const auto& item : m_contents)
        {
            std::cout << item << std::endl;
        }
    }

private:
    int m_width;
    int m_length;
    int m_height;

    std::vector<std::string> m_contents;
};

Box get_box()
{
    Box b(3, 2, 5);
    b.Add_Item("hello");
    
    return b;
}


int main() {
    Box b;
    Box a(b);
    
    Box c(3, 4, 5);
    Box e[3] {{1,2,3}, {2,3,4}, {3,4,4}};
    Box d{3, 4, 4};
    std::cout << b.Volume() << " " << a.Volume() << " " << c.Volume() << std::endl;
    std::cout << e[1].Volume() <<std::endl;

    Box dd(get_box());
    dd.Print_Contents();

    // std::initializer_list<std::string> tmp{"hello", "initializer_list"};
    Box f(std::initializer_list<std::string>{"hello", "initializer_list"}, 1, 2, 3);
    f.Print_Contents();
}