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

void AocDay4::remove_accessible_bales(Screen & layout)
{
    vector<pair<int, int>> to_remove; // pairs stored in row,col format
    
    int count = 0;
    for (int row=layout.get_min_y()+1; row<layout.get_max_y(); row++)
    {
        for (int col=layout.get_min_x()+1; col<layout.get_max_x(); col++)
        {
            if (layout.get(col, row) == SYMBOL_PAPER_ROLL)
            {
                if (layout.num_matching_neighbors(col, row, SYMBOL_PAPER_ROLL) < 4)
                {
                    to_remove.push_back(make_pair(row,col));
                }
            }
        }
    }
    vector<pair<int, int>>::iterator pos = to_remove.begin();
    while (pos != to_remove.end())
    {
        layout.set(pos->second, pos->first, SYMBOL_EMPTY);
#ifdef DEBUG_DAY_4
        cout << "Removing bale of paper at row=" << pos->first << " col=" << pos->second << endl;
#endif
        ++pos;
    }
    return;
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

string AocDay4::part2(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    
    Screen layout;
    layout.load(data,1,1);
    layout.expand(SYMBOL_EMPTY);

#ifdef DEBUG_DAY_4
    cout << "Expanded map:" << endl;
    layout.display();
#endif
    
    int current = 0;
    int total = 0;
    
    current = count_accessible_bales(layout);
    while (current > 0)
    {
#ifdef DEBUG_DAY_4
        cout << "There are " << current << " bales to remove" << endl;
#endif
        total+=current;
        remove_accessible_bales(layout);
#ifdef DEBUG_DAY_4
        cout << "Updated map:" << endl;
        layout.display();
#endif
        current = count_accessible_bales(layout);
    }
    
    ostringstream out;
    out << total;
    return out.str();
}

