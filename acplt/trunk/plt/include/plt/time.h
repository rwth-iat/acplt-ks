/* -*-plt-c++-*- */
/*
 * Copyright (c) 1996, 1997
 * Chair of Process Control Engineering,
 * Aachen University of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must print or display the above
 *    copyright notice either during startup or must have a means for
 *    the user to view the copyright notice.
 * 3. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the Chair of Process Control Engineering nor the
 *    name of the Aachen University of Technology may be used to endorse or
 *    promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE CHAIR OF PROCESS CONTROL ENGINEERING
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CHAIR OF PROCESS CONTROL
 * ENGINEERING BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* Author: Martin Kneissl <martin@plt.rwth-aachen.de> */
#ifndef PLT_TIME_INCLUDED
#define PLT_TIME_INCLUDED

#include "plt/debug.h"

#include <sys/time.h>

//////////////////////////////////////////////////////////////////////
// a PltTime object is a timeval with some operations added
//////////////////////////////////////////////////////////////////////

struct PltTime : public timeval {
    // Constructors
    PltTime(long seconds = 0, long useconds = 0);
    PltTime(struct timeval &tv);

#if PLT_DEBUG_INVARIANTS
    bool invariant() const;
#endif

    // Make representation canonical
    void normalize();

    // adding and substracting times
    PltTime & operator += (const PltTime &t);
    PltTime & operator -= (const PltTime &t);
};

PltTime operator + (const PltTime &t1, const PltTime &t2);
PltTime operator - (const PltTime &t1, const PltTime &t2);

//
// Comparison operators.
//

bool operator == (const PltTime &t1, const PltTime &t2);
bool operator != (const PltTime &t1, const PltTime &t2);
bool operator < (const PltTime &t1, const PltTime &t2);
bool operator > (const PltTime &t1, const PltTime &t2);
bool operator <= (const PltTime &t1, const PltTime &t2);
bool operator >= (const PltTime &t1, const PltTime &t2);


//////////////////////////////////////////////////////////////////////
// INLINE IMPLEMENTATION
//////////////////////////////////////////////////////////////////////

#if PLT_DEBUG_INVARIANTS
inline bool
PltTime::invariant() const
{
    return 
        tv_sec >= 0 
        && 0 <= tv_usec && tv_usec < 1000000;
}
#endif

//////////////////////////////////////////////////////////////////////

inline bool
operator == (const PltTime &t1, const PltTime &t2)
{
    return 
            t1.tv_usec == t2.tv_usec
        &&  t1.tv_sec  == t2.tv_sec;
}

//////////////////////////////////////////////////////////////////////

inline bool
operator <= (const PltTime &t1, const PltTime &t2)
{
    return 
            t1.tv_sec  <  t2.tv_sec
        || ( t1.tv_sec  == t2.tv_sec
          && t2.tv_usec <= t2.tv_usec);
}

//////////////////////////////////////////////////////////////////////

inline bool
operator != (const PltTime &t1, const PltTime &t2)
{
    return !(t1==t2);
}

//////////////////////////////////////////////////////////////////////

inline bool
operator >= (const PltTime &t1, const PltTime &t2)
{
    return t2 <= t1;
}

//////////////////////////////////////////////////////////////////////

inline bool
operator > (const PltTime &t1, const PltTime &t2)
{
    return !(t1 <= t2);
}

//////////////////////////////////////////////////////////////////////

inline bool
operator < (const PltTime &t1, const PltTime &t2)
{
    return !(t2 <= t1);
}

//////////////////////////////////////////////////////////////////////

inline void
PltTime::normalize() 
{
    while (tv_usec < 0) {
        tv_usec += 1000000;
        tv_sec  -= 1;
    }
    while (tv_usec >= 1000000) {
        tv_usec -= 1000000;
        tv_sec  += 1;
    }
    PLT_CHECK_INVARIANT();
}


//////////////////////////////////////////////////////////////////////

inline
PltTime::PltTime(long seconds, long useconds)
{ 
    tv_sec = seconds;
    tv_usec = useconds;
    normalize();
    PLT_CHECK_INVARIANT();
}

//////////////////////////////////////////////////////////////////////

inline
PltTime::PltTime(struct timeval &tv)
{
    tv_sec = tv.tv_sec;
    tv_usec = tv.tv_usec; 
    normalize();
    PLT_CHECK_INVARIANT();
}

//////////////////////////////////////////////////////////////////////

inline PltTime &
PltTime::operator += (const PltTime & t)
{
    tv_usec += t.tv_usec;
    tv_sec  += t.tv_sec;
    normalize();
    PLT_CHECK_INVARIANT();
    return *this;
}

//////////////////////////////////////////////////////////////////////

inline PltTime &
PltTime::operator -= (const PltTime & t)
{
    PLT_PRECONDITION(*this >= t);
    if (tv_usec < t.tv_usec) {
        // this->tv_usec borrows one second
        tv_usec += 1000000;
        --tv_sec;
    }
    tv_usec -= t.tv_usec;
    tv_sec  -= t.tv_sec;
    normalize();
    PLT_CHECK_INVARIANT();
    return *this;
}    

//////////////////////////////////////////////////////////////////////

inline PltTime
operator + (const PltTime & t1, const PltTime & t2) 
{
    PltTime t(t1);
    t += t2;
    return t;
}

//////////////////////////////////////////////////////////////////////

inline PltTime
operator - (const PltTime & t1, const PltTime & t2) 
{
    PltTime t(t1);
    t -= t2;
    return t;
}

//////////////////////////////////////////////////////////////////////

#endif // PLT_TIME_INCLUDED
