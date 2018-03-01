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

#include "tokenizer.h"

#include <cstring>
#include <utility>

using namespace LAMMPS_NS;

Tokenizer::Tokenizer(char* str)
    : cursor(str)
    , first(true)
{ }

char* Tokenizer::next(const char* delim) {
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // ! HACK use `strtok` for now to make it easier to test            !
    // ! replacements across the codebase.                              !
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (first) {
        first = false;
        return strtok(cursor, delim);
    } else {
        return strtok(NULL, delim);
    }
}

void Tokenizer::reset(char* str) {
    cursor = str;
    first = true;
}

// Factored out to allow writing `int count(const char* delim) const`.
// Returns either:
// - If one or more tokens remain:
//   (pointer to token beginning, pointer just past token's end)
// - If no tokens remain:
//   (NULL, NULL)
std::pair<char *, char *> _strtok_scan(char * cursor, const char* delim) {
    while (*cursor != '\0' && strchr(delim, *cursor)) {
        cursor++;
    }

    // Invariant: cursor not in delim.
    if (*cursor == '\0') {
        return { NULL, NULL };
    }

    // Invariant: cursor not in delim, cursor not at NUL.
    //            It must point to the token's first character.
    char * result = cursor;

    while (!strchr(delim, *(++cursor)))
    { }

    // Invariant: cursor in delim, or at NUL
    return { result, cursor };
}