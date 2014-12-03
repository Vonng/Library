/****************************** Module Header ******************************\
Filename:		Matlab.h
Project:		Vonng::Matlab
Digest:			Warpper For Matlab c++ API
Author:			Feng Ruohang
Create:			2014/11/25 22:36
LastModify:		2014/11/25 22:36
\****************************** Module Header ******************************/

#define _DISABLE_DRAW_SUPPORT
#ifndef _DISABLE_DRAW_SUPPORT


#ifdef NDEBUG
#define _V_DISABLE_ALL_DEBUG_MARCO
#endif

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include "Matlab.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdexcept>

using namespace Vonng;

namespace Vonng
{
    namespace Matlab
    {
        MatlabHandle::MatlabHandle()
        {
            if (!(ep = engOpen("")))
            {
                fprintf(stderr, "\nCan't start Matlab Engine");
                throw std::runtime_error("Can't start Matlab Engine!");
            }
        }

        MatlabHandle::MatlabHandle(MatlabHandle && other)
        {

        }

        MatlabHandle::~MatlabHandle()
        {
            engClose(ep);
        }

        Engine* MatlabHandle::GetInstance()
        {
            return ep;
        }

        inline cstr MatlabHandle::E(cstr cmd)
        {
            engEvalString(ep, cmd);
        }
    }
}
#endif