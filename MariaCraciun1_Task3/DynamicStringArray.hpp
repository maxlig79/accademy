#pragma once

#include<iostream>
#include<string>
#include<vector>

class DynamicStringArray {
private:
    int size ;
    std::string *dynamicArray ;

public:
    DynamicStringArray () ;
    DynamicStringArray ( const std::vector < std::string > &str) ;
    DynamicStringArray ( const DynamicStringArray &obj ) ;
    DynamicStringArray ( DynamicStringArray &&obj ) ;
    DynamicStringArray & operator = ( const DynamicStringArray &obj ) ;
    DynamicStringArray & operator = ( DynamicStringArray &&obj ) ;
    int getLength () const ;
    void addEntry ( const std::string &str ) ;
    bool deleteEntry ( const std::string &str ) ;
    std::string *getEntry ( const int index ) ;
    ~DynamicStringArray () ; 
};