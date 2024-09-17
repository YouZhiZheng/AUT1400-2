#ifndef Q3_H
#define Q3_H

#include <queue>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <regex>

namespace q3{
    struct Flight
    {
        std::string flight_number;
        size_t duration = 0; // 单位为分钟
        size_t connections = 0;
        size_t connection_times = 0; // 单位为分钟
        size_t price = 0;
        // 用于计算优先级，返回逻辑与 cmp 相反
        friend bool operator<(Flight a, Flight b){
            size_t a_weights = a.duration + a.connection_times + 3 * a.price;
            size_t b_weights = b.duration + b.connection_times + 3 * b.price;
            return a_weights >= b_weights;
        }
    };

    inline std::priority_queue<Flight> gather_flights(std::string filename)
    {
        std::priority_queue<Flight> flights;
        std::ifstream fin(filename); // 打开文件

        if (!fin.is_open()) 
        {
            throw std::runtime_error("Unable to open file: " + filename);
        }

        std::string line;
        std::regex pattern; // 正则匹配模式
        std::smatch matches;// 正则匹配结果
        std::sregex_iterator next;
        std::sregex_iterator end;

        while(getline(fin, line))
        {
            std::istringstream iss(line);
            Flight flight;

            // 获取行号
            std::getline(iss, line, '-');

            // 获取航班号
            std::getline(iss, line, '-'); // line内容: flight_number:QR492 
            pattern.assign(R"(flight_number:([A-Z0-9]+))");
            std::regex_search(line, matches, pattern);
            flight.flight_number = matches[1].str();
            
            // 获取飞行时间
            std::getline(iss, line, '-'); //  line内容: duration:11h30m 
            pattern.assign(R"(duration:((\d+)h)?((\d+)m)?)");
            std::regex_search(line, matches, pattern);
            if(matches[2].matched) flight.duration += (std::stoul(matches.str(2)) * 60);
            if(matches[4].matched) flight.duration += std::stoul(matches.str(4));
            
            // 获取中转数
            std::getline(iss, line, '-'); // line内容:  connections:3 
            pattern.assign(R"(connections:([0-9]+))");
            std::regex_search(line, matches, pattern);
            flight.connections = std::stoul(matches[1].str());

            // 获取中转时间
            std::getline(iss, line, '-');  // linen内容: connection_times:2h,1h30m,4h15m 
            line.erase(0, 18); // linen内容:2h,1h30m,4h15m
            pattern.assign(R"(((\d+)h)?((\d+)m)?)");
            next = std::sregex_iterator(line.begin(), line.end(), pattern);
            end = std::sregex_iterator();
            // 处理获取的每个转机时间
            while (next != end)
            {
                std::smatch match = *next;
                ++next;

                if (match[2].matched)
                {
                    flight.connection_times += (std::stoul(match.str(2)) * 60); 
                }

                if (match[4].matched)
                {
                    flight.connection_times += std::stoul(match.str(4)); 
                }
            }
            
            // 获取价格
            std::getline(iss, line);
            pattern.assign(R"(price:(\d+))");
            std::regex_search(line, matches, pattern);
            flight.price = std::stoul(matches.str(1));
            
            /*
            std::cout << flight.flight_number << " " << flight.duration << " " << flight.connections << " " 
            << flight.connection_times << " " << flight.price << std::endl;
            */
            flights.push(flight);
        }

        return flights;
    }
}

#endif //Q3_H