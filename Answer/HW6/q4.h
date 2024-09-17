#ifndef Q4_H
#define Q4_H

#include <algorithm>
#include <vector>

namespace q4{
    struct Vector2D
    {
        Vector2D(double x, double y): x(x), y(y) {}
        double x{};
        double y{}; 
    };

    struct Sensor
    {
        Vector2D pos;
        double accuracy;
    };

    // 由于禁止使用for语句，这里采用 std::for_each 来实现
    inline Vector2D kalman_filter(std::vector<Sensor> sensors)
    {
        double x, y, total_weight;
        x = y = total_weight = 0.0;

        auto Func = [&x, &y, &total_weight](const Sensor &sensor){
                x += (sensor.pos.x * sensor.accuracy);
                y += (sensor.pos.y * sensor.accuracy);
                total_weight += sensor.accuracy;
            };

        std::for_each(sensors.begin(), sensors.end(), Func);

        x /= total_weight;
        y /= total_weight;

        return Vector2D(x, y);
    }
}

#endif //Q4_H