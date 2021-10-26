#ifndef COUNTER_H
#define COUNTER_H
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <stdexcept>

template <class T>
class Counter {
    public:
        Counter();                              // initializes empty Counter<T>
        Counter(std::vector<T> vals);           // initialize Counter<T> with vector<T> vals
        int Count();                            // access the total of all counts so far
        int Count(T key);                       // access the count associated with any object T, even for values of T that have not been counted
        int Count(T min, T max);                // access the total of all couns for objects T given a certain range (inclusive T min and exclusive T max)
        void Remove(T key);                     // remove the object T from the Counter
        void Increment(T key);                  // increment the count of an object T by one
        void Increment(T key, int n);           // increment the count of an object T by n
        void Decrement(T key);                  // decrement the count of an object T by one
        void Decrement(T key, int n);           // decrement the count of an object T by n
        T MostCommon();                         // get the most commonly occuring object of type T(object with highest count) If Counter is empty this method should throw domain error
        std::vector<T> MostCommon(int n);       // get the n most commonly occuring objects of type T (object with highest count)
        T LeastCommon();                        // get the least commonly occuring object of type T (object with lowest count) If the counter is empty this method should throw domain error
        std::vector<T> LeastCommon(int n);      // get the n least commonly occuring objects of type T
        std::map<T,double> Normalized();        // access nomalized weights for all objects of type T seen so far
        std::set<T> Keys() const;               // access the set of all keys in the Counter
        std::vector<int> Values() const;        // access the collection of all values in the Counter
    private:    
        std::map<T,int> count_;
};

/**
 * Constructor, creates an empty Counter<T>
 * @param none
 * @return none
*/
template <class T>
Counter<T>::Counter(){

}

/**
 * Paramaterized constructor, creates an Counter<T> map,
 * Gives keys that are not already in the map a value of 1,
 * Increments a key's value if it appears multiple times in vector<T> vals
 * @param none
 * @return none
*/
template <class T>
Counter<T>::Counter(std::vector<T> vals){
    for(int i=0;i<vals.size();i++){
        if(count_.find(vals[i])==count_.end()){
            count_[vals[i]]=1;
        } else {
            Increment(vals[i]);
        }
    }
}

/**
 * Loops through the Counter<T> map and adds each occurence of each key
 * @param none
 * @return int: total amount of occurences of each key in Counter<T>
*/
template <class T>
int Counter<T>::Count(){
    int result=0;
    typename std::map<T, int>::iterator it;
    for(it=count_.begin();it!=count_.end();it++){
        result+=it->second;
    }
    return result;
}

/**
 * Loops through the Counter<T> map to find key and returns number of occurences of that key
 * The function returns 0 if the key 'T key' is not found in the map
 * @param T key: key of the key in then map that the function is searching for
 * @return int: amount occurences of T key in Counter<T>
*/
template <class T>
int Counter<T>::Count(T key){
    typename std::map<T, int>::iterator it = count_.find(key);
    if(it!=count_.end()){
        return it->second;
    } else {
        return 0;
    }
}

/**
 * If the key 'T min' or 'T max' does not exist, the function returns 0
 * If the key 'T max' is not after 'T min' in the map, the function returns 0
 * Otherwise, T min and T max are a valid range and the number of occurences
 * of each key in the range is added together
 * @param T min, T max: keys in the map that represent the range of keys to sum the number of occurences of each key
 * @return int: total amount of occurences in the range
*/
template <class T>
int Counter<T>::Count(T min,T max){
    int result=0;
    bool exists = false;
    bool found = false;
    if(count_.find(min)!=count_.end()&&count_.find(max)!=count_.end()) exists = true;
    if(!exists){
        return 0;
    }
    typename std::map<T, int>::iterator it;

    for(it=count_.find(min);it!=count_.end();it++){
        if(it==count_.find(max)){
            found = true;
            break;
        }
        result+=it->second;
    }
    
    if(!found){
        return 0;
    }
    return result;
}

/**
 * Finds a key and removes it from the map if the key exists
 * @param T key: the key of the key in the map to be removed
 * @return none
*/
template <class T>
void Counter<T>::Remove(T key){
    typename std::map<T, int>::iterator it = count_.find(key);
    if(it!=count_.end()){
        count_.erase(it);
    }
}

/**
 * If the key exists in the map, it is found then its value is increased by 1
 * If the key does not exist, then it is added to the map with a value of 1
 * @param T key: key of the key in the map to be incremented
 * @return none
*/
template <class T>
void Counter<T>::Increment(T key){
    typename std::map<T, int>::iterator it = count_.find(key);
    if(it!=count_.end()){
        it->second+=1;
    } else {
        count_[key] = 1;
    }
}  

/**
 * If the key exists in the map, it is found then its value is increased by n
 * If the key does not exist, then it is added to the map with a value of n
 * @param T key: key of the key in the map to be incremented, int n: number to increment the key by
 * @return none
*/
template <class T>
void Counter<T>::Increment(T key, int n){
    typename std::map<T, int>::iterator it = count_.find(key);
    if(it!=count_.end()){
        it->second+=n;
    } else {
        count_[key] = n;
    }
}

/**
 * If the key exists, 1 is subtracted from its number of occurences
 * If a key's value is decremented below 1 occurence, then it is removed from the map
 * @param T key: key of the key in the map to be decremented
 * @return none
*/
template <class T>
void Counter<T>::Decrement(T key){
    typename std::map<T, int>::iterator it = count_.find(key);
    if(it!=count_.end()){
        it->second-=1;
        if(it->second<1){
            Remove(key);
        }
    }
}

