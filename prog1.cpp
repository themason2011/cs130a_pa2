#include <iostream>
#include <list>
#include <iterator>
#include <queue>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

char op = 'n';

class map_node	{ //Class for holding a value and the count of that value in a list
	private:

	public:
		mutable int value = 0;
		mutable int count = 0;
		//Add pointer to go across
		map_node(int value, int count)	{
			this->value = value;
			this->count = count;
		}

		~map_node()	{
			value = 0;
			count = 0;
		}

		int get_value()	{
			return value;
		}

		int get_count()	{
			return count;
		}

		void count_up()	{
			count++;
		}

		void count_down()	{
			count--;
		}
};

// Data structure for Min Heap
class PriorityQueue 
{
private:
	// vector to store heap elements
	vector<map_node> A;

	// return parent of A[i]
	// don't call this function if i is already a root node
	int PARENT(int i) 
	{ 
		return (i - 1) / 2; 
	}

	// return left child of A[i]	
	int LEFT(int i) 
	{ 
		return (2 * i + 1); 
	}

	// return right child of A[i]	
	int RIGHT(int i) 
	{ 
		return (2 * i + 2); 
	}

	// Recursive Heapify-down algorithm
	// the node at index i and its two direct children
	// violates the heap property
	void heapify_down(int i)
	{
		// get left and right child of node at index i
		int left = LEFT(i);
		int right = RIGHT(i);

		int smallest = i;

		// compare A[i] with its left and right child
		// and find smallest value
		if (left < size() && A[left].value < A[i].value)
			smallest = left;

		if (right < size() && A[right].value < A[smallest].value)
			smallest = right;

		// swap with child having lesser value and 
		// call heapify-down on the child
		if (smallest != i) {
			swap(A[i], A[smallest]);
			heapify_down(smallest);
		}
	}

	// Recursive Heapify-up algorithm
	void heapify_up(int i)
	{
		// check if node at index i and its parent violates 
		// the heap property
		if (i && A[PARENT(i)].value > A[i].value) 
		{
			// swap the two if heap property is violated
			swap(A[i], A[PARENT(i)]);
			
			// call Heapify-up on the parent
			heapify_up(PARENT(i));
		}
	}
	
public:
	// return size of the heap
	unsigned int size()
	{
		return A.size();
	}

	// function to check if heap is empty or not
	bool empty()
	{
		return size() == 0;
	}
	
	// insert key into the heap
	void push(map_node key)
	{
		// insert the new element to the end of the vector
		A.push_back(key);

		// get element index and call heapify-up procedure
		int index = size() - 1;
		heapify_up(index);
	}

	// function to remove element with lowest priority (present at root)
	void pop()
	{
		try {
			// if heap has no elements, throw an exception
			if (size() == 0)
				throw out_of_range("Vector<X>::at() : "
						"index is out of range(Heap underflow)");

			// replace the root of the heap with the last element
			// of the vector
			A[0] = A.back();
			A.pop_back();

			// call heapify-down on root node
			heapify_down(0);
		}
		// catch and print the exception
		catch (const out_of_range& oor) {
			cout << "\n" << oor.what();
		}
	}

	// function to return element with lowest priority (present at root)
	map_node top()
	{
		try {
			// if heap has no elements, throw an exception
			if (size() == 0)
				throw out_of_range("Vector<X>::at() : "
						"index is out of range(Heap underflow)");

			// else return the top (first) element
			return A.at(0);	// or return A[0];
		}
		// catch and print the exception
		catch (const out_of_range& oor) {
			cout << "\n" << oor.what();
		}
	}

	void delete_node(int * del)	{
		//TODO: Implement delete function
	}
};

class Quash	{
	private:
		list<map_node> hash_map[42]; //hash_map is an array of lists that hold map_node objects
		PriorityQueue min_heap;
	public:
		void insert(int value)	{
			int hash = value%43;
			if(hash_map[hash].empty())	{ //List at current hash is empty, insert new map_node with value and count = 1
				map_node node(value, 1);
				hash_map[hash].push_back(node);
				min_heap.push(node);
				cout << "item successfully inserted, count = 1" << endl;
				return;
			}
			else	{	//Check if value already exists in list the value hashed to. If it does, increment count. If not, add to end of list
				for(map_node const& i : hash_map[hash])	{ //Iterate through list of current hash
					if(i.value == value)	{
						i.count++;
						//TODO: Add function for PriorityQueue that implements count up for any node in the heap (probably need those pointers set up)
						cout << "item already present, new count = " << i.count << endl;
						return;
					}
				}

				//If this point is reached, that means value did not exist in list. Create new node and push back
				map_node node(value, 1);
				hash_map[hash].push_back(node);
				min_heap.push(node);
				cout << "item successfully inserted, count = 1" << endl;
				return;
			}
		}

		void lookup(int value)	{
			int hash = value%43;
			if(hash_map[hash].empty())	{ //If list at current hash is empty, print item not found and return"
				cout << "item not found" << endl;
				return;
			}
			else	{ //List not empty, look for hash value
				for(map_node const& i : hash_map[hash])	{
					if(i.value == value)	{
						cout << "item found, count = " << i.count << endl;
						return;
					}
				}
				//If not found in list the value hashes to at this point, means value does not exist.
				cout << "item not found" << endl;
				return;
			}
		}

