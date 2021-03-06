/*
 * Copyright (C) 2008, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the British Broadcasting Corporation nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __COMMON_TYPES_H__
#define __COMMON_TYPES_H__

//#ifdef __cplusplus
//extern "C"
//{
//#endif

#include <mxf/mxf_types.h>
//#include <string>
//using namespace std;
#ifdef _WIN32
//typedef std::wstring  psnd_string;
#else
//typedef std::string  psnd_string;
#endif

/*
class Timecode
{
public:
    Timecode()
        : hour(0),
        min(0),
        sec(0),
        frame(0),
        dropFrame(false)
        {}
    Timecode(bool invalid)
    : hour(0), min(0), sec(0), frame(0), dropFrame(false)
    {
        if (invalid)
        {
            hour = -1;
        }
    }
    Timecode(int h, int m, int s, int f) : hour(h), min(m), sec(s), frame(f), dropFrame(false) {}
    Timecode(int h, int m, int s, int f, bool d) : hour(h), min(m), sec(s), frame(f), dropFrame(d) {}

    bool isValid() { return hour >= 0 && min >= 0 && sec >= 0 && frame >= 0; }

    bool operator==(const Timecode& rhs)
    {
        return hour == rhs.hour && min == rhs.min && sec == rhs.sec && frame == rhs.frame && dropFrame == rhs.dropFrame;
    }

    int hour;
    int min;
    int sec;
    int frame;
    bool dropFrame;
};
*/

const mxfRational g_4by3AspectRatio = {4, 3};
const mxfRational g_16by9AspectRatio = {16, 9};

//#ifdef __cplusplus
//}
//#endif

#endif


