#ifndef __AOC_DAY_1__
#define __AOC_DAY_1__

#include "aoc_day.h"

namespace Day1
{
    class Dial
    {
        private:
            int m_position;
            int m_number_times_at_zero;
            int m_number_times_ending_at_zero;
        public:
            Dial();
            ~Dial();
            void process_move(string move);
            int get_number_times_at_zero();
            int get_number_times_ending_at_zero();
    };
}

class AocDay1 : public AocDay
{
    private:
        vector<string> read_input(string filename);
    public:
        AocDay1();
        ~AocDay1();
        string part1(string filename, vector<string> extra_args);
        string part2(string filename, vector<string> extra_args);
};

#endif
