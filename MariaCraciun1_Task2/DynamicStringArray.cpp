    #include "DynamicStringArray.hpp"


    DynamicStringArray::DynamicStringArray(){
        size=0;
        dynamicArray=nullptr;
    }
    
    DynamicStringArray::DynamicStringArray(const DynamicStringArray& obj){
        size=obj.getLength();
        dynamicArray= new std::string[size];
        for(int i=0;i<size;i++){
            dynamicArray[i]=obj.dynamicArray[i];
        }
    }
    
    DynamicStringArray &DynamicStringArray::operator=(const DynamicStringArray &obj){
        delete[] dynamicArray;
        dynamicArray=nullptr;
        size= obj.getLength();
        dynamicArray= new std::string[size];
        for(int i=0;i<size;i++){
            dynamicArray[i]=obj.dynamicArray[i];
        }
     return *this;       
    }
    int DynamicStringArray::getLength() const{
        return size;
    }
   
    void DynamicStringArray::addEntry(const std::string &str){
        
        if(size==0){
            dynamicArray= new std::string[size+1];
            dynamicArray[size]=str;
            size++;
        }
        else{
            std::string *tempArray= new std::string[size+1];
            for(int i=0;i<size;i++){
                tempArray[i]=dynamicArray[i];
            }
            size++;
            for(int i=size;i<str.size();i++){
                tempArray[i]=str[i];
                size++;
            }
            delete[] dynamicArray;
            dynamicArray=nullptr;
            dynamicArray=tempArray;
        }
    }
    bool DynamicStringArray::deleteEntry(const std::string &str){

        for(int i=0; i<size; i++){
            if(dynamicArray[i]==str)
                 return true;
        }
        std::string *tempArray = new std::string[size-1];
        int j=0;
        for(int i=0; i<size; i++){
            if(dynamicArray[i]!=str)
                tempArray[j]=dynamicArray[i];
                j++;
        }
        delete[] dynamicArray;
        dynamicArray=nullptr;
        size--;

        return true;
    }
   std::string DynamicStringArray::getEntry(const int &index) const{
       if((dynamicArray!=nullptr) && (index>=0 && index < size))
           return dynamicArray[index];

        return "";
   }

  DynamicStringArray::~DynamicStringArray(){
       //A destructor that frees up the memory allocated to the dynamic array. 
       if(dynamicArray!=nullptr){
            delete[] dynamicArray;
            dynamicArray=nullptr;
       }
   }
