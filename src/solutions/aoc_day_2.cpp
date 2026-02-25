#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <set>

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
    
    long long int Range::get_sum_invalid_ids(long long int low, long long int high, long long int split_divisor)
    {
        long long int sum=0;
#ifdef DEBUG_DAY_2
        cout << "Checking for invalid ids between " << low << " and " << high << " using split divisor " << split_divisor << endl;
#endif
        if (split_divisor == 0)
        {
#ifdef DEBUG_DAY_2
            cout << " Split divisor is 0; nothing to find." << endl;
#endif            
            return 0;
        }
        
        long long int left_half_low = low / split_divisor;
        long long int left_half_high = high / split_divisor;
#ifdef DEBUG_DAY_2
        cout << " Checking left halves between " << left_half_low << " and " << left_half_high << endl;
#endif            
        for (long long int current = left_half_low; current <= left_half_high; current++)
        {
            long long int check_value = (current * split_divisor) + current;
            if ((check_value >= low) && (check_value <= high))
            {
#ifdef DEBUG_DAY_2
                cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                sum+=check_value;
            }
        }
        
        return sum;
    }
    
    long long int Range::get_sum_invalid_ids()
    {
        // low and high are either the same length or high is 1 character longer than low
        
        if (m_low_str.length() == m_high_str.length())
        {
            // if they are they same length, do simple processing of 1 range
            return get_sum_invalid_ids(m_low, m_high, m_low_high_divisor_lookup[m_low_str.length()][2]);
        }
        else
        {
            // different lengths = sum the values from the 2 ranges
            int low_len = m_low_str.length();
            int high_len = m_high_str.length();
            return   get_sum_invalid_ids(m_low, 
                                         m_low_high_divisor_lookup[low_len][1], 
                                         m_low_high_divisor_lookup[low_len][2])
                   + get_sum_invalid_ids(m_low_high_divisor_lookup[high_len][0], 
                                         m_high, 
                                         m_low_high_divisor_lookup[high_len][2]);
        }
        return 0;
    }
    
    long long int Range::get_sum_invalid_ids_expanded(long long int low, long long int high, int length)
    {
        set<long long int> invalid_ids;
        long long int left_half_low, left_half_high, check_value;
#ifdef DEBUG_DAY_2
        cout << "Checking for invalid ids between " << low << " and " << high << " with length " << length << endl;
#endif
        if (length < 2)
        {
#ifdef DEBUG_DAY_2
            cout << " Length less than 2; nothing to find." << endl;
#endif            
            return 0;
        }
        
        if (length == 2)
        {
            left_half_low = low / 10ll; // long long
            left_half_high = high / 10ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 2. checking if 1 digit repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 10ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }
        }
        
        if (length == 3)
        {
            left_half_low = low / 100ll; // long long
            left_half_high = high / 100ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 3. checking if 1 digit repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 100ll) + (current * 10ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }
        }
        
        if (length == 4)
        {
            left_half_low = low / 1000ll; // long long
            left_half_high = high / 1000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 4. checking if 1 digit repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 1000ll) + (current * 100ll) + (current * 10ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }
            left_half_low = low / 100ll; // long long
            left_half_high = high / 100ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 4. checking if 2 digits repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 100ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }
        }
        
        if (length == 5)
        {
            left_half_low = low / 10000ll; // long long
            left_half_high = high / 10000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 5. checking if 1 digit repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 10000ll) + (current * 1000ll) + (current * 100ll) + (current * 10ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }
        }
        
        if (length == 6)
        {
            left_half_low = low / 100000ll; // long long
            left_half_high = high / 100000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 6. checking if 1 digit repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 100000ll) + (current * 10000ll) + (current * 1000ll) + (current * 100ll) + (current * 10ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }

            left_half_low = low / 10000ll; // long long
            left_half_high = high / 10000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 6. checking if 2 digits repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 10000ll) + (current * 100ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }

            left_half_low = low / 1000ll; // long long
            left_half_high = high / 1000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 6. checking if 3 digits repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 1000ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }
        }

        if (length == 7)
        {
            left_half_low = low / 1000000ll; // long long
            left_half_high = high / 1000000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 7. checking if 1 digit repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 1000000ll) + (current * 100000ll) + (current * 10000ll) + (current * 1000ll) + (current * 100ll) + (current * 10ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }
        }
        
        if (length == 8)
        {
            left_half_low = low / 10000000ll; // long long
            left_half_high = high / 10000000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 8. checking if 1 digit repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 10000000ll) + (current * 1000000ll) + (current * 100000ll) + (current * 10000ll) + (current * 1000ll) + (current * 100ll) + (current * 10ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }

            left_half_low = low / 1000000ll; // long long
            left_half_high = high / 1000000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 8. checking if 2 digit repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 1000000ll) + (current * 10000ll) + (current * 100ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }

            left_half_low = low / 10000ll; // long long
            left_half_high = high / 10000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 8. checking if 4 digit repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 10000ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }
        }
        
        if (length == 9)
        {
            left_half_low = low / 100000000ll; // long long
            left_half_high = high / 100000000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 9. checking if 1 digit repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 100000000ll) + (current * 10000000ll) + (current * 1000000ll) + (current * 100000ll) + (current * 10000ll) + (current * 1000ll) + (current * 100ll) + (current * 10ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }

            left_half_low = low / 1000000ll; // long long
            left_half_high = high / 1000000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 9. checking if 3 digits repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 1000000ll) + (current * 1000ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }
        }

        if (length == 10)
        {
            left_half_low = low / 1000000000ll; // long long
            left_half_high = high / 1000000000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 10. checking if 1 digit repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 1000000000ll) + (current * 100000000ll) + (current * 10000000ll) + (current * 1000000ll) + (current * 100000ll) + (current * 10000ll) + (current * 1000ll) + (current * 100ll) + (current * 10ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }

            left_half_low = low / 100000000ll; // long long
            left_half_high = high / 100000000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 10. checking if 2 digits repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 100000000ll) + (current * 1000000ll) + (current * 10000ll) + (current * 100ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }
            
            left_half_low = low / 100000ll; // long long
            left_half_high = high / 100000ll; // long long
            
