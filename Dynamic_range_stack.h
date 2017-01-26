/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  x37ding  @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"
#include "ece250.h"

class Dynamic_range_stack {
	private:
		int entry_count;
		int max_count;
		int min_count;
		int initial_capacity;
		int current_capacity;

		int *stack_array;
		int *maximum_array;
		int *minimum_array;
		int *popvalue;

		// You may wish to include a number of helper functions
		// in order to abstract out some operations


	public:
		Dynamic_range_stack( int = 10 );
		Dynamic_range_stack( Dynamic_range_stack const & );
		~Dynamic_range_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		int maximum() const;
		int minimum() const;

		
		void push( int const & );
		int pop();
		void clear();


	// Friends

	friend std::ostream &operator<<( std::ostream &, Dynamic_range_stack const & );
};

Dynamic_range_stack::Dynamic_range_stack( int n ):
entry_count( 0 ),
min_count( 0 ),
max_count( 0 ),
initial_capacity( std::max( 1, n ) ),
current_capacity( initial_capacity ),
stack_array( new int[current_capacity] ),
maximum_array( new int[current_capacity] ),
minimum_array( new int[current_capacity] ) {
	// empty constructor
}

Dynamic_range_stack::~Dynamic_range_stack() {
	delete[] stack_array;
	delete[] maximum_array;
	delete[] minimum_array;
}

int Dynamic_range_stack::top() const {
	if (entry_count == 0){
		underflow excep;
		throw excep;
	}
	return *(stack_array+entry_count - 1);
}

int Dynamic_range_stack::maximum() const {
	if (max_count == 0){
		underflow excep;
		throw excep;
	}
	return *(maximum_array+max_count - 1);
}

int Dynamic_range_stack::minimum() const {
	if (min_count == 0){
		underflow excep;
		throw excep;
	}
		
	return *(minimum_array+min_count - 1);
}

int Dynamic_range_stack::size() const {
	return entry_count;
}

bool Dynamic_range_stack::empty() const {
	return entry_count==0;
}

int Dynamic_range_stack::capacity() const {
	return current_capacity;
}



void Dynamic_range_stack::push( int const &obj ) {
	//size check
	if (entry_count == current_capacity) {
		current_capacity = current_capacity * 2;
		int *stack_array_new = new int[current_capacity];
		int *maximum_array_new = new int[current_capacity];
		int *minimum_array_new = new int[current_capacity];
		for (int i = 0; i < current_capacity; i++) {
			*(stack_array_new+i) = *(stack_array+i);
			*(maximum_array_new+i) = *(maximum_array+i);
			*(minimum_array_new+i) = *(minimum_array+i);
		}
		delete[] stack_array;
		delete[] maximum_array;
		delete[] minimum_array;
		stack_array = stack_array_new;
		maximum_array = maximum_array_new;
		minimum_array = minimum_array_new;
		delete stack_array_new;
		delete minimum_array_new;
		delete maximum_array_new;
	}
	//push new value
	*(stack_array+entry_count) = obj;
	//max array
	if (max_count != 0) {
		if (*(stack_array + entry_count) > *(maximum_array+max_count-1)) {
			*(maximum_array+max_count) = *(stack_array+entry_count);
			max_count++;
		}
	}
	else {
		*(maximum_array) = *(stack_array+entry_count);
		max_count = 1;
	}
	//min array
	if (min_count != 0) {
		if (*(stack_array+entry_count) < *(minimum_array+min_count - 1)) {
			*(minimum_array+min_count) = *(stack_array+entry_count);
			min_count++;
		}
	}
	else {
		*(minimum_array) = *(stack_array + entry_count);
		min_count = 1;
	}
	//stack array count increment
	entry_count++;
}

int Dynamic_range_stack::pop() {
	if (entry_count == 0){
		underflow excep;
		throw excep;
	}
		;
	//pop maximum array if match
	if (*(stack_array + entry_count - 1) == *(maximum_array + max_count - 1)) {
		*popvalue=*(maximum_array + max_count - 1);
		*(maximum_array + max_count - 1) = 0;
		max_count--;
	}
	//pop minimum array if match
	if (*(stack_array + entry_count - 1) == *(minimum_array + min_count - 1)) {
		*popvalue=*(minimum_array + min_count - 1);
		*(minimum_array + min_count - 1) = 0;
		min_count--;
	}
	//pop stack array
	*(stack_array+entry_count - 1) = 0;
	entry_count--;
	return *popvalue;
}

void Dynamic_range_stack::clear() {
	//reset three arrays
	delete[] stack_array;
	delete[] maximum_array;
	delete[] minimum_array;
	//reset array count
	entry_count = 0;
	min_count = 0;
	max_count = 0;
	//allocate new memory location for three arrays if size does not match
	if (current_capacity!=initial_capacity) {
		stack_array = new int[initial_capacity];
		maximum_array = new int[initial_capacity];
		minimum_array = new int[initial_capacity];
	}
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Dynamic_range_stack const &stack ) {

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif