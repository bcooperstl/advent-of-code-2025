#ifndef __AOC_DAY_2__
#define __AOC_DAY_2__

#include "aoc_day.h"

namespace Day2
{
    class Range
    {
        private:
            static long long int m_low_high_divisor_lookup[11][3];
            string m_low_str;
            string m_high_str;
            long long int m_low;
            long long int m_high;
            long long int get_sum_invalid_ids(long long int low, long long int high, int length);
        public:
            Range(string low, string high);
            ~Range();
            long long int get_sum_invalid_ids();
    };
}

class AocDay2 : public AocDay
{
    private:
        vector<Day2::Range> read_input(string filename);
    public:
        AocDay2();
        ~AocDay2();
        string part1(string filename, vector<string> extra_args);
        //string part2(string filename, vector<string> extra_args);
};

#endif
