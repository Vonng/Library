/****************************** Module Header ******************************\
Filename:		Matlab.h
Project:		Vonng::Matlab
Digest:			Wrapper For Matlab c++ API
Author:			Feng Ruohang
Create:			2014/11/25 22:36
LastModify:		2014/11/25 22:36
\****************************** Module Header ******************************/

#define DISABLE_DRAW_SUPPORT
#ifndef DISABLE_DRAW_SUPPORT

#ifndef _V_MATLAB
#define _V_MATLAB

#ifdef NDEBUG
#define _V_DISABLE_ALL_DEBUG_MARCO
#endif

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS



#include "Matlab.h"
#include "Basic.h"
#include "engine.h"
#include "matrix.h"

constexpr const int buffer_size = 1024;

namespace Vonng
{
    namespace Matlab
    {
        class MatlabHandle
        {
        private:
            Engine*     ep;
            int*        ref_count = 0;
            char buffer[buffer_size];

        public:
            MatlabHandle();                         //Default
            //MatlabHandle(MatlabHandle& other);      //Copy
            MatlabHandle(MatlabHandle&& other);     //Move
            //operator=(MatlabHandle& other);         //Copy Assign
            bool operator=(MatlabHandle&& other);        //Move Assign

            bool operator==(MatlabHandle& other);
            ~MatlabHandle();                        //Destructor

            Engine* GetInstance();
            cstr E(cstr cmd);
        };
    }
}
#endif
#endif