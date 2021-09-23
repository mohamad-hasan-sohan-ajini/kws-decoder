#ifndef COUNTER_H
#define COUNTER_H

#include <map>
#include <vector>

using namespace std;

class Counter
{
    map<string, float> counter;

    public:
        map<string, float> get_counter();
        void set_item(string, float);
        float get_value(string);
        void accumulate_prob(string, float);
        vector<string> get_keys();
        vector<float> get_normalized_probs(float beta);
        float get_normalized_prob(float beta, string key);
        Counter operator+(Counter);
        float operator[](string);
        void clear();
};

#endif
