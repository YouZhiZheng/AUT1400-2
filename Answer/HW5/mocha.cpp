#include "mocha.h"

Mocha::Mocha(): EspressoBased()
{
    _name = "Mocha";
    _ingredients.push_back( std::make_shared<Espresso>(2) );
    _ingredients.push_back( std::make_shared<Milk>(2) );
    _ingredients.push_back( std::make_shared<MilkFoam>(1) );
    _ingredients.push_back( std::make_shared<Chocolate>(1) );
}

Mocha::Mocha(const Mocha& cap): EspressoBased(cap)
{
    side_items = cap.side_items;
}

void Mocha::operator=(const Mocha& cap)
{
    if(&cap != this) side_items = cap.side_items;
}

std::string Mocha::get_name()
{
    return _name;
}

double Mocha::price()
{
    double totalPrice = 0.0;

    for(auto &ingredient: _ingredients)
    {
        totalPrice += ingredient->price();
    }

    for(auto &side_item: side_items)
    {
        totalPrice += side_item->price();
    }

    return totalPrice;
}

void Mocha::add_side_item(std::shared_ptr<Ingredient> side)
{
    side_items.push_back(side);
}

std::vector< std::shared_ptr<Ingredient> >& Mocha::get_side_items()
{
    return side_items;
}