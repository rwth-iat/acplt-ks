/* -*-plt-c++-*- */
/* $Header: /home/david/cvs/acplt/ks/include/ks/array_impl.h,v 1.1 1997-03-12 16:27:59 martin Exp $ */
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

//////////////////////////////////////////////////////////////////////
// Author: Martin Kneissl <martin@plt.rwth-aachen.de>
//////////////////////////////////////////////////////////////////////

#include "ks/array.h"

#include "plt/array_impl.h"

//////////////////////////////////////////////////////////////////////

template <class T>
bool
KsArray<T>::xdrDecode(XDR *xdr)
{
    PLT_PRECONDITION(xdr->x_op == XDR_DECODE);
    // retrieve size
    //
    u_long sz;
    if (! xdr_u_long(xdr, &sz) ) return false; // failed

    // adjust array size (possibly losing contents)
    //
    if (size() != sz) {
        // allocate sz elements
        PltArrayHandle<T> ha(new T[sz], PltOsArrayNew);
        if (!ha) return false; // failed
        a_array = ha;
        a_size = sz;
    }
    PLT_ASSERT(size() == sz);

    // now deserialize elements
    //
    for (size_t i=0; i < a_size; ++i) {
        if (! a_array[i].xdrDecode(xdr) ) return false; // failed
    }
    
    // success
    //
    return true;
}

//////////////////////////////////////////////////////////////////////

template <class T>
bool
KsArray<T>::xdrEncode(XDR *xdrs) const
{
    PLT_PRECONDITION(xdrs->x_op == XDR_ENCODE);
    // serialize size
    //
    u_long sz = a_size;
    if (! xdr_u_long(xdrs, &sz)) return false; // fail

    // serialize elements
    //
    for (size_t i = 0; i < a_size; ++i) {
        if (! a_array[i].xdrEncode(xdrs)) return false; // fail
    }

    // success
    //
    return true;
}
            
//////////////////////////////////////////////////////////////////////

template <class T>
KsArray<T> *
KsArray<T>::xdrNew(XDR *xdrs)
{
    PLT_PRECONDITION(xdrs->x_op == XDR_DECODE);
    bool ok;                                         
    KsArray<T> * p = new KsArray<T>(xdrs, ok);     
    if ( !ok && p) {                             
        delete p;                                
        p = 0;                                   
    }                                            
    return p;                                    
}                                                

//////////////////////////////////////////////////////////////////////

// ks/iarray.h
