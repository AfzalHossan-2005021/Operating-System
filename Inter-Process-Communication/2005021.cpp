#include <iostream>
#include <random>
#include<pthread.h>
#include<unistd.h>

#define STARTING_STANDARD_TICKET 1001
#define STARTING_PREMIUM_TICKET 2001

using namespace std;

int N, M, w, x, y, z;

enum visitor_type {
    STANDARD = 1,
    PREMIUM = 2
};

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

class visitor {
    private:
        int ticket_number;
        enum visitor_type visitor_type;
    public:
        visitor(int ticket_number, enum visitor_type visitor_type) {
            this->ticket_number = ticket_number;
            this->visitor_type = visitor_type;
        }

        int get_ticket_number() {
            return ticket_number;
        }

        enum visitor_type get_visitor_type() {
            return visitor_type;
        }
};

void* simulate_visit(void* arg) {
    visitor* visitor = (class visitor*) arg;
    int random_number = poisson_random_number(1, N + M);
    usleep(random_number);
    int ticket_number = visitor->get_ticket_number();
    cout << ticket_number << endl;
    return NULL;
}

void* simulate_standard_visitor_entry(void* arg) {
    visitor* standard_visitors[N];
    for(int i = 0; i < N; i++) {
        standard_visitors[i] = new visitor(STARTING_STANDARD_TICKET + i, STANDARD);
    }
    pthread_t standard_visitor_thread[N];
    for(int i = 0; i < N; i++) {
        pthread_create(&standard_visitor_thread[i], NULL, simulate_visit, standard_visitors[i]);
    }
    for(int i = 0; i < N; i++) {
        pthread_join(standard_visitor_thread[i], NULL);
    }
    return NULL;
}

void* simulate_premium_visitor_entry(void* arg) {
    visitor* premium_visitors[M];
    for(int i = 0; i < M; i++) {
        premium_visitors[i] = new visitor(STARTING_PREMIUM_TICKET + i, PREMIUM);
    }
    pthread_t premium_visitor_thread[M];
    for(int i = 0; i < M; i++) {
        pthread_create(&premium_visitor_thread[i], NULL, simulate_visit, premium_visitors[i]);
    }
    for(int i = 0; i < M; i++) {
        pthread_join(premium_visitor_thread[i], NULL);
    }
    return NULL;
}


int main(int argc, char* argv[]) {
    // Check if the input and output files are provided
    if(argc < 3) {
        cout << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return 1;
    }
    // Get the input and output file names
    char* input_file = argv[1];
    char* output_file = argv[2];

    // Redirect the input and output to the input.txt and output.txt files
    freopen(input_file, "r", stdin);
    freopen(output_file, "w", stdout);

    // Read N, M from the input
    cin >> N >> M;

    // Read w, x, y, z from the input
    cin >> w >> x >> y >> z;

    pthread_t standard_visitor_entry_thread;
    pthread_t premium_visitor_entry_thread;

    pthread_create(&standard_visitor_entry_thread, NULL, simulate_standard_visitor_entry, NULL);
    pthread_create(&premium_visitor_entry_thread, NULL, simulate_premium_visitor_entry, NULL);

    pthread_join(standard_visitor_entry_thread, NULL);
    pthread_join(premium_visitor_entry_thread, NULL);
    
    return 0;
}
