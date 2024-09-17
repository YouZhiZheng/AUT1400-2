#ifndef Q2_H
#define Q2_H

#include <vector>
#include <fstream>
#include <stdexcept>
#include <algorithm>

namespace q2{
    struct Patient
    {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };

    inline std::vector<Patient> read_file(std::string filename)
    {
        std::vector<Patient> patients;
        std::ifstream fin(filename); // 打开文件
        
        if (!fin.is_open()) 
        {
            throw std::runtime_error("Unable to open file: " + filename);
        }
        
        std::string line;
        std::getline(fin, line); // 读取标题行
        std::getline(fin, line); // 读取每列说明

        while( std::getline(fin, line) )
        {
            std::istringstream iss(line);
            Patient patientInfo;

            std::getline(iss, patientInfo.name, ',');
            std::getline(iss, line, ',');
            patientInfo.name += (" " + line);

            std::getline(iss, line, ',');
            patientInfo.age = std::stoul(line);

            std::getline(iss, line, ',');
            patientInfo.smokes = std::stoul(line);

            std::getline(iss, line, ',');
            patientInfo.area_q = std::stoul(line);

            std::getline(iss, line, ',');
            patientInfo.alkhol = std::stoul(line);

            patients.push_back(patientInfo);
        }

        fin.close();

        return patients;
    }

    inline bool cmp(Patient a, Patient b)
    {
        size_t a_weights = 3 * a.age + 5 * a.smokes + 2 * a.area_q + 4 * a.alkhol;
        size_t b_weights = 3 * b.age + 5 * b.smokes + 2 * b.area_q + 4 * b.alkhol;

        return a_weights >= b_weights;
    }

    inline void sort(std::vector<Patient> &patients)
    {
        std::sort(patients.begin(), patients.end(), cmp);
    }
}

#endif //Q2_H