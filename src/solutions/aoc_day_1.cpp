#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "aoc_day_1.h"
#include "file_utils.h"

using namespace std;

AocDay0::AocDay0():AocDay(0)
{
}

AocDay0::~AocDay0()
{
}

vector<long> AocDay1::read_input(string filename)
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

string AocDay0::part1(string filename, vector<string> extra_args)
{
    vector<string> data = read_input(filename);
    long sum = 0;
    for (vector<long>::iterator iter = data.begin(); iter != data.end(); ++iter)
    {
        sum+=*iter;
    }
    ostringstream out;
    out << sum;
    return out.str();
}
