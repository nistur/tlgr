#pragma once
#ifndef __TLGR_SURFACE_H__
#define __TLGR_SURFACE_H__

struct _tlgrSurface
{
    void* _pixels;
    int   _size[2];
};

tlgrReturn tlgrInitDefaultSurface(tlgrContext* context);

#endif/*__TLGR_SURFACE_H__*/
