#ifndef array_h
#define array_h

template<typename T>
class Array 
{
	T* _ptr;
	int _capacity;
	int _next;

  public:
	Array();
	~Array();
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
Array<T>::Array() : _ptr( NULL ), _capacity(0), _next(0)
{}
/*******/
template<typename T>
Array<T>::~Array()
{
	if ( _ptr ) delete []_ptr;
	_ptr = NULL;
}
/******/
template<typename T>
void Array<T>::push_back( const T& obj )
{
	if ( _next >= _capacity )
	{
		int temp_capacity = _capacity + 5;
		T* temp = new T[temp_capacity];
		for( int i = 0; i < temp_capacity; i++ )
		{
			if ( i < _capacity ) temp[i] = _ptr[i];
			else break;
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
T& Array<T>::at( int i )
{
	return _ptr[i];
}
template<typename T>
void Array<T>::clear()
{
	_capacity = _next = 0;
	if ( _ptr ) delete []_ptr;
	_ptr = NULL;
}
template<typename T>
void Array<T>::roll_down()
{
	_next = 0;
}
template<typename T>
void Array<T>::resize( const int& s )
{
	if ( _next < s )
	{
		T* temp = new T[s];
		for( int i = 0; i < s; i++ )
		{
			if ( i < _capacity ) temp[i] = _ptr[i];
			else break;
		}
		if ( _ptr ) delete []_ptr;
		_ptr = temp;
		temp = NULL;
		_capacity = s;
		
	}
}

#endif // array_h
