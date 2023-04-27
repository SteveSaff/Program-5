#include "StringSearch.h"
#include <algorithm>
#include <vector>

using namespace std;

StringSearch::StringSearch(const string& text, const string& pattern)
    : text_(text), pattern_(pattern), bruteResult_(-1), boyerMooreResult_(-1), knuthMorrisPrattResult_(-1) {}

void StringSearch::brute() {
    for (int i = 0; i <= text_.size() - pattern_.size(); ++i) {
        bool found = true;
        for (int j = 0; j < pattern_.size(); ++j) {
            if (text_[i+j] != pattern_[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            lock_guard<mutex> lock(mutex_);
            bruteResult_ = i;
            return;
        }
    }
}

void StringSearch::boyerMoore() {
    int n = text_.size();
    int m = pattern_.size();
    vector<int> badchar(256, -1);
    for (int i = 0; i < m; ++i) {
        badchar[pattern_[i]] = i;
    }
    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern_[j] == text_[s+j]) {
            --j;
        }
        if (j < 0) {
            lock_guard<mutex> lock(mutex_);
            boyerMooreResult_ = s;
            return;
        } else {
            s += max(1, j - badchar[text_[s+j]]);
        }
    }
}

void StringSearch::knuthMorrisPratt() {
    int n = text_.size();
    int m = pattern_.size();
    vector<int> prefix(m);
    prefix[0] = 0;
    int k = 0;
    for (int i = 1; i < m; ++i) {
        while (k > 0 && pattern_[k] != pattern_[i]) {
            k = prefix[k-1];
        }
        if (pattern_[k] == pattern_[i]) {
            ++k;
        }
        prefix[i] = k;
    }
    k = 0;
    for (int i = 0; i < n; ++i) {
        while (k > 0 && pattern_[k] != text_[i]) {
            k = prefix[k-1];
        }
        if (pattern_[k] == text_[i]) {
            ++k;
        }
        if (k == m) {
            lock_guard<mutex> lock(mutex_);
            knuthMorrisPrattResult_ = i - m + 1;
            return;
        }
    }
}

int StringSearch::getBruteResult() const {
    return bruteResult_;
}

int StringSearch::getBoyerMooreResult() const {
    return boyerMooreResult_;
}

int StringSearch::getKnuthMorrisPrattResult() const {
    return knuthMorrisPrattResult_;
}
