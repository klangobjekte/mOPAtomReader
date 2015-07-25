/*
 * Test the OP-Atom reader
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define __STDC_FORMAT_MACROS    1

#include <cstdio>
#include <iostream>
#include <libMXF++/MXF.h>

#include "OPAtomClipReader.h"

using namespace std;
using namespace mxfpp;


#include <cstdint>

typedef uint8_t  CHAR;
typedef uint16_t WORD;
typedef uint32_t DWORD;

typedef int8_t  BYTE;
typedef int16_t SHORT;
typedef int32_t LONG;

typedef LONG INT;
typedef INT BOOL;


/// sample data type. int or float
/// it is compatible to WWBitFormatType on WasapiUser.h
enum WWMFBitFormatType {
    WWMFBitFormatUnknown = -1,
    WWMFBitFormatInt,
    WWMFBitFormatFloat,
    WWMFBitFormatNUM
};

struct WWMFPcmFormat {
    WWMFBitFormatType sampleFormat;
    WORD  nChannels;
    WORD  bits;
    DWORD sampleRate;
    DWORD dwChannelMask;
    WORD  validBitsPerSample;

    WWMFPcmFormat(void) {
        sampleFormat       = WWMFBitFormatUnknown;
        nChannels          = 0;
        bits               = 0;
        sampleRate         = 0;
        dwChannelMask      = 0;
        validBitsPerSample = 0;
    }

    WWMFPcmFormat(WWMFBitFormatType aSampleFormat, WORD aNChannels, WORD aBits,
            DWORD aSampleRate, DWORD aDwChannelMask, WORD aValidBitsPerSample) {
        sampleFormat       = aSampleFormat;
        nChannels          = aNChannels;
        bits               = aBits;
        sampleRate         = aSampleRate;
        dwChannelMask      = aDwChannelMask;
        validBitsPerSample = aValidBitsPerSample;
    }

    WORD FrameBytes(void) const {
        return (WORD)(nChannels * bits /8U);
    }

    DWORD BytesPerSec(void) const {
        return sampleRate * FrameBytes();
    }
};



static int WriteBytes(FILE *fpw, const char *s, DWORD bytes)
{
    int writeBytes = 0;

    writeBytes = fwrite(s, 1, bytes, fpw);
    if (bytes != writeBytes) {
        printf("write error\n");
        return 0x80070006;
    }

    return 0x00000000;
}

static int WriteInt16(FILE *fpw, short value)
{
    int32_t writeBytes = 0;

    writeBytes = fwrite(&value, 1, 2, fpw);
    if (2U != writeBytes) {
        printf("write error\n");
        return 0x80070006;
    }

    return 0x00000000;
}

static int
WriteInt32(FILE *fpw, int value)
{
    int32_t writeBytes = 0;

    writeBytes = fwrite(&value, 1, 4, fpw);
    if (4U != writeBytes) {
        printf("write error\n");
        return 0x80070006;
    }

    return 0x00000000;
}

static int
WriteWavHeader(FILE *fpw, WWMFPcmFormat &format, DWORD dataBytes)
{
    int err = 0;
    int dataChunkSize = ((dataBytes+1)&(~1)) + 4;

    WriteBytes(fpw, "RIFF", 4U);
    WriteInt32(fpw, dataChunkSize + 0x24);
    WriteBytes(fpw, "WAVE", 4U);

    WriteBytes(fpw, "fmt ", 4U);
    WriteInt32(fpw, 16);

    // fmt audioFormat size==2 1==int 3==_BUFFDATATYPE
    switch (format.sampleFormat) {
    case WWMFBitFormatInt:
        WriteInt16(fpw, 1);
        break;
    case WWMFBitFormatFloat:
        WriteInt16(fpw, 3);
        break;
    default:
        goto end;
    }

    // fmt numChannels size==2
    WriteInt16(fpw, format.nChannels);

    // fmt sampleRate size==4
    WriteInt32(fpw, format.sampleRate);

    // fmt byteRate size==4
    WriteInt32(fpw, format.BytesPerSec());

    // fmt blockAlign size==2
    WriteInt16(fpw, format.FrameBytes());

    // fmt bitspersample size==2
    WriteInt16(fpw, format.bits);

    WriteBytes(fpw, "data", 4U);
    WriteInt32(fpw, dataChunkSize);

end:
    return err;
}


int main(int argc, const char **argv)
{
    vector<string> filenames;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <mxf filename>\n", argv[0]);
        return 1;
    }

    filenames.push_back(argv[1]);

    //! Über  OPAtomClipReader::Open wird ein neues
    //! OPAtomClipReader Objekt erzeugt. Für jeden übergebenen
    //! Filenamen wird OPAtomTrackReader::Open(filename, &track_reader)
    //! aufgerufen und im Vector track_readers gespeichert.
    //! In OPAtomTrackReader::Open wird über die Klasse File openRead() aufgerufen
    //! und ein neues OPAtomTrackReader(filename,file) Objekt erzeugt.
    //! Der Konstruktor erzeugt ein neues DataModel(), AvidHeaderMetadata(data_model)
    //! Objekt. Hier wird die Factorymethode RawEssenceParser::create aufgerufen
    //! welche ein neues spezialisiertes Parser-Opbjekt ()  aus PCMEssenceParser
    //! VariableSizeEssenceParser oder FixedSizeEssenceParser auswählt und erzeugt.
    //!
    OPAtomClipReader *clip_reader;
    pair<OPAtomOpenResult, string> result = OPAtomClipReader::Open(filenames, &clip_reader);
    if (result.first != OP_ATOM_SUCCESS) {
        fprintf(stderr, "Failed to open file '%s': %s\n", result.second.c_str(),
                OPAtomClipReader::ErrorToString(result.first).c_str());
        return 1;
    }

    printf("Duration = %" PRId64 "\n", clip_reader->GetDuration());

    vector<OPAtomTrackReader*> track_readers = clip_reader->GetTrackReaders();
    OPAtomTrackReader *reader = track_readers[0];
    cout<< "main samplerate: " << clip_reader->getFile_descriptor()->getAudioSamplingRate().numerator << endl;




     Preface *preface = reader->GetHeaderMetadata()->getPreface();
     preface->getInstanceUID();
     if (preface->haveGenerationUID())
     {
         preface->getGenerationUID();
     }
     printf("Preface::Version = %u\n", preface->getVersion());
     printf("size Preface::Identifications = %d\n", (int)preface->getIdentifications().size());
     printf("size Preface::EssenceContainers = %d\n", (int)preface->getEssenceContainers().size());
     if (preface->getIdentifications().size() > 0)
     {
         Identification *identification = *preface->getIdentifications().begin();
         printf("Identification::CompanyName = '%s'\n", identification->getCompanyName().c_str());
     }


    FILE *output = fopen("/Users/admin/Music/mxf_Avid/test.wav", "wb");

    //! Wav - Header schreiben,
    WWMFPcmFormat format;
    format.sampleFormat = WWMFBitFormatInt;
    format.nChannels = clip_reader->getFile_descriptor()->getChannelCount();
    format.sampleRate = clip_reader->getFile_descriptor()->getAudioSamplingRate().numerator;
    format.bits = clip_reader->getFile_descriptor()->getQuantizationBits();
    DWORD bytes = clip_reader->getFile_descriptor()->getQuantizationBits()/8*
            clip_reader->getFile_descriptor()->getAudioSamplingRate().numerator*
            clip_reader->GetDuration()/25;
    WriteWavHeader(output,format,bytes);

    //! Files lesen:
    //! clip_reader->Read() ruft für alle
    //! Trackreaders nacheinander
    //! mTrackReaders[i]->Read(&mContentPackage)
    //! auf.
    //!content_package
    //! Contains the Raw Data
    //!
    const OPAtomContentPackage *content_package;
    while (true) {
        content_package = clip_reader->Read();
        if (!content_package) {
            if (!clip_reader->IsEOF()) {
                fprintf(stderr, "Failed to read content package\n");
            }
            break;
        }

        printf("writing %d bytes from essence offset 0x%" PRIx64"\n",
               content_package->GetEssenceDataISize(0),
               content_package->GetEssenceDataI(0)->GetEssenceOffset());

        fwrite(content_package->GetEssenceDataIBytes(0),
               content_package->GetEssenceDataISize(0), 1, output);
    }

    printf("Duration = %" PRId64"\n", clip_reader->GetDuration());

    fclose(output);

    clip_reader->Seek(0);
    content_package = clip_reader->Read();
    if (!content_package) {
        if (!clip_reader->IsEOF()) {
            fprintf(stderr, "Failed to read content package\n");
        }
    }


    delete clip_reader;

    return 0;
}
