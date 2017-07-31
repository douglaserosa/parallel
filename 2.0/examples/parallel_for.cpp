#include <iostream>
#include <vector>
#include <cmath>

#include "parallel_for.h"
#include "parallel_reduce.h"

#include "timer.h"

class Sum {
public:
    double operator()(double a, double b) {
        double c = a + b;
        return c;
    }
};

int main(int argc, char *argv[]) {
    const int size = 60000;

    std::vector<double> vector(size);

    Timer timer = Timer();

    jampi::parallel_for(jampi::Range(0, size), 1000, [&](jampi::Range &r_) -> void {
                   for (int i = r_.begin(); i < r_.end(); i++) {
                       vector[i] = std::pow(i, 2) / sqrt(i + 1);
                   }
               }
    );

    std::cout << jampi::parallel_reduce<Sum, double>(vector) << std::endl;

    std::cout << timer.elapsed() << std::endl;

    return 0;
}