		void deleteMin()	{
			if(min_heap.empty())	{	//Table is empty, min value cannot be deleted bc doesn't exist
				cout << "min item not present since table is empty" << endl;
			}
			else if(min_heap.top().count == 1)	{
				//Pop the item at the top. Must implement delete function instead later
				cout << "min item " << min_heap.top().value << " successfully deleted" << endl;
				min_heap.pop();
			}
			else if(min_heap.top().count > 1)	{ //Count of top value is > 1, so decrement count and return value
				cout << "min item = " << min_heap.top().value << ", count decremented, new count = " << min_heap.top().count << endl;
				int new_count = min_heap.top().count - 1;
				int new_value = min_heap.top().value;
				min_heap.pop();
				map_node new_node(new_value, new_count);
				min_heap.push(new_node);
			}
		}

		void delete_node(int value)	{
			int hash = value%43;
			if(hash_map[hash].empty())	{ //If list at current hash is empty, print item not found and return"
				cout << "item not present in table" << endl;
				return;
			}
			else	{ //List not empty, look for hash value
				for(map_node const& i : hash_map[hash])	{
					if(i.value == value)	{
						if(i.count == 1)	{ //Delete the node
							cout << "item successfully deleted" << endl;
							//TODO: Add function for PriorityQueue that implements delete for any node in the heap (probably need those pointers set up)
							//hash_map[hash].erase(i); //TODO: Delete element in question. Must somehow override erase function for list
							return;
						}
						else if(i.count > 1)	{
							//TODO: Add function for PriorityQueue that implements count down for any node in the heap (probably need those pointers set up)
							i.count--;
							cout << "item count decremented, new count = " << i.count << endl;
							return;
						}
					}
				}
				//If not found in list the value hashes to at this point, means value does not exist.
				cout << "item not present in table" << endl;
				return;
			}
		}

		void print()	{
			PriorityQueue min_heap_copy = min_heap; //Make a copy of min_heap so you can remove elements when iterating

			while(!min_heap_copy.empty())	{
				cout << min_heap_copy.top().value << " ";
				min_heap_copy.pop();
			}

			cout << endl;
		}

		void performOp(char op, int value)	{
			if(op == 'i')	{
				insert(value);
			}
			else if(op == 'l')	{
				lookup(value);
			}
			else if(op == 'd')	{
				delete_node(value);
			}
			else if(op == 'M')	{
				deleteMin();
			}
			else if(op == 'p')	{
				print();
			}
		}
};

void readInput(Quash q, string input)	{
	bool power = false;
	int size_num = 0;
	int coef = 0;
	int pow = 0;
	int num = 0;
	for(int i = 0; i<input.length(); i++)	{
		if(input[i] == 'i' || input[i] == 'l' || input[i] == 'd' || input[i] == 'p')	{ //Handle operators
			if(input[i] == 'i' || input[i] == 'l')	{ //Handle insert and lookup. Increment i by 6 to skip rest of the word (plus the space after it) when parsing
				op = input[i];
				i += 6;
				continue;
			}
			else if(input[i] == 'p')	{ //Increment i by 4 to skip rest of the word print when parsing
				op = 'p';
				i += 4;
				if(i == input.length()-1)	{ //Last command. Execute print statement and finish
					q.performOp(op, 0);
					return;
				}
				continue;
			}
			else if(input[i] == 'd')	{
				if(input[i+6] == 'M')	{ //Set op to deleteMin command. Increment i by 8 to skip rest of word deleteMin when parsing
					op = 'M';
					i += 8;
					if(i == input.length()-1)	{ //Last command. Execute print statement and finish
						q.performOp(op, 0);
						return;
					}
					continue;
				}
				else	{ //Delete command. Increment i by 5 to move past rest of word (plus the space after it) when parsing
					op = 'd';
					i += 6;
					continue;
				}
			}
		}

		else if(input[i] == ',')	{ //Comma delimiter, save previous num in this function
			if(size_num != 0)	{
				num = stoi(input.substr(i-size_num, size_num)); //Converting input string to integer
			}
			else	{ //Size_num == 0, we either have a print statement or a deleteMin. Just set num equal to 0
				num = 0;
			}
			q.performOp(op, num);
			size_num = 0; //Reset number size
			i++; //Increment i by 1 to move past space
		}

		else	{ //If not comma or operator, is a number. The size of the number increments and you continue
			size_num++;
			if(i == input.length()-1)	{
				if(size_num != 0)	{
					num = stoi(input.substr(i-size_num, size_num+1)); //Converting input string to integer
					q.performOp(op, num);
				}
			}
			continue;
		}
	}
}

int main(int argc, char const *argv[])
{
	if(argc != 2)	{
		cout << "Please only enter a string of numbers and operators as a parameter";
		exit(0);
	}
	Quash q;
	string input(argv[1]); //Make argv[1] a string
	readInput(q, input); //Parse input
	
	//Memory Management???
	//Don't forget about memory leak shit, delete head at end
	return 0;
}