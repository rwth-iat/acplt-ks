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

/* Author: Markus Juergens <markusj@plt.rwth-aachen.de> */

//////////////////////////////////////////////////////////////////////

#include "ks/clntpath.h"

//////////////////////////////////////////////////////////////////////

const KsString KscPath::praefixes[KSC_MAX_REL_DEPTH+1] = {
    KsString("."),
    KsString(".."),
    KsString("../.."),
    KsString("../../.."),
    KsString("../../../.."),
    KsString("../../../../..")
};

//////////////////////////////////////////////////////////////////////
// class KscPath
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// checks following condition:
//   - path starts with slash
//   - no double slashes
//   - last character is not a slash
//
bool
KscPath::parse()
{
    const char *sz = (const char *)(*this);
    
    if(sz && *sz == '/') {

        if(!sz[1]) {
            // root
            slash_count = 0;
            last_comp = 1;
            return true;
        }

        slash_count = 1;
        last_comp = 1;

        bool repeating_slash = true;
        size_t pos = 0;

        while(sz[++pos]) {
            if(sz[pos] == '/') {
                if(repeating_slash) {
                    // doubled slash
                    return false;
                } else {
                    repeating_slash = true;
                    slash_count++;
                    last_comp = pos+1;
                }
            } else {
                repeating_slash = false;
            }
        }

        if(!repeating_slash) return true;
    }

    return false;
}

//////////////////////////////////////////////////////////////////////

KsString
KscPath::relTo(const KscPath &to, size_t maxDepth) const
{
    if(slash_count && to.slash_count) {
        // this and other path are not root
        //
        if(maxDepth > KSC_MAX_REL_DEPTH) {
            maxDepth = KSC_MAX_REL_DEPTH;
        }

        size_t last_common;
        size_t up = to.countComponents() - inCommon(to, last_common) - 1;

        if(up <= maxDepth) {
            return KsString(praefixes[up], getSubstrPtr(last_common));
        }
    } 

    // no relative path if other path or this are root or
    // distance is to big
    //
    return *this;

}

//////////////////////////////////////////////////////////////////////

size_t
KscPath::inCommon(const KscPath &other, size_t &last_common) const 
{
    const char *sz1 = (const char *)(*this);
    const char *sz2 = (const char *)other;

    size_t slashes = 0,
           pos = 0,
           lc = 0;

    while( sz1[pos] && sz1[pos] == sz2[pos] ) {
        if(sz1[pos] == '/') {
            slashes++;
            lc = pos;
        }
        pos++;
    }

    last_common = lc;

    return slashes - 1; 
}

//////////////////////////////////////////////////////////////////////
// class KscPathParser
//////////////////////////////////////////////////////////////////////

KscPathParser::operator KsString () const
{
    return KsString(host_and_server, path_and_name);
}

//////////////////////////////////////////////////////////////////////

size_t
KscPathParser::pathStart(const char *sz)
{
    if(sz && *sz == '/' && sz[1] == '/') {
        size_t pos = 2;
        // search end of first component
        //
        while(sz[pos] && (sz[pos++] != '/')) ;
        if(!sz[pos]) {
            fValid = false;
            return 0;
        }
        // search end of second component
        //
        while(sz[pos] && (sz[pos++] != '/')) ;
        if(sz[pos-1] == '/') {
            fValid = true;
            return pos;
        }
    } 
    
    fValid = false;
    return 0;
}
    
//////////////////////////////////////////////////////////////////////
// EOF clntpath.cpp
//////////////////////////////////////////////////////////////////////

    
    




