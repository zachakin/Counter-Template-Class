/**
 * Zach Akin-Amland
 * CSCI 3010
 * HW 2 - Templating
 * 
 * This is the test file for the template of the Counter class
 * The methods of the class are tested with types int, double, char, and struct
 * The class puts the values of type T and the number of occurences of that value
 * into a map. The methods of the Counter class manipulate this map in ways such as:
 * Incrementing/Decrementing the number of occurences of a value
 * Finding the key(s) with the Most/Least number of occurences
 * Removing a key from the map
 * Normalizing the number of occurences of a value
 * 
 * Commands to run the program:
 * $ make clean
 * $ make all
 * $ ./test -s
*/
#define CATCH_CONFIG_MAIN
#include "Counter.hpp"
#include "catch.hpp"
#include <iostream>


TEST_CASE("Testing Counter Template Class", "[counter]") {
    SECTION("checking cases for empty integer Counter"){
        Counter<int> emptyCounter;
        std::cout<<emptyCounter;
        REQUIRE(emptyCounter.Count()==0);
        REQUIRE(emptyCounter.Count(30)==0);

        std::cout<<emptyCounter;
    }
    SECTION("checking cases for integer type"){
        std::vector<int> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);
        vec.push_back(40);
        Counter<int> intCounter(vec);
        intCounter.Increment(10,5);
        intCounter.Increment(20,8);
        intCounter.Increment(30,17);
        intCounter.Increment(40,3);
        std::cout<<intCounter;
        REQUIRE(intCounter.Count()==37);
        REQUIRE(intCounter.Count(30)==18);
        REQUIRE(intCounter.Count(10,30)==15);
        REQUIRE(intCounter.Count(40,10)==0);
        intCounter.Remove(40);
        REQUIRE(intCounter.Count()==33);

        intCounter.Decrement(30);
        intCounter.Decrement(20,4);
        REQUIRE(intCounter.Count()==28);

        REQUIRE(intCounter.MostCommon()==30);
        std::vector<int> mc = intCounter.MostCommon(2);
        REQUIRE(mc[0]==30);
        REQUIRE(mc[1]==10);

        REQUIRE(intCounter.LeastCommon()==20);
        std::vector<int> lc = intCounter.LeastCommon(3);
        REQUIRE(lc[0]==20);
        REQUIRE(lc[1]==10);
        REQUIRE(lc[2]==30);

        std::cout<<intCounter;
        std::map<int,double> x = intCounter.Normalized();
        typename std::map<int,double>::iterator it;
        std::cout<< "{";
        for(it=x.begin();it!=x.end();it++){
            if(it!=x.begin()&&it!=x.end()) std::cout << ",";
            std::cout << it->first <<":"<<it->second;
        }
        std::cout<<"}"<<std::endl;
    }
    SECTION("checking cases for double type"){
        std::cout<<std::endl<<std::endl;
        std::vector<double> vec;
        vec.push_back(10.75);
        vec.push_back(20.2);
        vec.push_back(30.55);
        vec.push_back(40.21);
        Counter<double> doubleCounter(vec);
        doubleCounter.Increment(10.75,5);
        doubleCounter.Increment(20.2,8);
        doubleCounter.Increment(30.55,17);
        doubleCounter.Increment(40.21,3);
        std::cout<<doubleCounter;
        REQUIRE(doubleCounter.Count()==37);
        REQUIRE(doubleCounter.Count(30.55)==18);
        REQUIRE(doubleCounter.Count(10.75,30.55)==15);
        REQUIRE(doubleCounter.Count(40.21,10.75)==0);
        doubleCounter.Remove(40.21);
        REQUIRE(doubleCounter.Count()==33);

        doubleCounter.Decrement(30.55);
        doubleCounter.Decrement(20.2,4);
        REQUIRE(doubleCounter.Count()==28);

        REQUIRE(doubleCounter.MostCommon()==30.55);
        std::vector<double> mc = doubleCounter.MostCommon(2);
        REQUIRE(mc[0]==30.55);
        REQUIRE(mc[1]==10.75);

        REQUIRE(doubleCounter.LeastCommon()==20.2);
        std::vector<double> lc = doubleCounter.LeastCommon(3);
        REQUIRE(lc[0]==20.2);
        REQUIRE(lc[1]==10.75);
        REQUIRE(lc[2]==30.55);

        std::cout<<doubleCounter;
        std::map<double,double> x = doubleCounter.Normalized();
        typename std::map<double,double>::iterator it;
        std::cout<< "{";
        for(it=x.begin();it!=x.end();it++){
            if(it!=x.begin()&&it!=x.end()) std::cout << ",";
            std::cout << it->first <<":"<<it->second;
        }
        std::cout<<"}"<<std::endl;
    }
    SECTION("checking cases for char type"){
        std::cout<<std::endl<<std::endl;
        std::vector<char> vec;
        vec.push_back('a');
        vec.push_back('b');
        vec.push_back('c');
        vec.push_back('d');
        Counter<char> charCounter(vec);
        std::cout<<charCounter;
        charCounter.Increment('a',5);
        charCounter.Increment('b',8);
        charCounter.Increment('c',17);
        charCounter.Increment('d',3);
        std::cout<<charCounter;
        REQUIRE(charCounter.MostCommon()=='c');
        REQUIRE(charCounter.LeastCommon()=='d');
        REQUIRE(charCounter.Count()==37);
        REQUIRE(charCounter.Count('c')==18);
        REQUIRE(charCounter.Count('a','c')==15);
        REQUIRE(charCounter.Count('d','a')==0);
        charCounter.Remove('d');
        REQUIRE(charCounter.Count()==33);

        charCounter.Decrement('c');
        charCounter.Decrement('b',4);
        REQUIRE(charCounter.Count()==28);
        std::cout<<charCounter;

        REQUIRE(charCounter.MostCommon()=='c');
        std::vector<char> mc = charCounter.MostCommon(2);
        REQUIRE(mc[0]=='c');
        REQUIRE(mc[1]=='a');

        REQUIRE(charCounter.LeastCommon()=='b');
        std::vector<char> lc = charCounter.LeastCommon(3);
        REQUIRE(lc[0]=='b');
        REQUIRE(lc[1]=='a');
        REQUIRE(lc[2]=='c');

        std::cout<<charCounter;
        std::map<char,double> x = charCounter.Normalized();
        typename std::map<char,double>::iterator it;
        std::cout<< "{";
        for(it=x.begin();it!=x.end();it++){
            if(it!=x.begin()&&it!=x.end()) std::cout << ",";
            std::cout << it->first <<":"<<it->second;
        }
        std::cout<<"}"<<std::endl;
    }
    SECTION("checking cases for struct type"){
        Person p1;
        p1.name="Eric";
        p1.age=18;
        Person p2;
        p2.name="Gerard";
        p2.age=20;
        Person p3;
        p3.name="Joe";
        p3.age=21;
        Person p4;
        p4.name="Mary";
        p4.age=19;

        std::cout<<std::endl<<std::endl;
        std::vector<Person> vec;
        vec.push_back(p1);
        vec.push_back(p2);
        vec.push_back(p3);
        vec.push_back(p4);
        Counter<Person> structCounter(vec);
        REQUIRE(structCounter.Count()==4);
        structCounter.Increment(p1,5);
        structCounter.Increment(p2,8);
        structCounter.Increment(p3,17);
        structCounter.Increment(p4,3);
        REQUIRE(structCounter.Count()==37);
        REQUIRE(structCounter.Count(p3)==18);
            
        CHECK(structCounter.Count(p1,p3)==15);
        CHECK(structCounter.Count(p4,p1)==0);

        structCounter.Remove(p4);
        REQUIRE(structCounter.Count()==33);
        
        structCounter.Decrement(p3);
        structCounter.Decrement(p2,4);
        REQUIRE(structCounter.Count()==28);

        REQUIRE(structCounter.MostCommon()==p3);
        std::vector<Person> mc = structCounter.MostCommon(2);
        REQUIRE(mc[0]==p3);
        REQUIRE(mc[1]==p1);

        REQUIRE(structCounter.LeastCommon()==p2);
        std::vector<Person> lc = structCounter.LeastCommon(3);
        REQUIRE(lc[0]==p2);
        REQUIRE(lc[1]==p1);
        REQUIRE(lc[2]==p3);
    }
}