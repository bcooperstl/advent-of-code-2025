#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_3.h"
#include "file_utils.h"

using namespace std;
using namespace Day3;

namespace Day3
{
    Bank::Bank(string input)
    {
        m_num_batteries=input.length();
        for (int i=0; i<m_num_batteries; i++)
        {
            m_batteries[i] = input[i]-'0';
        }
    }
    
    Bank::~Bank()
    {
    }
    
    int Bank::get_max_joltage()
    {
#ifdef DEBUG_DAY_3
        cout << "Finding max voltage" << endl;
#endif

        int largest_values[2];
        largest_values[0] = m_batteries[0];
        largest_values[1] = m_batteries[1];
        
#ifdef DEBUG_DAY_3
        cout << " Initial values " << largest_values[0] << "," << largest_values[1] << endl;
#endif
        for (int i=1; i<(m_num_batteries - 1); i++)
        {
            // check for largest first value
            if (m_batteries[i] > largest_values[0])
            {
#ifdef DEBUG_DAY_3
                cout << " Larger first value " << m_batteries[i] << " found at position " << i << endl;
                cout << "  second value is " << m_batteries[i+1] << endl;
#endif
                largest_values[0] = m_batteries[i];
                largest_values[1] = m_batteries[i+1];
            }
            else if (m_batteries[i] > largest_values[1])
            {
#ifdef DEBUG_DAY_3
                cout << " Larger sescond value " << m_batteries[i] << " found at position " << i << endl;
#endif
                largest_values[1] - m_batteries[i];
            }
        }
        
        // check last position - can only be second value
        if (m_batteries[m_num_batteries-1] > largest_values[1])
        {
#ifdef DEBUG_DAY_3
                cout << " Larger sescond value " << m_batteries[m_num_batteries-1] << " found at position " << m_num_batteries-1 << endl;
#endif
                largest_values[1] - m_batteries[m_num_batteries-1];
        }
        
#ifdef DEBUG_DAY_3
        cout << " Final joltage is " << (largest_values[0]*10)+largest_values[1] << endl;
#endif
        return (largest_values[0]*10)+largest_values[1];
    }
    
}

AocDay3::AocDay3():AocDay(3)
{
}

AocDay3::~AocDay3()
{
}

vector<Bank> AocDay3::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    vector<Bank> banks;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return banks;
    }
    
    for (vector<string>::iterator iter = raw_lines.begin(); iter != raw_lines.end(); ++iter)
    {
        banks.push_back(Bank(*iter));
    }
    
    return banks;
}

string AocDay3::part1(string filename, vector<string> extra_args)
{
    int total_joltage = 0;
    vector<Bank> banks = read_input(filename);
    for (vector<Bank>::iterator bank_iter = banks.begin(); bank_iter != banks.end(); ++bank_iter)
    {
        total_joltage+=(*bank_iter).get_max_joltage();
    }
    
    ostringstream out;
    out << total_joltage;
    return out.str();
}
