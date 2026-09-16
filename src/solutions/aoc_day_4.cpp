#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_4.h"
#include "file_utils.h"
#include "screen.h"

#define SYMBOL_PAPER_ROLL '@'
#define SYMBOL_EMPTY '.'

using namespace std;

AocDay4::AocDay4():AocDay(4)
{
}

AocDay4::~AocDay4()
{
}

vector<string> AocDay4::read_input(string filename)
{
    FileUtils fileutils;
    vector<string> data;
    
    if (!fileutils.read_as_list_of_strings(filename, data))
    {
        cerr << "Error reading in the data from " << filename << endl;
        return data;
    }
    return data;
}

int AocDay4::count_accessible_bales(Screen & layout)
{
    int count = 0;
    for (int row=layout.get_min_y()+1; row<layout.get_max_y(); row++)
    {
        for (int col=layout.get_min_x()+1; col<layout.get_max_x(); col++)
        {
            if (layout.get(col, row) == SYMBOL_PAPER_ROLL)
            {
                if (layout.num_matching_neighbors(col, row, SYMBOL_PAPER_ROLL) < 4)
                {
                    count++;
#ifdef DEBUG_DAY_4
                    cout << "Accessible bale of paper at row=" << row << " col=" << col << endl;
#endif
                }
            }
        }
    }
    return count;
}

string AocDay4::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    Screen layout;
    layout.load(data,1,1);
    layout.expand(SYMBOL_EMPTY);

#ifdef DEBUG_DAY_4
    cout << "Expanded map:" << endl;
    layout.display();
#endif
    
    ostringstream out;
    out << count_accessible_bales(layout);
    return out.str();
}

