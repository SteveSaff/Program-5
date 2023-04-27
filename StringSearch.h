#ifndef STRINGSEARCH_H
#define STRINGSEARCH_H

#include <string>
#include <thread>
#include <mutex>

using namespace std;

class StringSearch {
public:
    StringSearch(const string& text, const string& pattern);
    void brute();
    void boyerMoore();
    void knuthMorrisPratt();
    int getBruteResult() const;
    int getBoyerMooreResult() const;
    int getKnuthMorrisPrattResult() const;

private:
    string text_;
    string pattern_;
    int bruteResult_;
    int boyerMooreResult_;
    int knuthMorrisPrattResult_;
    mutex mutex_;
};

#endif
