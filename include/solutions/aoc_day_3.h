#ifndef __AOC_DAY_3__
#define __AOC_DAY_3__

#include "aoc_day.h"

#define BANK_MAX_BATTERIES 100

namespace Day3
{
    class Bank
    {
        private:
            int m_num_batteries;
            char m_batteries[BANK_MAX_BATTERIES];
            int find_first_largest_pos(int start_pos, int digits_after);
        public:
            Bank(string input);
            ~Bank();
            int get_max_joltage();
            long long int get_max_large_joltage();
    };
}

using namespace Day3;

class AocDay3 : public AocDay
{
    private:
        vector<Bank> read_input(string filename);
    public:
        AocDay3();
        ~AocDay3();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
