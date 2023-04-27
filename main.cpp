// Stephen Saffioti
// Program 5: Threads Implementation
// Due: 4/30/23

#include <iostream>
#include <thread>
#include "StringSearch.h"

using namespace std;

int main()
{
    StringSearch obj1("Hello world!", "world");
    StringSearch obj2("Hello world!", "foo");
    StringSearch obj3("Hello world!", "!");

    thread t1( &StringSearch::brute, &obj1 );
    thread t2( &StringSearch::boyerMoore, &obj2 );
    thread t3( &StringSearch::knuthMorrisPratt, &obj3 );

    t1.join();
    t2.join();
    t3.join();

    cout << "Brute Force Algorithm (Hello world!, world) :  " << obj1.getBruteResult() << endl;
    cout << "Boyer Moore Algorithm (Hello world!, foo) :  " << obj2.getBoyerMooreResult() << endl;
    cout << "Knuth, Morris, Pratt Algorithm (Hello world!, !) :  " << obj3.getKnuthMorrisPrattResult() << endl;

    return 0;
}
