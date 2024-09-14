#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H

#include <vector>
#include <memory>
#include <ncurses.h>
#include <unistd.h>
#include "sub_ingredients.h"

class EspressoBased
{
public:
    virtual std::string get_name() = 0;
    virtual double price() = 0;

    void brew();
    std::vector< std::shared_ptr<Ingredient> >& get_ingredients();

    // 如果析构函数在 protected 下定义, 则该类对象不能正常释放资源, 且该析构函数应
    // 声明为虚函数
    virtual ~EspressoBased() { _ingredients.clear(); }

protected:
    EspressoBased() {}
    // 采用 shared_ptr 时，在这里会发生深拷贝，每个对象的引用数都会加1
    EspressoBased(const EspressoBased& esp): _name(esp._name), 
        _ingredients(esp._ingredients) {}
    void operator=(const EspressoBased& esp);
    // 改用 shared_ptr 来实现，更优雅，但需要自行更改 unit_test.cpp 文件
    std::vector< std::shared_ptr<Ingredient> > _ingredients;
    std::string _name;
};

#endif // ESPRESSO_BASED_H