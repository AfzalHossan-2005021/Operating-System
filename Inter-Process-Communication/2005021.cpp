#include <iostream>
#include <random>
#include <pthread.h>
#include <unistd.h>
#include <chrono>
#include <semaphore.h>

#define STARTING_STANDARD_TICKET 1001
#define STARTING_PREMIUM_TICKET 2001
#define GALLARY1_CAPACITY 5
#define GLASS_CORRIDOR_CAPACITY 3
#define STEP_DELAY 10

using namespace std;

int N, M, w, x, y, z;

enum visitor_type {
    STANDARD,
    PREMIUM
};

enum zoo_position {
    A,
    B,
    STEP1,
    STEP2,
    STEP3,
    C,
    D,
    E,
    WAITING,
    PHOTO_BOOTH,
    F
};

int pb_visiting_standard_visitor_count = 0;
int pb_waiting_premium_visitor_count = 0;

// Define the mutex locks
pthread_mutex_t print_lock;
pthread_mutex_t step1_lock;
pthread_mutex_t step2_lock;
pthread_mutex_t step3_lock;

sem_t sem_C;
sem_t sem_D;

pthread_mutex_t pb_premium_visitor_waiting_lock;
pthread_mutex_t pb_visiting_lock;
pthread_mutex_t pb_visiting_standard_visitor_count_lock;
pthread_mutex_t pb_waiting_premium_visitor_count_lock;

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

// Define the start time
auto start_time = std::chrono::high_resolution_clock::now();

// Get the current time
long long get_time() {
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
  long long elapsed_time_ms = duration.count();
  return elapsed_time_ms;
}

// Define the visitor class
class visitor {
private:
    int id;
    visitor_type type;
public:
    visitor(int id) {
        this->id = id;
        if(id >= STARTING_STANDARD_TICKET && id < STARTING_PREMIUM_TICKET) {
            this->type = STANDARD;
        } else {
            this->type = PREMIUM;
        }
    }
    int get_id() {
        return id;
    }
    visitor_type get_type() {
        return type;
    }
};

void init_lock() {
    pthread_mutex_init(&print_lock, NULL);
    pthread_mutex_init(&step1_lock, NULL);
    pthread_mutex_init(&step2_lock, NULL);
    pthread_mutex_init(&step3_lock, NULL);
    sem_init(&sem_C, 0, GALLARY1_CAPACITY);
    sem_init(&sem_D, 0, GLASS_CORRIDOR_CAPACITY);
    pthread_mutex_init(&pb_premium_visitor_waiting_lock, NULL);
    pthread_mutex_init(&pb_visiting_lock, NULL);
    pthread_mutex_init(&pb_visiting_standard_visitor_count_lock, NULL);
    pthread_mutex_init(&pb_waiting_premium_visitor_count_lock, NULL);
}

void destroy_lock() {
    pthread_mutex_destroy(&print_lock);
    pthread_mutex_destroy(&step1_lock);
    pthread_mutex_destroy(&step2_lock);
    pthread_mutex_destroy(&step3_lock);
    sem_destroy(&sem_C);
    sem_destroy(&sem_D);
    pthread_mutex_destroy(&pb_premium_visitor_waiting_lock);
    pthread_mutex_destroy(&pb_visiting_lock);
    pthread_mutex_destroy(&pb_visiting_standard_visitor_count_lock);
    pthread_mutex_destroy(&pb_waiting_premium_visitor_count_lock);
}

void print_step(visitor* visitor, zoo_position position) {
    pthread_mutex_lock(&print_lock);
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
            cout << "Visitor " << visitor->get_id() << " is at C (entered Gallery 1) at time stamp " << get_time() << endl;
            break;
        case D:
            cout << "Visitor " << visitor->get_id() << " is at D (exiting Gallery 1) at time stamp " << get_time() << endl;
            break;
        case E:
            cout << "Visitor " << visitor->get_id() << " is at E (entered Gallery 2) at time stamp " << get_time() << endl;
            break;
        case WAITING:
            cout << "Visitor " << visitor->get_id() << " is about to enter the photo booth at time stamp " << get_time() << endl;
            break;
        case PHOTO_BOOTH:
            cout << "Visitor " << visitor->get_id() << " is inside the photo booth at time stamp " << get_time() << endl;
            break;
        case F:
            cout << "Visitor " << visitor->get_id() << " has left the photo booth at time stamp " << get_time() << endl;
            break;
    }
    pthread_mutex_unlock(&print_lock);
}

