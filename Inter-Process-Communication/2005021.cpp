#include <iostream>
#include <random>

using namespace std;
// Generate a random number using the Poisson distribution
int poisson_random_number(int start, int end) {
    // Set the mean (lambda) for the Poisson distribution
    double lambda = (start + end) / 2.0;

    // Create a random device and generator
    random_device rd;
    mt19937 generator(rd());

    // Define the Poisson distribution
    poisson_distribution<int> poisson(lambda);

    // Determine the range of the random number
    int range = end - start + 1;

    // Generate a random number
    int random_number = poisson(generator);

    // Adjust the random number to be within the range
    random_number = random_number % range + start;

    return random_number;
}


int main() {
    // Define the range for the random number
    int start = 2001;
    int end = 2100;
    for(int i = 0; i < 100; i++) {
        // Generate a random number
        int random_number = poisson_random_number(start, end);

        // Output the random number
        std::cout << random_number << std::endl;
    }

    return 0;
}
