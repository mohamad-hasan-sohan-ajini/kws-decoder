#include <iostream>
#include <map>

#include "counter.h"

using namespace std;

int main()
{
    Counter counter1, counter2;

    counter1.set_item("a", 1.);
    counter1.set_item("b", 2.);
    counter2.set_item("a", 3.);

    Counter result = counter1 + counter2;
    // method 1
    map<string, float> counter = result.get_counter();
    for(map<string, float>::iterator i = counter.begin(); i != counter.end(); i++)
    {
        cout<<"key: "<<i->first<<", value: "<<i->second<<endl;
    }

    cout<<"end of program"<<endl;
    return 0;
}
