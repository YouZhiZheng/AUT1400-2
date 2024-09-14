#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

//#include <string>
#include "ingredient.h"

// 对于 Challenge 的问题：使用宏来定义类
// 可参考Blog: https://www.cnblogs.com/zhaoqingqing/p/17675871.html
// 除了宏，也可以使用模板来简化

class Cinnamon: public Ingredient
{
public:
    Cinnamon(size_t units) : Ingredient{5, units}
    {
        this->_name = "Cinnamon";
    }

    std::string get_name() const override { return this->_name; }
};

class Chocolate: public Ingredient
{
public:
    Chocolate(size_t units) : Ingredient{5, units}
    {
        this->_name = "Chocolate";
    }

    std::string get_name() const override { return this->_name; }
};

class Sugar: public Ingredient
{
public:
    Sugar(size_t units) : Ingredient{1, units}
    {
        this->_name = "Sugar";
    }

    std::string get_name() const override { return this->_name; }
};

class Cookie: public Ingredient
{
public:
    Cookie(size_t units) : Ingredient{10, units}
    {
        this->_name = "Cookie";
    }

    std::string get_name() const override { return this->_name; }
};

class Espresso: public Ingredient
{
public:
    Espresso(size_t units) : Ingredient{15, units}
    {
        this->_name = "Espresso";
    }

    std::string get_name() const override { return this->_name; }
};

class Milk: public Ingredient
{
public:
    Milk(size_t units) : Ingredient{10, units}
    {
        this->_name = "Milk";
    }

    std::string get_name() const override { return this->_name; }
};

class MilkFoam: public Ingredient
{
public:
    MilkFoam(size_t units) : Ingredient{5, units}
    {
        this->_name = "MilkFoam";
    }

    std::string get_name() const override { return this->_name; }
};

class Water: public Ingredient
{
public:
    Water(size_t units) : Ingredient{1, units}
    {
        this->_name = "Water";
    }

    std::string get_name() const override { return this->_name; }
};

#endif // SUB_INGREDIENTS_H