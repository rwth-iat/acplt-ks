/* -*-plt-c++-*- */

/*
 * Copyright (c) 1996, 1997, 1998
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

/* Author : Markus Juergens <markusj@plt.rwth-aachen.de> */

/////////////////////////////////////////////////////////////////////////////

#include "ks/histdomain.h"

/////////////////////////////////////////////////////////////////////////////

PLT_IMPL_RTTI1(KssHistoryDomain, KssSimpleDomain);
PLT_IMPL_RTTI1(KssHistoryPart, KssVariable);

/////////////////////////////////////////////////////////////////////////////

bool
KssHistoryDomain::addPart(KsString id,
                          KS_VAR_TYPE vtype,
                          KsString comment)
{
    KssHistoryPart *p =
        new KssHistoryPart(id, getCreationTime(),
                           vtype, comment);

    return addChild(p);
}

/////////////////////////////////////////////////////////////////////////////

#if 0
bool 
KssHistoryDomain::addPart(KsString id, 
                          enum_t flags, 
                          KS_SELECTOR_TYPE sel_type,
                          KS_VAR_TYPE var_type)
{
    PartInfo inf(id, flags, sel_type);

    if( _parts.add( inf ) ) {
        KsString comment;
        if( flags & BOTH ) {
            comment = "Maskable and readable";
        } else if( flags & MASKABLE ) {
            comment = "Maskable";
        } else if( flags & READABLE ) {
            comment = "Readable";
        } else {
            comment = "No access";
        }

        KssHistoryPart *p = 
            new KssHistoryPart(id, getCreationTime(),
                               var_type, comment);

        return addCommObject(p);
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////////

KS_RESULT 
KssHistoryDomain::parseArgs(const KsGetHistParams &params,
                            KsGetHistResult &result)
{
}
#endif

/////////////////////////////////////////////////////////////////////////////

KsSelectorHandle 
KssHistoryDomain::getSelector(const KsGetHistParams &params,
                              KsString id)
{
    PltArrayIterator<KsGetHistItem> it(params.items);

    for( ; it; ++it) {
        if( it->part_id == id ) {
            return it->sel;
        }
    }

    return KsSelectorHandle();
}

/////////////////////////////////////////////////////////////////////////////
// EOF histdomain.cpp
/////////////////////////////////////////////////////////////////////////////





