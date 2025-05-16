//
// Created by frank on 5/15/25.
//

#ifndef DYNARR_H
#define DYNARR_H
#include <iostream>


//This is like a vector, but simpler
template<class T>
class DynArr {
    int length;
    T* pData;
public:
    DynArr() {
        length=0;
        pData=new T[0];
    }
    DynArr(const DynArr& theOther) {
        length=theOther.length;
        pData=new T[length];
        for(int i=0;i<length;i++) {
            pData[i]=theOther.pData[i];
        }
    }
    int getLength() {
        return length;
    }



    void insert(T value) {
        T* newData= new T[length+1];
        for(int i=0;i<length;i++) {
            newData[i]=pData[i];
        }
        newData[length]=value;
        delete[] pData;
        pData=newData;
        length++;
    }

    void deleteAt(int index) {
        T* newData= new T[length-1];
        int j=0;
        for(int i=0;i<length;i++) {
            if(i!=index)
                newData[j++]=pData[i];
        }
        delete[] pData;
        pData=newData;
        length--;
    }
    void deleteLast() {
        deleteAt(length);
    }

    void printArr() {
        try {
            std::cout<<"[";
            for(int i=0;i<length;i++)
                std::cout<<pData[i]<<",";
            std::cout<<"]\n";
        }
        catch (...) {
            std::cout<<"Unable to output! Is '<<' defined for the type?";
        }

    }

    T& last() {
        return pData[length];
    }

    int find(T& value) {
        for(int i=0;i<length;i++) {
            if (pData[i]==value) {
                return i;
            }
        }
        return -1;
    }

    T& operator[](int index) {
        return pData[index];
    }

};



#endif //DYNARR_H
