#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_1.h"
#include "file_utils.h"

#define DIAL_INITIAL_POSITION 50
#define DIAL_NUM_POSITIONS 100

using namespace std;
using namespace Day1;

namespace Day1
{
    Dial::Dial()
    {
        m_position = DIAL_INITIAL_POSITION;
        m_number_times_at_zero = 0;
        m_number_times_ending_at_zero = 0;
    }
    
    Dial::~Dial()
    {
    }
    
    void Dial::process_move(string move)
    {
        char direction = move[0];
        int value = strtol(move.c_str()+1, NULL, 10);
#ifdef DEBUG_DAY_1
        cout << "Dial moving from " << m_position << " by " << value << " direction " << direction << " ";
#endif
        
        m_number_times_at_zero += (value / DIAL_NUM_POSITIONS);
        value = value % DIAL_NUM_POSITIONS;
        
        if (direction == 'L')
        {
            // moving left - subtract
            m_position = ((m_position - value) % DIAL_NUM_POSITIONS);
            if (m_position < 0)
            {
                m_position+=DIAL_NUM_POSITIONS;
            }
        }
        else if (direction == 'R')
        {
            // moving right - add
            m_position = ((m_position + value) % DIAL_NUM_POSITIONS);
        }
        else
        {
            cerr << "*****INVALID DIRECTION [" << direction << "]*****" << endl;
            return;
        }
#ifdef DEBUG_DAY_1
        cout << "ends at " << m_position << endl;
#endif
        if (m_position == 0)
        {
            m_number_times_at_zero++;
            m_number_times_ending_at_zero++;
        }
        return;
    }
    
    int Dial::get_number_times_at_zero()
    {
        return m_number_times_at_zero;
    }

    int Dial::get_number_times_ending_at_zero()
    {
        return m_number_times_ending_at_zero;
    }
}

AocDay1::AocDay1():AocDay(1)
{
}

AocDay1::~AocDay1()
{
}

vector<string> AocDay1::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> raw_lines;
    if (!fileutils.read_as_list_of_strings(filename, raw_lines))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return raw_lines;
    }
    return raw_lines;
}

string AocDay1::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    Dial dial;
    for (vector<string>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        dial.process_move(*iter);
    }
    
    ostringstream out;
    out << dial.get_number_times_ending_at_zero();
    return out.str();
}

string AocDay1::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    Dial dial;
    for (vector<string>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        dial.process_move(*iter);
    }
    
    ostringstream out;
    out << dial.get_number_times_at_zero();
    return out.str();
}
