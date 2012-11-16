#pragma once
#ifndef __TLGR_SPECS_H__
#define __TLGR_SPECS_H__

struct _tlgrSpecs
{
    int             _dirty; // if the surface might need to be rebuilt
    
    tlgrColourDepth _depth;
};

#endif/*__TLGR_SPECS_H__*/
