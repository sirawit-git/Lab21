#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Please input numbers to find average." << std::endl;
        return 0;
    }
    
    std::vector<double> numbers;
    for (int i = 1; i < argc; ++i) {
        numbers.push_back(std::atof(argv[i]));
    }
    
    double sum = 0;
    for (double num : numbers) {
        sum += num;
    }
    
    int average = static_cast<int>(sum / numbers.size());
    
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Average of " << numbers.size() << " numbers = " << average << std::endl;
    std::cout << "---------------------------------" << std::endl;
    
    return 0;
}
