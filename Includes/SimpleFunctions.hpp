#ifndef __SimpleFunctions_HPP_INCLUDED__
#define __SimpleFunctions_HPP_INCLUDED__

#include "MadLibrary.hpp"
#include <ctgmath>
#include <sstream>
#include <algorithm>
#include <limits>

//Map
double MadLibrary::Map(double value, double start1, double stop1, double start2, double stop2) {
    double outgoing = start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    return outgoing;
}

//Dijkstra
template <class DataType>
uint32_t ExtractMin(std::vector<uint32_t> theList, std::vector<DataType>& distance){
    uint32_t MinDist=distance[theList[0]],TheNode=theList[0];
    for (size_t i=1;i<theList.size();i++){
        if (distance[theList[i]]<MinDist){
            MinDist=distance[theList[i]];
            TheNode=theList[i];
        }
    }
    return TheNode;
}

template <class DataType>
std::vector<DataType> TheNeighbors(std::vector<std::vector<DataType>> Graph,uint32_t node){
    std::vector<DataType> TheNeighbors;
    for (size_t i=0;i<Graph.size();i++){
        if (Graph[node][i]!=0)
        {
            TheNeighbors.push_back(i);
        }
    }
    return TheNeighbors;
}

template <class DataType>
void MadLibrary::Dijkstra(std::vector<std::vector<DataType>> Graph, uint32_t source, std::vector<uint32_t>& previous, std::vector<DataType>& distance){
    uint32_t GraphSize=Graph.size();
    previous.clear();
    distance.clear();
    for (size_t i=0; i<GraphSize;i++){
        //previous.push_back(-1);
        //distance.push_back(-1);
        previous.push_back(std::numeric_limits<uint32_t>::max());
        distance.push_back(std::numeric_limits<DataType>::max());
    }
    distance[source]=0;
    std::vector<uint32_t> theList;
    for (size_t i=0;i<GraphSize;i++){
        theList.push_back(i);
    }
    while (!theList.empty())
    {
        uint32_t temp=ExtractMin(theList,distance);
        std::vector<DataType> Neighbors=TheNeighbors(Graph,temp);
        for (size_t i=0;i<Neighbors.size();i++){
            DataType alt=distance[temp]+Graph[temp][Neighbors[i]];
            if (alt<distance[Neighbors[i]]){
                distance[Neighbors[i]]=alt;
                previous[Neighbors[i]]=temp;
            }
        }
        uint32_t pos=0;
        for (size_t i=0;i<theList.size();i++){
            if (theList[i]==temp){
                pos=i;
                break;
            }
        }
        theList.erase(theList.begin()+pos);
    }
}

template <class DataType>
void MadLibrary::Dijkstra(MadLibrary::Matrix<DataType> Graph, uint32_t source, std::vector<uint32_t>& previous, std::vector<DataType>& distance){
    Dijkstra((std::vector<std::vector<DataType>>)Graph,source,previous,distance);
}

//Abs
template <class DataType>
DataType MadLibrary::Abs(DataType data){
    if (data<0) return -1*data;
    return data;
}

//PolygonArea
template<class DataType,class DataType2>
void MadLibrary::PolygonArea(std::vector<DataType> X, std::vector<DataType> Y,DataType2 &temp) 
{ 
    // Initialze area 
    DataType2 area = 0.0; 
  
    // Calculate value of shoelace formula 
    int j = X.size() - 1;
    for (int i = 0; i < X.size(); i++) 
    { 
        area += (X[j] + X[i]) * (Y[j] - Y[i]); 
        j = i;  // j is previous vertex to i 
    } 
  
    // Return absolute value 
    temp=MadLibrary::Abs(area / 2.0); 
}

//StringToNumber
template <class DataType,class RandomAccesIterator>
void MadLibrary::StringToNumber(RandomAccesIterator begin,RandomAccesIterator end,DataType& toData){
    std::stringstream sS;
    for (auto i=begin; i != end;i++){
        sS<<*(i);
    }
    sS>>toData;
}

//NumberSize
template <class DataType>
uint32_t MadLibrary::NumberSize(DataType Number){
    unsigned int size=0;
    do{
        Number/=10;
        size++;
    }while (Number!=0);
    return size;
}

//SimplePow
template <class DataType>
DataType MadLibrary::SimplePow(DataType Number,uint32_t exp){
    if (exp==0) return (Number/Number);
    if (exp==1) return Number;
    DataType temp=Number;
    uint32_t MomentExp=1;
    std::vector<DataType> Numbers;//0->2^1, 1->2^2
    std::vector<uint32_t> Exponents;//0->1,1->2
    while (MomentExp*2<=exp)
    {
        Number*=Number;
        MomentExp*=2;
        Exponents.push_back(MomentExp);
        Numbers.push_back(Number);
    }
    for (uint32_t i=0;i<Numbers.size();i++){
        if (MomentExp+Exponents[i]<exp){
            Number*=Numbers[i];
            MomentExp+=Exponents[i];
        }
    }
    while (MomentExp<exp)
    {
        Number*=temp;
        MomentExp++;
    }
    return Number;
}

//DeleteDigit
template <class DataType>
DataType MadLibrary::DeleteDigit(DataType Number,uint32_t pos){
    return Number/MadLibrary::SimplePow(10,MadLibrary::NumberSize(Number)-pos)*MadLibrary::SimplePow(10,MadLibrary::NumberSize(Number)-pos-1)+Number%MadLibrary::SimplePow(10,MadLibrary::NumberSize(Number)-pos-1);
}

//PrimeCheck
template <class DataType>
bool MadLibrary::PrimeCheck(DataType prime){
    if (prime<=1) return false;
    if (prime==2) return true;
    if (prime%2==0) return false;
    for (DataType i = 3; i <=sqrt(prime) ; i+=2)
    {
        if (prime%i==0) return false;
        
    }
    return true;
}

//MergeSort
template<typename Iter>
void merge(Iter beg, Iter mid, Iter end)
{
    std::vector<typename Iter::value_type> temp;
    temp.reserve(std::distance(beg, end));
    Iter left = beg;
    Iter right = mid;
    while (left != mid and right != end) {
        if (*right < *left) {
            temp.emplace_back(*right++);
        }
        else {
            temp.emplace_back(*left++);
        }
    }
    temp.insert(temp.end(), left, mid);
    temp.insert(temp.end(), right, end);

    std::move(temp.begin(), temp.end(), beg);
}

template<typename Iter>
void MadLibrary::MergeSort(Iter beg, Iter end) 
{
    int size = std::distance(beg, end);
    if (size <= 1) {
        return;
    }

    auto mid = std::next(beg, size / 2);
    // sort left half
    MadLibrary::MergeSort(beg, mid);
    // sort right half
    MadLibrary::MergeSort(mid, end);
    // merge halves
    merge(beg, mid, end);
}
#endif