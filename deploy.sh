#!/bin/sh
echo "aufgerufenes Script:"
echo $0



SOURCEPATH=$(dirname $0)
echo "SOURCEPATH: "$SOURCEPATH


SOURCEPATH=$(dirname $0)

BUILDDIR=$(pwd)
echo "BUILDDIR           : " $BUILDDIR
PASSWORD=$1
#echo "PASSWORD           : "$PASSWORD


TARGET="mOPAtomReader.dylib"
echo "Target: " $TARGET
#macdeployqt  " $TARGET"




echo "rm -R /usr/local/include/mOPAtomReader"
echo $PASSWORD | sudo -S rm -R /usr/local/include/mOPAtomReader
if ! test -e /usr/local/include/mOPAtomReader
then
echo "mkdir /usr/local/include/mOPAtomReader"
echo $PASSWORD | sudo -S mkdir /usr/local/include/mOPAtomReader
fi



if ! test -e /usr/local/include/mOPAtomReader/Common
then
echo "mkdir /usr/local/include/mOPAtomReader/Common"
echo $PASSWORD | sudo -S mkdir /usr/local/include/mOPAtomReader/Common
fi

echo ""

echo "cp -f $BUILDDIR/libmOPAtomReader.a /usr/local/lib_s/libmOPAtomReader.a"
echo $PASSWORD | sudo -S cp -f $BUILDDIR/libmOPAtomReader.a /usr/local/lib_s/libmOPAtomReader.a

echo "cp -f $SOURCEPATH/FixedSizeEssenceParser.h /usr/local/include/mOPAtomReader/"
echo $PASSWORD | sudo -S cp -f $SOURCEPATH/FixedSizeEssenceParser.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/FrameOffsetIndexTable.h /usr/local/include/mOPAtomReader/"
echo $PASSWORD | sudo -S cp -f $SOURCEPATH/FrameOffsetIndexTable.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/OPAtomClipReader.h /usr/local/include/mOPAtomReader/"
echo $PASSWORD | sudo -S cp -f $SOURCEPATH/OPAtomClipReader.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/OPAtomContentPackage.h /usr/local/include/mOPAtomReader/"
echo $PASSWORD | sudo -S cp -f $SOURCEPATH/OPAtomContentPackage.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/OPAtomTrackReader.h /usr/local/include/mOPAtomReader/"
echo $PASSWORD | sudo -S cp -f $SOURCEPATH/OPAtomTrackReader.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/PCMEssenceParser.h /usr/local/include/mOPAtomReader/r"
echo $PASSWORD | sudo -S cp -f $SOURCEPATH/PCMEssenceParser.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/RawEssenceParser.h /usr/local/include/mOPAtomReader/"
echo $PASSWORD | sudo -S cp -f $SOURCEPATH/RawEssenceParser.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/VariableSizeEssenceParser.h /usr/local/include/mOPAtomReader/"
echo $PASSWORD | sudo -S cp -f $SOURCEPATH/VariableSizeEssenceParser.h /usr/local/include/mOPAtomReader/

echo "cp -f $SOURCEPATH/Common/CommonTypes.h /usr/local/include/mOPAtomReader/Common/"
echo $PASSWORD | sudo -S cp -f $SOURCEPATH/Common/CommonTypes.h /usr/local/include/mOPAtomReader/Common/

echo "cp -f $SOURCEPATH/Common/DynamicByteArray.h /usr/local/include/mOPAtomReader/Common/"
echo $PASSWORD | sudo -S cp -f $SOURCEPATH/Common/DynamicByteArray.h /usr/local/include/mOPAtomReader/Common/

echo ""

echo "cp -f $BUILDDIR/libmOPAtomReader.1.0.0.dylib /usr/local/lib"
echo $PASSWORD | sudo -S cp -f $BUILDDIR/libmOPAtomReader.1.0.0.dylib /usr/local/lib

echo "cp -f $BUILDDIR/libmOPAtomReader.1.0.dylib /usr/local/lib"
echo $PASSWORD | sudo -S cp -P $BUILDDIR/libmOPAtomReader.1.0.dylib /usr/local/lib

echo "cp -f $BUILDDIR/libmOPAtomReader.1.dylib /usr/local/lib"
echo $PASSWORD | sudo -S cp -P $BUILDDIR/libmOPAtomReader.1.dylib /usr/local/lib

echo "cp -f $BUILDDIR/libmOPAtomReader.dylib /usr/local/lib"
echo $PASSWORD | sudo -S cp -P $BUILDDIR/libmOPAtomReader.dylib /usr/local/lib

echo "cp $BUILDDIR/$TARGET to /usr/local/lib/lib$TARGET"
echo $PASSWORD | sudo -S cp $BUILDDIR/lib$TARGET /usr/local/lib/lib$TARGET

echo ""

echo "install_name_tool -id /usr/local/lib/lib$TARGET /usr/local/lib/lib$TARGET"
echo $PASSWORD | sudo -S install_name_tool -id /usr/local/lib/lib$TARGET /usr/local/lib/lib$TARGET

echo ""
