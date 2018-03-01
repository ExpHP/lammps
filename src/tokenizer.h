/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2018) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifndef LMP_TOKENIZER_H
#define LMP_TOKENIZER_H

namespace LAMMPS_NS {

// Parser that simulates strtok() with a thread-safe API.
//
// Like strtok, it destructively modifies its input string
// by inserting NUL bytes.
class Tokenizer {
    // starting point for next search.
    char * cursor;

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // ! HACK because the current implementation uses `strtok`.         !
    // ! This makes it easier to test replacements across the codebase. !
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    bool first;

public:
    Tokenizer(char* str);

    // Equivalent to tokenizing the empty string.
    Tokenizer();

    // Set a new string to be tokenized.
    // Useful if there are multiple strings to be tokenized,
    // as this lets you reduce the number of Tokenizers you
    // need to invent names for.
    void reset(char* str);

    // Find the next non-empty string of characters not
    // contained in `delim`.  This will modify the string
    // to insert a NUL byte.
    //
    // Returns NULL if there are no tokens left.
    char* next(const char* delim);

    // int count_words(const char* delim) const;
};

}

#endif