#include <iostream>
#include <vector>
#include "parallel_reduce.h"
#include "default_algorithm.h"

#include "default_thread.h"

class Sum {
public:
    int operator()(int &a, int &b) {
        int c = a + b;
        return c;
    }
};

int main(int argc, char *argv[]) {

    std::vector<int> vector(100);

    for (int i = 0; i < 100; i++) {
        vector[i] = i;
    }

    std::cout << jampi::parallel_reduce<Sum, int, jampi::DefaultAlgorithm, jampi::DefaultThread>(vector) << std::endl;

    return 0;
}