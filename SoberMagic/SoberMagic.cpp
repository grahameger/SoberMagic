//
//  SoberMagic.cpp
//  SoberMagic
//
//  Created by Graham Eger on 4/5/17.
//  Copyright © 2017 Graham Eger. All rights reserved.
//


/* --------------- STL Includes --------------- */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <iomanip>

/* -------------- Local Includes -------------- */
#include "Sober.hpp"

/* ------- Helper Function Declarations ------- */
using queue_type = std::priority_queue<Sober, std::vector<Sober>, std::less<Sober> >;
void not_enough_args();
inline bool operator<(const Sober& lhs, const Sober& rhs);
void print_and_increment(queue_type &queue, size_t n);
void write_to_file(queue_type &heads, queue_type &regs, std::string &pool);
void print_queue(queue_type &queue, std::ostream &output);
std::string get_file_name(std::string &pool);

/* ------------------- Main ------------------- */
int main(int argc, char const *argv[]) {
    
    if (argc != 5) {
        not_enough_args();
        return 0;
    }
    
    // The first argument is going to be the name of the current database file
    std::ifstream in_file(argv[1]);
    
    // The file will contain a header HEAD in all capital letters followed by an integer, that
    // will tell us the number of people who are in that section
    std::string header;
    size_t num_entries;
    in_file >> header >> num_entries;
      
    // create two priority queues using the comparator lambda created above
    queue_type heads;
    queue_type regs;
    
    std::string first_name;
    std::string last_name;
    size_t points;
    // Loop through the number of lines that are specified by the header
    for (size_t i = 0; i < num_entries; ++i) {
        // get the information into our temporary variables
        in_file >> first_name >> last_name >> points;
        
        //push it into our priority queue
        heads.push({first_name + ' ' + last_name, points});
    }
    
    // Next we have to look at our "regular" sobers
    // We can use the same temp variables from above
    in_file >> header >> num_entries;
    for (size_t i = 0; i < num_entries; ++i) {
        // same as above`
        in_file >> first_name >> last_name >> points;
        regs.push({first_name + ' ' + last_name, points});
    }
    
    // no we have everything from the flatfile into the priority queues
    // time to print stuff
    // First we're going to get the number of sobers of each type that we want from the command line
    size_t num_head = atoi(argv[2]);
    size_t num_regs = atoi(argv[3]);
    
    // Also we're going to get which point pool we're working with, "BIG" or "SMALL", for the filename
    std::string pool(argv[4]);
    
    // Print a header line then print the sobers and increment
    std::cout << num_head << " head sobers - " << num_regs << " regular sobers.\n";
    print_and_increment(heads, num_head);
    print_and_increment(regs, num_regs);
    
    // Write it all out to a file
    write_to_file(heads, regs, pool);
    
    return 0;
}


/* ------- Helper Function Definitions -------- */

// Print usage information for error handling
void not_enough_args() {
    std::cerr << "Not enough arguments!\n";
    std::cerr << "input format\n";
    std::cerr << "./SoberMagic <input_file_name> <number of head sobers> <number of regular sobers> <BIG || SMALL>\n";
}

// An overloaded < operator for the Sober class.
inline bool operator<(const Sober& lhs, const Sober& rhs) {
    return lhs.getPoints() > rhs.getPoints();
}

// Prints and increments the points of n sobers
void print_and_increment(queue_type &queue, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        // Pop off the top element and store it in a temp variable
        Sober temp = queue.top();
        queue.pop();
        
        // Print the sober monitors name with a newline
        std::cout << temp.getName() << '\n';
        
        // Increment the number of points that our sober has
        ++temp;
        
        // Add it back to the priority queue
        queue.push(temp);
    }
}

void write_to_file(queue_type &heads, queue_type &regs, std::string &pool) {

    std::ofstream out_file(get_file_name(pool));
    
    // Writes headers than the queues to the file
    out_file << "HEAD " << heads.size() << '\n';
    print_queue(heads, out_file);
    out_file << "REGULAR " << regs.size() << '\n';
    print_queue(regs, out_file);
}

void print_queue(queue_type &queue, std::ostream &output) {
    // This will print and empty the queue with a random shuffle.
    // We will pop the pq into a vector, randomly shuffle the vector
    // Then print it to the ostream
    std::vector<Sober> to_shuffle;
    while (!queue.empty()) {
        Sober temp = queue.top();
        queue.pop();
        to_shuffle.push_back(temp);
    }
    std::random_shuffle(to_shuffle.begin(), to_shuffle.end());
    for (int i = 0; i < to_shuffle.size(); ++i) {
        output << to_shuffle[i].getName() << '\t' << to_shuffle[i].getPoints() << '\n';
    }
}

std::string get_file_name(std::string &pool) {
    // Get the date and time as a string
    std::stringstream date_time;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    date_time << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    
    // return the full string
    return (pool + "Sobers-" + date_time.str() + ".txt");
}
