/*
 * Read a clip consisting of a set of MXF OP-Atom files
 *
 * Copyright (C) 2009, British Broadcasting Corporation
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

#ifndef __OPATOM_CLIP_READER_H__
#define __OPATOM_CLIP_READER_H__

#include <vector>
#include <map>

#include "OPAtomTrackReader.h"


class OPAtomClipReader
{
public:
    static std::pair<OPAtomOpenResult, std::string> Open(const std::vector<std::string> &track_filenames,
                                                         OPAtomClipReader **clip_reader);
    static std::string ErrorToString(OPAtomOpenResult result);

public:
    ~OPAtomClipReader();

public:
    int64_t GetDuration();
    int64_t DetermineDuration();
    int64_t GetPosition();
   const  mxfpp::GenericSoundEssenceDescriptor *getFile_descriptor();

    const OPAtomContentPackage* Read();

    bool Seek(int64_t position);

    bool IsEOF();


    const std::vector<OPAtomTrackReader*>& GetTrackReaders() { return mTrackReaders; }

private:
    OPAtomClipReader(const std::vector<OPAtomTrackReader*> &track_readers);

private:
    OPAtomContentPackage mContentPackage;
    const mxfpp::GenericSoundEssenceDescriptor *msound_descriptor;
    std::vector<OPAtomTrackReader*> mTrackReaders;

    int64_t mPosition;
    int64_t mDuration;
};



#endif

