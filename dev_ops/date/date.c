#define _POSIX_C_SOURCE 200809L

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void print_time (void) {


    time_t     now;
    struct tm  ts;
    char       buf[80];

    // Get current time
    time(&now);

    // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&now);

    long            ms; // Milliseconds
    time_t          s;  // Seconds

    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    s  = spec.tv_sec;
    ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
    if (ms > 999) {
        s++;
        ms = 0;
    }

    strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
    printf("%s .%03ld \n", buf,ms);

}

// Create an elapsed time of 500 ns and print the system time
// Test if the time gap is 500 ms
void test_nsec(){
	printf("\nTesting gap of 500 ms\n");
	struct timespec tim, tim2;
	for(int i = 0; i < 10; i++){
   		tim.tv_sec = 0;
		tim.tv_nsec = 500000000L;
		nanosleep(&tim, &tim2);
		print_time();
	}

}

// Create an elapsed time of 500 ns and print the system time
// Test if the time gap is 500 ms
void test_sec(){
	printf("\nTesting gap of 10 seconds\n");
	struct timespec tim, tim2;
	for(int i = 0; i < 10; i++){
		sleep(10);
		print_time();
	}

}

int main(){
	test_nsec();
	test_sec();
}