#ifdef DEBUG_DAY_2
            cout << " Length 10. checking if 5 digits repeats between " << left_half_low << " and " << left_half_high << endl;
#endif            
            for (long long int current = left_half_low; current <= left_half_high; current++)
            {
                check_value = (current * 100000ll) + current;
                if ((check_value >= low) && (check_value <= high))
                {
#ifdef DEBUG_DAY_2
                    cout << "  Invalid ID " << check_value << " found" << endl;
#endif            
                    invalid_ids.insert(check_value);
                }
            }

        }

        long long int sum=0;
        for (set<long long int>::iterator pos = invalid_ids.begin(); pos != invalid_ids.end(); ++pos)
        {
            sum+=(*pos);
        }
        
        return sum;
    }
    

    long long int Range::get_sum_invalid_ids_expanded()
    {
        // low and high are either the same length or high is 1 character longer than low
        
        if (m_low_str.length() == m_high_str.length())
        {
            // if they are they same length, do simple processing of 1 range
            return get_sum_invalid_ids_expanded(m_low, m_high, m_low_str.length());
        }
        else
        {
            // different lengths = sum the values from the 2 ranges
            int low_len = m_low_str.length();
            int high_len = m_high_str.length();
            return   get_sum_invalid_ids_expanded(m_low, 
                                         m_low_high_divisor_lookup[low_len][1], 
                                         low_len)
                   + get_sum_invalid_ids_expanded(m_low_high_divisor_lookup[high_len][0], 
                                         m_high, 
                                         high_len);
        }
        return 0;
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
    
    for (int i=0; i<data[0].size(); i+=2)
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

string AocDay2::part2(string filename, vector<string> extra_args)
{
    long long int sum = 0;
    vector<Range> data = read_input(filename);
    for (vector<Range>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        sum+= (*iter).get_sum_invalid_ids_expanded();
    }
    
    ostringstream out;
    out << sum;
    return out.str();
}
