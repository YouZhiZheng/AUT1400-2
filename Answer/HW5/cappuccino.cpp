#include "cappuccino.h"

Cappuccino::Cappuccino(): EspressoBased()
{
    _name = "Cappuccino";
    _ingredients.push_back( std::make_shared<Espresso>(2) );
    _ingredients.push_back( std::make_shared<Milk>(2) );
    _ingredients.push_back( std::make_shared<MilkFoam>(1) );
}

Cappuccino::Cappuccino(const Cappuccino& cap): EspressoBased(cap)
{
    side_items = cap.side_items;
}

void Cappuccino::operator=(const Cappuccino& cap)
{
    if(&cap != this) side_items = cap.side_items;
}

std::string Cappuccino::get_name()
{
    return _name;
}

double Cappuccino::price()
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

void Cappuccino::add_side_item(std::shared_ptr<Ingredient> side)
{
    side_items.push_back(side);
}

std::vector< std::shared_ptr<Ingredient> >& Cappuccino::get_side_items()
{
    return side_items;
}