/*****************************************************************
 * 
 * Steven Ortiz 
 * ECGR 3090 Data Structure  Assignment 9
 * Find the running median using Max and Min heaps 
 *int main provided by professor Dr. R from UNC-Charlotte
 * ***************************************************************/


#include <iostream>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <algorithm>    // std::swap

using namespace std;

const int MAX_VAL = 100;
const int NUM_ELEM = 15;

// Global Variables
int h_low_size, h_high_size;
int heap_size_diff=0;

// declared functions 
int find_median(priority_queue<int, vector<int>, greater<int>>& h_high, priority_queue<int>& h_low, int num);
void balance( priority_queue<int,vector<int>, greater<int>>& h_high, priority_queue<int>& h_low);
template<typename T> void print_queue(T& q);

int main() {
    int current_median;
    priority_queue<int> lo; // Bottom half of numbers - max-heap (default) 
    priority_queue<int, vector<int>, greater<int> > hi; // Top half of numbers - min-heap 
    srand(time(0)); // Seed for random number generator
    for (int i = 0; i < NUM_ELEM; i++) {
        int n = rand() % MAX_VAL;
        current_median = find_median(hi, lo, n);
        cout <<  "Inserted " << n << " Median " << current_median << endl << endl;
    }
    return 0;
}

template<typename T> void print_queue(T& q) {
    T q_copy(q);
    while(!q_copy.empty()) {
        std::cout << q_copy.top() << " ";
        q_copy.pop();
    }
    std::cout << '\n';
}
 

int find_median(priority_queue<int,vector<int>, greater<int>>& h_high, priority_queue<int>& h_low, int num) {
	
int result;
bool more_than_2_entries_flag = false; 
int h_high_top, h_low_top;

/**********************************************
 * This section inserts the number into the appropriate heap. 
 * The first entry is inserted into the low heap. 
 * A flag is used to take care of the unbalanced by setting a flag high
 * ********************************************/
if(h_low.empty() == true && h_high.empty() == true){
	more_than_2_entries_flag = false;
	h_low.push(num);
	result=h_low.top();
	}
else if(num <= h_low.top()){//1st if num is lower than h_low 
		more_than_2_entries_flag =true; 
		h_low.push(num);}
else if(num > h_low.top() && h_high.empty() == true){//3rd if num is higher than the h_low and h_high empty 
	more_than_2_entries_flag =true;
	h_high.push(num);
	}
else if(num > h_low.top() && num < h_high.top()) {
	more_than_2_entries_flag =true;
	h_low.push(num);}
	
else if(num >= h_high.top()){ //2nd if num is higher or equal to h_high 
	more_than_2_entries_flag =true;
		h_high.push(num);}
		
/*****************************************************
 * This will balance for any entry thats 2 or greater 
 * **************************************************/
if(more_than_2_entries_flag == true) {
		balance(h_high,h_low);
	}
	
/***********************************************
 * Checks for median after balancing of 2 entries or greater
 * ******************************************/
if(more_than_2_entries_flag ==true){
	h_high_top = h_high.top();
	h_low_top = h_low.top();
	
	h_low_size = h_low.size(); 
	h_high_size = h_high.size();
	heap_size_diff = abs(h_high_size - h_low_size); 
	
	if((h_low.size()%2 == 0 && h_high.size()%2 ==0) || (h_high.size() == 1 && h_low.size() == 1)){
		result = ( h_low_top + h_high_top)/2;}
	else if(h_low.size()%2 != 0 && h_high.size()%2 !=0){
		result = (h_low_top + h_high_top)/2;}
	else if(heap_size_diff >= 1){
	if(h_high_size > h_low_size)
			result = h_high_top; 
	else if(h_low_size > h_high_size)
		result = h_low_top;
		}
	}
	return (result);
}


/**********************************************************
 * The balance function will balance the two heaps if the difference in size 
 * are bigger than 2 or gretaer 
 * **********************************************************/
void balance( priority_queue<int,vector<int>, greater<int>>& h_high, priority_queue<int>& h_low){
bool h_low_unbalance = false; 
bool h_high_unbalance = false; 	
	int temp1 =0;
	int temp2 =0;
	
if( h_high.empty() != true && h_low.empty() != true) {
		h_low_size = h_low.size(); 
		h_high_size = h_high.size(); 
		heap_size_diff = abs(h_high_size - h_low_size); 
		}
else if(h_high.empty() == true && h_low.size() >= 2){
			h_low_unbalance = true;
		}
else if(h_low.empty() == true && h_high.size() >= 2)
			h_high_unbalance = true;
	
if(heap_size_diff >= 2){
	if( h_high_size > h_low_size){
		h_high_unbalance = true;
		}
	else if(  h_low_size > h_high_size){
		h_low_unbalance = true;
		}
	}
	
if(h_low_unbalance == true){
		temp1 = h_low.top();
		h_high.push(temp1);
		h_low.pop();
		h_low_unbalance = false;
		}
if(h_high_unbalance == true){
		temp2 = h_high.top();
		h_low.push(temp2);
		h_high.pop();
		h_high_unbalance = false;}
		
}