/**
 * If the key exists, n is subtracted from its number of occurences
 * If a key's value is decremented below 1 occurence, then it is removed from the map
 * @param T key: key of the key in the map to be decremented, int n: number to decrement the key by
 * @return none
*/
template <class T>
void Counter<T>::Decrement(T key,int n){
    typename std::map<T, int>::iterator it = count_.find(key);
    if(it!=count_.end()){
        it->second-=n;
        if(it->second<1){
            Remove(key);
        }
    }
}

/**
 * Loops through the map and finds the key with the maximum value
 * by comparing a key's value with the previous key with the highest value
 * This function throws a domain error if the Counter is empty
 * @param none
 * @return T, returns the key of the key in the map with the most occurences
*/
template <class T>
T Counter<T>::MostCommon(){
    if(count_.empty()){
        throw std::domain_error("Domain Error: The counter is empty");
    } else {
        T max_key;
        int max=-1;
        typename std::map<T,int>::iterator it;
        for(it=count_.begin();it!=count_.end();it++){
            if(it->second>=max){
                max = it->second;
                max_key = it->first;
            }
        }
        return max_key;
    }
}

/**
 * Creates a map<T,int> temp to preserve the state of the count_ map
 * Finds the most common key in count_ then removes that key after it
 * is pushed to the vector<T> keys, and loops until keys is of size n
 * The count_ map is then set back to the state it was when the function was called
 * @param int n: number of keys to put into the vector of keys with most occurences
 * @return vector<T>: returns vector of n keys with type T that have the most occurences in the map
*/
template <class T>
std::vector<T> Counter<T>::MostCommon(int n){
    std::vector<T> keys;
    if(!count_.empty()){
        std::map<T,int> temp = count_;
        while(keys.size()!=n){
            keys.push_back(MostCommon());
            Remove(MostCommon());
        }
        count_ = temp;
    }
    return keys;
}

/**
 * Loops through the map and finds the key with the minimum value
 * by comparing a key's value with the previous key with the lowest value
 * This function throws a domain error if the Counter is empty
 * @param none
 * @return T, returns the key of the key in the map with the least occurences
*/
template <class T>
T Counter<T>::LeastCommon(){
    if(count_.empty()){
        throw std::domain_error("Domain Error: The counter is empty");
    } else {
        T min_key;
        int min=1000000000;
        typename std::map<T,int>::iterator it;
        for(it=count_.begin();it!=count_.end();it++){
            if(it->second<min){
                min = it->second;
                min_key = it->first;
            }
        }
        return min_key;
    }
}

/**
 * Creates a map<T,int> temp to preserve the state of the count_ map
 * Finds the least common key in count_ then removes that key after it
 * is pushed to the vector<T> keys, and loops until keys is of size n
 * The count_ map is then set back to the state it was when the function was called
 * @param int n: number of keys to put into the vector of keys with least occurences
 * @return vector<T>: returns vector of n keys with type T that have the least occurences in the map
*/
template <class T>
std::vector<T> Counter<T>::LeastCommon(int n){
    std::vector<T> keys;
    if(!count_.empty()){
        std::map<T,int> temp = count_;
        while(keys.size()!=n){
            keys.push_back(LeastCommon());
            Remove(LeastCommon());
        }
        count_ = temp;
    }
    return keys;
}

/**
 * Changes the number of occurences in each key to a percentage of type double
 * that represents the percent amount of occurences the key has compared to the
 * total number of occurences in the map
 * @param none
 * @return map<T,double>: map of Counter<T> with new percentage of occurences
*/
template <class T>
std::map<T,double> Counter<T>::Normalized(){
    double total = Count()*1.0;
    std::map<T,double> normal;
    typename std::map<T, int>::iterator it;
    for (it = count_.begin();it!=count_.end();it++){
        normal[it->first] = (double) it->second / total;
    }
    return normal;
}

/**
 * Puts all of the keys in the map into a set<T>
 * @param none
 * @return set<T>: set of all keys in the map
*/
template <class T>
std::set<T> Counter<T>::Keys() const{
    std::set<T> keys;
    typename std::map<T, int>::const_iterator it;
    for (it = count_.begin();it!=count_.end();it++){
        keys.insert(it->first);
    }
    return keys;
}

/**
 * Puts all of the values in the map into a vector<int>
 * @param none
 * @return vector<int>: vector of all values in the map
*/
template <class T>
std::vector<int> Counter<T>::Values() const{
    std::vector<int> vals;
    typename std::map<T, int>::const_iterator it;
    for (it = count_.begin();it!=count_.end();it++){
        vals.push_back(it->second);
    }
    return vals;
}

/** Overloads the << operator to allow a Counter<T> map to be outputted
 * @param ostream& os: output of the function, const Counter<U> &b: Counter object being outputted
 * @return ostream& os: output stream that represents the map of the Counter
*/
template <class U>
std::ostream& operator<<(std::ostream& os, const Counter<U> &b){
    std::set<U> keys = b.Keys();
    std::vector<int> vals = b.Values();
    typename std::set<U>::iterator it;
    int index = 0;
    os << "{";
    for(it=keys.begin();it!=keys.end();it++){
        os << *it << ":" << vals[index]<<",";
        index++;
    }
    os<<"}"<<std::endl;
    return os;
}

// example struct to test the template with a user created struct
struct Person{
    std::string name;
    int age;
    
    bool operator==(const Person& a) const{
        return (name == a.name && age == a.age);
    }

    bool const operator<(const Person &a) const{
        return name < a.name || (name == a.name && age < a.age);
    }
};

#endif