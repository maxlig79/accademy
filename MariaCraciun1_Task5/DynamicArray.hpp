#include<iostream>
#include<string>
#include<vector>

template <typename T>
class DynamicArray 
{
private:
    int size ;
    T *dynamicArray ;

public:
    DynamicArray () ;
    DynamicArray ( const std::vector < T > &input) ;
    DynamicArray ( const DynamicArray < T > &obj ) ;
    DynamicArray ( DynamicArray < T > &&obj ) ;
    DynamicArray < T > & operator = ( const DynamicArray < T > &obj ) ;
    DynamicArray < T > & operator = ( DynamicArray < T > &&obj ) ;
    int getLength () const ;
    void addEntry ( const T &input) ;
    bool deleteEntry ( const T &input ) ;
    T *getEntry ( const int index ) ;
    ~DynamicArray () ; 
};

template <typename T>
DynamicArray < T > :: DynamicArray () : size { 0 }, dynamicArray { nullptr } 
{ } 

template <typename T>
DynamicArray < T > ::DynamicArray ( const std::vector < T > &input ) : DynamicArray < T >  () 
{
    for (auto i : input ) 
    DynamicArray < T > ::addEntry( i );
}

template <typename T>
DynamicArray < T > ::DynamicArray ( const DynamicArray < T >  &obj ) 
{
    size = obj.getLength() ;
    dynamicArray = new T[size] ;
    for(int i = 0; i < size; i++ ) 
    dynamicArray[i] = obj.dynamicArray[i] ;
}

template <typename T>
DynamicArray < T > ::DynamicArray ( DynamicArray < T >  &&obj ) : size {obj.size}, dynamicArray{obj.dynamicArray} 
{
    obj.size = 0;
    obj.dynamicArray = nullptr;
}

template <typename T>
DynamicArray < T > &DynamicArray < T > ::operator = (const DynamicArray < T >  &obj) 
{
    if ( this != &obj )
    {
        size = obj.getLength() ;
        dynamicArray = new T[size] ;
        for(int i = 0; i < size; i++ )
        {
            dynamicArray[i] = obj.dynamicArray[i] ;
        }
    }
    return *this ; 
}

template <typename T>
DynamicArray < T > &DynamicArray < T >::operator = ( DynamicArray < T >  &&obj) 
{
    if ( this != &obj ) 
    {
        delete[] dynamicArray ;
        dynamicArray = obj.dynamicArray ;
        size = obj.size ;
        obj.dynamicArray = nullptr ;
        obj.size = 0 ;
    }
    return *this ; 
}

template <typename T>
int DynamicArray < T > ::getLength () const 
{ 
    return size; 
}

template <typename T>
void DynamicArray < T > ::addEntry (const T &input ) 
{
    T *tempArray = new T[size+1];
    for(int i = 0; i < size; i++ ) 
    {
        tempArray[i] = dynamicArray[i]; 
    }
    tempArray[size] = input;
    size++ ;
    delete[] dynamicArray;
    dynamicArray = tempArray;
}

template<>
void DynamicArray < std::string > ::addEntry (const std::string &input ) 
{
    try
    {
        if (input == "")
        {
            throw std::invalid_argument("Non-empty string expected as input.");
        }
        std::string *tempArray = new std::string[size+1] ;
        for(int i = 0; i < size; i++ ) 
        {
            tempArray[i] = dynamicArray[i] ; 
        }
        tempArray[size] = input ;
        size++ ;
        delete[] dynamicArray;
        dynamicArray = tempArray ;
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << e.what() << '\n';
    }
}

template <typename T>
bool DynamicArray < T >::deleteEntry (const T &input) 
{
    bool status = false ;
    T *tempArray = nullptr;
    for ( int i = 0; i < size; i++ ) 
    {
        if ( dynamicArray[i] == input ) 
        { 
            status = true ;
            break;
        }
    }

    if( status )
    {
        if( size > 1 )
        {
            tempArray = new T[size-1] ;
            int j=0 ;
            for ( int i = 0; i < size; i++ ) 
            {
                if ( dynamicArray[i] == input )
                {
                    continue;
                }
                tempArray[j] = dynamicArray[i] ;
                j++ ;
            }
        }
        delete[] dynamicArray ;
        dynamicArray = tempArray ;
        size-- ;
    }
    return status ;
}

template <typename T>
T *DynamicArray < T > ::getEntry ( const int index ) 
{  
        try
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range ( "Index is out of range" );
        }
        else
        {
            return &dynamicArray[index];
        }
    }
    catch(const std::out_of_range& e)
    {
        std::cout << e.what() << '\n';
        return nullptr;
    }
}

template <typename T>
DynamicArray < T > ::~DynamicArray () 
{
    if ( dynamicArray != nullptr ) 
    {
        delete[] dynamicArray ;
        dynamicArray = nullptr ;
    }
}
