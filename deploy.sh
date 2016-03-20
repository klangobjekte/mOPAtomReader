#!/bin/sh
echo "aufgerufenes Script:"
echo $0

SOURCEPATH=$(dirname $0)
echo "SOURCEPATH: "$SOURCEPATH


SOURCEPATH=$(dirname $0)

TARGET="mOPAtomReader.dylib"
echo "Target: "$TARGET
#macdeployqt  "$TARGET"

echo "rm -R /usr/local/include/mOPAtomReader"
rm -R /usr/local/include/mOPAtomReader
if ! test -e /usr/local/include/mOPAtomReader
then
echo "mkdir /usr/local/include/mOPAtomReader"
mkdir /usr/local/include/mOPAtomReader
fi
echo "cp -f $SOURCEPATH/FixedSizeEssenceParser.h /usr/local/include/mOPAtomReader/"
cp -f $SOURCEPATH/FixedSizeEssenceParser.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/FrameOffsetIndexTable.h /usr/local/include/mOPAtomReader/"
cp -f $SOURCEPATH/FrameOffsetIndexTable.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/OPAtomClipReader.h /usr/local/include/mOPAtomReader/"
cp -f $SOURCEPATH/OPAtomClipReader.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/OPAtomContentPackage.h /usr/local/include/mOPAtomReader/"
cp -f $SOURCEPATH/OPAtomContentPackage.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/OPAtomTrackReader.h /usr/local/include/mOPAtomReader/"
cp -f $SOURCEPATH/OPAtomTrackReader.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/PCMEssenceParser.h /usr/local/include/mOPAtomReader/r"
cp -f $SOURCEPATH/PCMEssenceParser.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/RawEssenceParser.h /usr/local/include/mOPAtomReader/"
cp -f $SOURCEPATH/RawEssenceParser.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/VariableSizeEssenceParser.h /usr/local/include/mOPAtomReader/"
cp -f $SOURCEPATH/VariableSizeEssenceParser.h /usr/local/include/mOPAtomReader/
