#pragma once
#ifndef __TLGR_INTERNAL_H__
#define __TLGR_INTERNAL_H__

#include "tlgr.h"
#include "tlgr_specs.h"
#include "tlgr_surface.h"

/***************************************
 * Library context
 * - holds current state
 ***************************************/
struct _tlgrContext
{
    float        _range[2];
    int          _size[2];
    
    tlgrSurface* _surface;
    int          _ownsSurface;

    tlgrRequest  _request;
    void*        _user;

    tlgrSpecs    _specs;
};

/***************************************
 * Some basic memory management wrappers
 ***************************************/
#include <stdlib.h>
#include <string.h>
void* _tlgrMallocInternal(int size);

#define tlgrMalloc(x) (x*)_tlgrMallocInternal(sizeof(x));
#define tlgrMallocArray(x,n) (x*)_tlgrMallocInternal(sizeof(x)*n)
#define tlgrFree(x)   { if(x) free(x); x = 0; }

/***************************************
 * Error handling
 ***************************************/
extern tlgrReturn  g_tlgrError;
extern const char* g_tlgrErrors[];
#define tlgrReturn(x)				\
    {						\
	g_tlgrError = TLGR_##x;			\
	return TLGR_##x;			\
    }

typedef struct _col24
{
    char r;
    char g;
    char b;
} col24;

typedef struct _col32
{
    char r;
    char g;
    char b;
    char a;
} col32;

#define MIN(a,b) (a<b ? a : b)
#define MAX(a,b) (a>b ? a : b)
#define CLAMP(min, max, val) (MAX(MIN(val, max), min))

#endif/*__TLGR_INTERNAL_H__*/
