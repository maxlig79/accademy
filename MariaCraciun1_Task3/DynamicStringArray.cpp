#include "DynamicStringArray.hpp"

DynamicStringArray::DynamicStringArray () : size {0}, dynamicArray {nullptr} 
{   } 

DynamicStringArray::DynamicStringArray ( const std::vector<std::string> &str ) : DynamicStringArray () 
{
    for (auto i : str ) 
        DynamicStringArray::addEntry(i);
}

DynamicStringArray::DynamicStringArray ( const DynamicStringArray &obj ) 
{
    size = obj.getLength() ;
    dynamicArray = new std::string[size] ;
    for(int i = 0; i < size; i++ ) 
        dynamicArray[i] = obj.dynamicArray[i] ;
}

DynamicStringArray::DynamicStringArray ( DynamicStringArray &&obj ) : size {obj.size}, dynamicArray{obj.dynamicArray} 
{
    obj.size = 0;
    obj.dynamicArray = nullptr;
}

DynamicStringArray &DynamicStringArray::operator = (const DynamicStringArray &obj) 
{
    if ( this != &obj )
    {
    size = obj.getLength() ;
    dynamicArray = new std::string[size] ;
        for(int i = 0; i < size; i++ )
        {
            dynamicArray[i] = obj.dynamicArray[i] ;
        }
    }
    return *this ; 
}

DynamicStringArray &DynamicStringArray::operator = ( DynamicStringArray &&obj) 
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

int DynamicStringArray::getLength () const 
{   return size;    }

void DynamicStringArray::addEntry (const std::string &str ) 
{
    std::string *tempArray = new std::string[size+1] ;
    for(int i = 0; i < size; i++ ) 
    {
        tempArray[i] = dynamicArray[i] ; 
    }
    tempArray[size] = str ;
    size++ ;
    delete[] dynamicArray;
    dynamicArray = tempArray ;
}
bool DynamicStringArray::deleteEntry (const std::string &str) 
{
    bool status = false ;
    std::string *tempArray = nullptr;
    
    for ( int i = 0; i < size; i++ ) 
    {
        if ( dynamicArray[0] == str ) 
        { 
            status = true ;
            break;
        }
    }

    if( status )
    {
        if( size > 1 )
        {
            tempArray = new std::string[size-1] ;
            int j=0 ;
            for ( int i = 0; i < size; i++ ) 
            {

                if ( dynamicArray[i] == str )
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

std::string *DynamicStringArray::getEntry ( const int index ) 
{
    if ( ( dynamicArray != nullptr ) && ( index >=0 && index < size ) )
        return &dynamicArray[index] ;
    return nullptr ;
}

DynamicStringArray::~DynamicStringArray () 
{
    if ( dynamicArray != nullptr ) 
    {
        delete[] dynamicArray ;
        dynamicArray = nullptr ;
    }
}