void simulate_standard_visitor_photo_booth_entry(visitor* visitor) {
    // Lock the premium visitor waiting lock and the standard visitor count lock
    pthread_mutex_lock(&pb_premium_visitor_waiting_lock);  // Check if there are any premium visitors waiting
    pthread_mutex_lock(&pb_visiting_standard_visitor_count_lock);  // Check if there is any standard visitor updating the count
    pb_visiting_standard_visitor_count++; // Increment the standard visitor count
    if(pb_visiting_standard_visitor_count == 1) { // If the standard visitor count is 1, lock the visiting lock
        pthread_mutex_lock(&pb_visiting_lock);
    }
    pthread_mutex_unlock(&pb_visiting_standard_visitor_count_lock);
    pthread_mutex_unlock(&pb_premium_visitor_waiting_lock);

    // Simulate the standard visitor's movement through the photo booth
    print_step(visitor, PHOTO_BOOTH);
    usleep(z);
    print_step(visitor, F);

    // Decrement the standard visitor count
    pthread_mutex_lock(&pb_visiting_standard_visitor_count_lock);
    pb_visiting_standard_visitor_count--;
    if(pb_visiting_standard_visitor_count == 0) {
        pthread_mutex_unlock(&pb_visiting_lock);
    }
    pthread_mutex_unlock(&pb_visiting_standard_visitor_count_lock);
}

void simulate_premium_visitor_photo_booth_entry(visitor* visitor) {
    // Lock the premium visitor waiting lock and the premium visitor count lock
    pthread_mutex_lock(&pb_waiting_premium_visitor_count_lock);    // Check if there is any premium visitor updating the count
    pb_waiting_premium_visitor_count++;    // Increment the waiting premium visitor count
    if(pb_waiting_premium_visitor_count == 1) {
        pthread_mutex_lock(&pb_premium_visitor_waiting_lock);   // If the waiting premium visitor count is 1, lock the premium visitor waiting lock
    }
    pthread_mutex_unlock(&pb_waiting_premium_visitor_count_lock);

    // Lock the photo booth visiting lock
    pthread_mutex_lock(&pb_visiting_lock);
    
    // Decrement the waiting premium visitor count
    pthread_mutex_lock(&pb_waiting_premium_visitor_count_lock);
    pb_waiting_premium_visitor_count--;
    if(pb_waiting_premium_visitor_count == 0) {
        pthread_mutex_unlock(&pb_premium_visitor_waiting_lock);
    }
    pthread_mutex_unlock(&pb_waiting_premium_visitor_count_lock);

    // Simulate the premium visitor's movement through the photo booth
    print_step(visitor, PHOTO_BOOTH);
    usleep(z);
    print_step(visitor, F);
    pthread_mutex_unlock(&pb_visiting_lock);
}

void* simulate_visit(void* arg) {
    visitor* visitor = (class visitor*) arg;
    // Add random delays before a visitor steps into the hallway AB to achieve randomness
    usleep(poisson_random_number(1, N + M));

    // Simulate the visitor's movement through the hallway
    print_step(visitor, A);
    usleep(w);  // Visitor takes w in the hallway AB
    print_step(visitor, B);

    // Synchronize the visitor's movement through the steps
    pthread_mutex_lock(&step1_lock);
    print_step(visitor, STEP1);
    usleep(STEP_DELAY);
    pthread_mutex_lock(&step2_lock);
    print_step(visitor, STEP2);
    pthread_mutex_unlock(&step1_lock);
    usleep(STEP_DELAY);
    pthread_mutex_lock(&step3_lock);
    print_step(visitor, STEP3);
    pthread_mutex_unlock(&step2_lock);
    usleep(STEP_DELAY);

    // Simulate the visitor's entry into the gallery 1
    sem_wait(&sem_C);
    print_step(visitor, C);
    pthread_mutex_unlock(&step3_lock);
    usleep(x); // Visitor takes x in the gallery 1

    // Simulate the visitor's entry into the glass corridor
    sem_wait(&sem_D);
    print_step(visitor, D);
    sem_post(&sem_C);

    // Visitor stay in the glass corridor for random time and waiting to enter the gallery 2
    usleep(poisson_random_number(1, 10));
    print_step(visitor, E);
    sem_post(&sem_D);
    usleep(y); // Visitor takes y in the gallery 2
    print_step(visitor, WAITING);

    // Simulate the visitor's movement through the photo booth
    if(visitor->get_type() == STANDARD) {
        // simulate the standard visitor's wait time before entering the photo booth
        usleep(poisson_random_number(1, 10));
        simulate_standard_visitor_photo_booth_entry(visitor);
    } else {
        simulate_premium_visitor_photo_booth_entry(visitor);
    }

    return NULL;
}

void* simulate_standard_visitor_entry(void* arg) {
    // Create the standard visitors
    visitor* standard_visitors[N];
    for(int i = 0; i < N; i++) {
        standard_visitors[i] = new visitor(STARTING_STANDARD_TICKET + i);
    }
    // Create threads for the standard visitors
    pthread_t standard_visitor_thread[N];
    for(int i = 0; i < N; i++) {
        pthread_create(&standard_visitor_thread[i], NULL, simulate_visit, standard_visitors[i]);
    }
    // Wait for the standard visitors to complete their visit
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
    // Create the premium visitors
    visitor* premium_visitors[M];
    for(int i = 0; i < M; i++) {
        premium_visitors[i] = new visitor(STARTING_PREMIUM_TICKET + i);
    }
    // Create threads for the premium visitors
    pthread_t premium_visitor_thread[M];
    for(int i = 0; i < M; i++) {
        pthread_create(&premium_visitor_thread[i], NULL, simulate_visit, premium_visitors[i]);
    }
    // Wait for the premium visitors to complete their visit
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
