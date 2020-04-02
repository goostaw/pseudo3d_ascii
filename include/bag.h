#ifndef bag_h
#define bag_h

template<typename T>
class Bag 
{
	T* _ptr;
	int _capacity;
	int _next;

  public:
	Bag();
	~Bag();
	void push_back( const T& );
	int size(){ return _next; }
	int capacity(){ return _capacity; }
	void clear();
	void roll_down();
	void resize( const int& );
	T& at( int );
	T& operator[]( int i ){ return _ptr[i]; }
};
/*******************************************/
template<typename T>
Bag<T>::Bag() : _ptr( NULL ), _capacity(0), _next(0)
{}
/*******/
template<typename T>
Bag<T>::~Bag()
{
	if ( _ptr ) delete []_ptr;
	_ptr = NULL;
}
/******/
template<typename T>
void Bag<T>::push_back( const T& obj )
{
	if ( _next >= _capacity )
	{
		int temp_capacity = _capacity + 5;
		T* temp = new T[temp_capacity];
		for( int i = 0; i < temp_capacity; i++ )
		{
			if ( i < _capacity ) temp[i] = _ptr[i];
			else i = temp_capacity;
		}
		if ( _ptr ) delete []_ptr;
		_ptr = temp;
		temp = NULL;
		_capacity = temp_capacity;
	}
	_ptr[_next] = obj;
	_next++;
}
/******/
template<typename T>
T& Bag<T>::at( int i )
{
	return _ptr[i];
}
template<typename T>
void Bag<T>::clear()
{
	_capacity = _next = 0;
	if ( _ptr ) delete []_ptr;
	_ptr = NULL;
}
template<typename T>
void Bag<T>::roll_down()
{
	_next = 0;
}
template<typename T>
void Bag<T>::resize( const int& s )
{
	if ( _next < s )
	{
		T* temp = new T[s];
		for( int i = 0; i < s; i++ )
		{
			if ( i < _capacity ) temp[i] = _ptr[i];
			else i = s - 1;
		}
		if ( _ptr ) delete []_ptr;
		_ptr = temp;
		temp = NULL;
		_capacity = s;
		
	}
}

#endif // bag_h
