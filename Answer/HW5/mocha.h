#ifndef MOCHA_H
#define MOCHA_H

#include "espresso_based.h"

class Mocha: public EspressoBased
{
public:
    // 该类的构造函数需要调用 EspressoBased 的构造函数
    Mocha();
    Mocha(const Mocha& cap);
	~Mocha() { side_items.clear(); }

    void operator=(const Mocha& cap);
    std::string get_name() override;
    double price() override;

    void add_side_item(std::shared_ptr<Ingredient> side);
    std::vector< std::shared_ptr<Ingredient> >& get_side_items();

private:
    // 存储顾客要求添加的其他原料
    std::vector< std::shared_ptr<Ingredient> > side_items;
};

#endif // MOCHA_H