#ifndef Q1_H
#define Q1_H

namespace q1{
    // TEST1 ~ TEST3 能够正确调用该函数，是因为C++ 编译器通过参数类型能自动推导出模板参数类型
    template<typename Func>
    double gradient_descent(double initial_value, double step_size, Func function)
    {
        double x = initial_value;
        double gradient;
        double tolerance = 1e-7;  // 收敛条件
        int max_iterations = 10000; // 最大迭代次数
        int iterations = 0;

        do {
            // 使用有限差分法计算导数
            gradient = (function(x + tolerance) - function(x)) / tolerance;
            
            // 根据梯度下降更新x的值
            x -= step_size * gradient;

            iterations++;
        } while (std::abs(gradient) > tolerance && iterations < max_iterations);

        return x;
    }

    template<typename T, typename Func>
    double gradient_descent(T initial_value, T step_size)
    {
        T x = initial_value;
        T gradient;
        T tolerance = 1e-7;  // 收敛条件
        int max_iterations = 10000; // 最大迭代次数
        int iterations = 0;
        Func function;

        do {
            // 使用有限差分法计算导数
            gradient = (function(x + tolerance) - function(x)) / tolerance;
            
            // 根据梯度下降更新x的值
            x -= step_size * gradient;

            iterations++;
        } while (std::abs(gradient) > tolerance && iterations < max_iterations);
        
        return x;
    }
}

#endif //Q1_H