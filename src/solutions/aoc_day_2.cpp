#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_2.h"
#include "file_utils.h"

#define Range_INITIAL_POSITION 50
#define Range_NUM_POSITIONS 100

using namespace std;
using namespace Day2;

namespace Day2
{
    long long int Range::m_low_high_divisor_lookup[11][3] = 
    {{0,0,0}, // skipping for 0
     {1,          9,         0}, // invalid for 1
     {10,         99,        10}, // valid for 2
     {100,        999,       0}, // invalid for 3
     {1000,       9999,      100}, // valid for 4
     {10000,      99999,     0}, // invalid for 5
     {100000,     999999,    1000}, // valid for 6
     {1000000,    9999999,   0}, // invalid for 7
     {10000000,   99999999,  10000}, // valid for 8
     {100000000,  999999999, 0}, // invalid for 9
     {1000000000, 9999999999, 100000}}; // valid for 10
    
    Range::Range(string low, string high)
    {
        m_low_str = low;
        m_high_str = high;
        m_low = strtoull(m_low_str.c_str(), NULL, 10);
        m_high = strtoull(m_high_str.c_str(), NULL, 10);
#ifdef DEBUG_DAY_2
        cout << "Created range from " << m_low << " to " << m_high << endl;
#endif
    }
    
    Range::~Range()
    {
    }
}

AocDay2::AocDay2():AocDay(2)
{
}

AocDay2::~AocDay2()
{
}

vector<Range> AocDay2::read_input(string filename)
{
    FileUtils fileutils;
    vector<vector<string>> data;
    vector<Range> ranges;
    char delimiters[3] = ",-";
    if (!fileutils.read_as_list_of_split_strings(filename, data, delimiters, 2, '\0', '\0'))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return ranges;
    }
    
    for (int i=0; data[0].size(); i+=2)
    {
        ranges.push_back(Range(data[0][i], data[0][i+1]));
    }
    
    return ranges;
}

string AocDay2::part1(string filename, vector<string> extra_args)
{
    long long int sum = 0;
    vector<Range> data = read_input(filename);
    for (vector<Range>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        sum+= (*iter).get_sum_invalid_ids();
    }
    
    ostringstream out;
    out << sum;
    return out.str();
}
