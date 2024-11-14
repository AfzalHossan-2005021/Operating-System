#include <iostream>
#include <random>
#include <pthread.h>
#include <unistd.h>
#include <chrono>
#include <semaphore.h>

#define STARTING_STANDARD_TICKET 1001
#define STARTING_PREMIUM_TICKET 2001
#define GALLARY1_CAPACITY 5

using namespace std;

int N, M, w, x, y, z;

enum zoo_position {
    A,
    B,
    STEP1,
    STEP2,
    STEP3,
    C
};



// Define the mutex locks
pthread_mutex_t print_lock;
pthread_mutex_t A_lock;
pthread_mutex_t B_lock;
pthread_mutex_t step1_lock;
pthread_mutex_t step2_lock;
pthread_mutex_t step3_lock;

sem_t sem_C;


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
    int id;
public:
    visitor(int id) {
        this->id = id;
    }
    int get_id() {
        return id;
    }
};

void init_lock() {
    pthread_mutex_init(&print_lock, NULL);
    pthread_mutex_init(&A_lock, NULL);
    pthread_mutex_init(&B_lock, NULL);
    pthread_mutex_init(&step1_lock, NULL);
    pthread_mutex_init(&step2_lock, NULL);
    pthread_mutex_init(&step3_lock, NULL);
    sem_init(&sem_C, 0, GALLARY1_CAPACITY);
}

void destroy_lock() {
    pthread_mutex_destroy(&print_lock);
    pthread_mutex_destroy(&A_lock);
    pthread_mutex_destroy(&B_lock);
    pthread_mutex_destroy(&step1_lock);
    pthread_mutex_destroy(&step2_lock);
    pthread_mutex_destroy(&step3_lock);
    sem_destroy(&sem_C);
}

auto start_time = std::chrono::high_resolution_clock::now();

long long get_time() {
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
  long long elapsed_time_ms = duration.count();
  return elapsed_time_ms;
}

void print_step(visitor* visitor, zoo_position position) {
    // pthread_mutex_lock(&print_lock);
    switch(position) {
        case A:
            cout << "Visitor " << visitor->get_id() << " has arrived at A at time stamp " << get_time() << endl;
            break;
        case B:
            cout << "Visitor " << visitor->get_id() << " has arrived at B at time stamp " << get_time() << endl;
            break;
        case STEP1:
            cout << "Visitor " << visitor->get_id() << " is at step 1 at time stamp " << get_time() << endl;
            break;
        case STEP2:
            cout << "Visitor " << visitor->get_id() << " is at step 2 at time stamp " << get_time() << endl;
            break;
        case STEP3:
            cout << "Visitor " << visitor->get_id() << " is at step 3 at time stamp " << get_time() << endl;
            break;
        case C:
            cout << "Visitor " << visitor->get_id() << " is at C (entered Gallery 1) at time " << get_time() << endl;
            break;
    }
    // pthread_mutex_unlock(&print_lock);
}

void* simulate_visit(void* arg) {
    visitor* visitor = (class visitor*) arg;
    // Add random delays before a visitor steps into the hallway AB to achieve randomness
    usleep(poisson_random_number(1, N + M));

    pthread_mutex_lock(&A_lock);
    print_step(visitor, A);
    pthread_mutex_lock(&B_lock);
    pthread_mutex_unlock(&A_lock);
    usleep(w);
    print_step(visitor, B);
    pthread_mutex_lock(&step1_lock);
    pthread_mutex_unlock(&B_lock);
    usleep(10);
    print_step(visitor, STEP1);
    pthread_mutex_lock(&step2_lock);
    pthread_mutex_unlock(&step1_lock);
    usleep(10);
    print_step(visitor, STEP2);
    pthread_mutex_lock(&step3_lock);
    pthread_mutex_unlock(&step2_lock);
    usleep(10);
    print_step(visitor, STEP3);
    sem_wait(&sem_C);
    pthread_mutex_unlock(&step3_lock);
    usleep(10);
    print_step(visitor, C);
    sem_post(&sem_C);

    return NULL;
}

void* simulate_standard_visitor_entry(void* arg) {
    visitor* standard_visitors[N];
    for(int i = 0; i < N; i++) {
        standard_visitors[i] = new visitor(STARTING_STANDARD_TICKET + i);
    }
    pthread_t standard_visitor_thread[N];
    for(int i = 0; i < N; i++) {
        pthread_create(&standard_visitor_thread[i], NULL, simulate_visit, standard_visitors[i]);
    }
    for(int i = 0; i < N; i++) {
        pthread_join(standard_visitor_thread[i], NULL);
    }
    // free the memory allocated for the standard visitors
    for(int i = 0; i < N; i++) {
        delete standard_visitors[i];
    }
    return NULL;
}

void* simulate_premium_visitor_entry(void* arg) {
    visitor* premium_visitors[M];
    for(int i = 0; i < M; i++) {
        premium_visitors[i] = new visitor(STARTING_PREMIUM_TICKET + i);
    }
    pthread_t premium_visitor_thread[M];
    for(int i = 0; i < M; i++) {
        pthread_create(&premium_visitor_thread[i], NULL, simulate_visit, premium_visitors[i]);
    }
    for(int i = 0; i < M; i++) {
        pthread_join(premium_visitor_thread[i], NULL);
    }
    // free the memory allocated for the premium visitors
    for(int i = 0; i < M; i++) {
        delete premium_visitors[i];
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

    // Initialize the locks
    init_lock();

    // Create the threads for the standard and premium visitors entry simulation
    pthread_t standard_visitor_entry_thread;
    pthread_t premium_visitor_entry_thread;

    pthread_create(&standard_visitor_entry_thread, NULL, simulate_standard_visitor_entry, NULL);
    pthread_create(&premium_visitor_entry_thread, NULL, simulate_premium_visitor_entry, NULL);

    pthread_join(standard_visitor_entry_thread, NULL);
    pthread_join(premium_visitor_entry_thread, NULL);

    // Destroy the locks
    destroy_lock();
    
    return 0;
}
