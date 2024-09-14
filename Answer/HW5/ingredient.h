#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient
{
public:
    double get_price_unit() const { return _price_unit; }
    size_t get_units() const { return _units; }
    virtual std::string get_name() const = 0;
    double price() { return _price_unit * static_cast<double>(_units); }
    virtual ~Ingredient() = default;
protected:
    Ingredient(double price_unit, size_t units):_price_unit(price_unit), 
        _units(units) {}

    double _price_unit;
    size_t _units;
    std::string _name;
};

#endif // INGREDIENT_H