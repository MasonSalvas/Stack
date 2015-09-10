#pragma once 

const int MAX = 60; // declares the max value 

template <class T> 
class stack
{

public:
	
	//pre: none
	//post: stores default values 
	//constructor
	stack()
	{
		data = new T[MAX];
		capacity = MAX;
		count = 0;
	}
	
	//pre: initialized stack
	//post: will delete the data 
	//destructor
	~stack()		
	{
		delete [] data;
	}
	
	//pre: a stack that already contains data 
	//post: a copy of that stack
	//copy constructor
	stack(const stack<T> & copy)
	{
		capacity = copy.capacity;
		count = copy.count;

		data = new T[capacity];
		for (int i = 0; i < count; i++)
		{
			data[i] = copy.data[i];
		}
	}

	//pre: a stack with values in it
	//post: same as copy constructor will return copy
	//= overload operator
	stack<T> & operator =(const stack<T> & swag)
	{
		delete [] data;

		capacity = copy.capacity;
		count = copy.count;

		data = new T[capacity];
		for (int i = 0; i < count; i++)
		{
			data[i] = copy.data[i];
		}
	}

	//pre: a stack with at least one number in it
	//post: will take the top off
	void pop()	
	{
		if(!isEmpty())
		{
			count--;
		}
	}
	
	//pre: none
	//post: place into stack
	void push(T swag)
	{
		if(isFull())
			resize();
		
		data[count] = swag;
		count++;
	}

	//pre: none
	//post: checks the top
	T top()
	{
		return data[count - 1];
	}

	//pre: none
	//post: checks if stack is empty
	bool isEmpty()
	{
		return count == 0;
	}

	//pre: none
	//post: checks to see if full
	bool isFull()
	{
		return count == capacity;
	}

	//pre: a stack that has numbers in it 
	//post: resizes the array
	void resize()
	{
		int new_capswag = capacity + 10;
		T * temp;

		temp = new T[new_capswag];
		
		for (int i = 0; i < capacity; i++)
		{
			temp[i] = data[i];
		}

		delete [] data;
		data = temp;

		capacity = new_capswag;
	}

	
private:
	T* data;			//the information of the stack
	int capacity;		//how big the stack is 
	int count;			//how much is in the stack
};

