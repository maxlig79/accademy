#include"DynamicStringArray.h"
#include<iostream>
#include<string>
//default constructor that sets the dynamic array to nullptr and sets size to 0
DynamicStringArray::DynamicStringArray () : size {0}, dynamicArray {nullptr} 
{
} 

//a function that return size
int DynamicStringArray::getSize() const
{
    return size;
}

//function creates a new dynamic array one element larger than dynamicArray and copy all element into the new array
void DynamicStringArray::addEntry(const string &String)
{
    string *newdynamicArray=new string[size+1]; 
    for(int i=0;i<size;i++)
    {
        newdynamicArray[i]=dynamicArray[i];
    }
    newdynamicArray[size]=String;
    delete[] dynamicArray;
    dynamicArray=newdynamicArray;
    size++;
}
//the function boolean should search dynamicArray for the string
bool DynamicStringArray::deleteEntry(const string &String)
{
        bool found=0;
        int i;      
        for(i=0;i<size;i++)
        {
            if(String==dynamicArray[i])
            {
                found=1;
                break;
            }
        }
        if(found==1)
        {
            string *temp=dynamicArray;
            dynamicArray=new string[size -1];
            for(int j;j<size;j++)
            {   
                if(j<i)
                {
                    dynamicArray[j]==temp[j];
                }
                else if(j>i)
                {
                    dynamicArray[j-1]=temp[j];
                }
            }
            size --;
        }
           
        return found;
}
string DynamicStringArray::getEntry(const int index) const
{
        if(index>=size)
        {
            return " ";
        }
        else
        {
            return dynamicArray[index];
        }
}

//A copy constructor

DynamicStringArray::DynamicStringArray(const DynamicStringArray &obj)
{
    size = obj.getSize();
	dynamicArray = new std::string[size];
	for(int i = 0; i < size; i++)
    {
		dynamicArray[i] = obj.getEntry(i);
	}

}

//Overload

DynamicStringArray &DynamicStringArray::operator=(const DynamicStringArray &obj)
{
    if (&obj != this)
    {
        delete[] dynamicArray;
        size = obj.size;
        dynamicArray = new string[size];
        
        for (int i = 0; i < size; i++)
        {
            dynamicArray[i] = obj.dynamicArray[i];
        }
    }
    return *this;
}


//destructor
DynamicStringArray::~DynamicStringArray()
{
    delete[] dynamicArray;
}

