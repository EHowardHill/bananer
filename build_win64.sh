#!/bin/bash
set -e

# Default values
EXE_NAME="glass_eyes.exe"
ICON_PATH="icon.ico"
FILE_DESCRIPTION="Glass Eyes for PC"
PRODUCT_NAME="Glass Eyes"
FILE_VERSION="1.0.0.0"
PRODUCT_VERSION="1.0.0.0"
COMPANY_NAME="Cinemint"
COPYRIGHT=""

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --name)
            EXE_NAME="$2"
            shift 2
            ;;
        --icon)
            ICON_PATH="$2"
            shift 2
            ;;
        --description)
            FILE_DESCRIPTION="$2"
            shift 2
            ;;
        --product)
            PRODUCT_NAME="$2"
            shift 2
            ;;
        --file-version)
            FILE_VERSION="$2"
            shift 2
            ;;
        --product-version)
            PRODUCT_VERSION="$2"
            shift 2
            ;;
        --company)
            COMPANY_NAME="$2"
            shift 2
            ;;
        --copyright)
            COPYRIGHT="$2"
            shift 2
            ;;
        --help)
            echo "Usage: $0 [options]"
            echo "Options:"
            echo "  --name NAME              Output executable name (default: gbaport.exe)"
            echo "  --icon PATH              Path to .ico file for executable icon"
            echo "  --description TEXT       File description"
            echo "  --product NAME           Product name"
            echo "  --file-version X.X.X.X   File version (default: 1.0.0.0)"
            echo "  --product-version X.X.X.X Product version (default: 1.0.0.0)"
            echo "  --company NAME           Company name"
            echo "  --copyright TEXT         Copyright notice"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

rm -f "$EXE_NAME"

python3 scripts/preprocess.py
python3 scripts/preprocess_music.py

CC=x86_64-w64-mingw32-g++
WINDRES=x86_64-w64-mingw32-windres
SRC_DIR=src
INC_DIR=include
HEADERS_DIR=headers
COMMON_INC_DIR=common\\include
BUILD_DIR=build
SOURCE_DIR=source
RAYLIB_DIR=raylib_win64/src

# Convert version strings to comma format for RC file (1.0.0.0 -> 1,0,0,0)
FILE_VERSION_RC=$(echo "$FILE_VERSION" | tr '.' ',')
PRODUCT_VERSION_RC=$(echo "$PRODUCT_VERSION" | tr '.' ',')

# Generate resource file
RC_FILE=$(mktemp --suffix=.rc)
RES_FILE=$(mktemp --suffix=.o)

cat > "$RC_FILE" << EOF
#include <winver.h>

EOF

# Add icon if specified
if [[ -n "$ICON_PATH" && -f "$ICON_PATH" ]]; then
    echo "1 ICON \"$ICON_PATH\"" >> "$RC_FILE"
fi

cat >> "$RC_FILE" << EOF

VS_VERSION_INFO VERSIONINFO
FILEVERSION $FILE_VERSION_RC
PRODUCTVERSION $PRODUCT_VERSION_RC
FILEFLAGSMASK 0x3fL
FILEFLAGS 0x0L
FILEOS VOS__WINDOWS32
FILETYPE VFT_APP
FILESUBTYPE 0x0L
BEGIN
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040904b0"
        BEGIN
            VALUE "FileDescription", "$FILE_DESCRIPTION"
            VALUE "FileVersion", "$FILE_VERSION"
            VALUE "InternalName", "$EXE_NAME"
            VALUE "OriginalFilename", "$EXE_NAME"
            VALUE "ProductName", "$PRODUCT_NAME"
            VALUE "ProductVersion", "$PRODUCT_VERSION"
EOF

if [[ -n "$COMPANY_NAME" ]]; then
    echo "            VALUE \"CompanyName\", \"$COMPANY_NAME\"" >> "$RC_FILE"
fi

if [[ -n "$COPYRIGHT" ]]; then
    echo "            VALUE \"LegalCopyright\", \"$COPYRIGHT\"" >> "$RC_FILE"
fi

cat >> "$RC_FILE" << EOF
        END
    END
    BLOCK "VarFileInfo"
    BEGIN
        VALUE "Translation", 0x409, 1200
    END
END
EOF

# Compile resource file
$WINDRES "$RC_FILE" -o "$RES_FILE"

$CC \
    -std=c++20 \
    -mwindows \
    $SOURCE_DIR/*.cpp \
    $SRC_DIR/*.cpp \
    "$RES_FILE" \
    -I$INC_DIR \
    -I$HEADERS_DIR \
    -I$COMMON_INC_DIR \
    -I$BUILD_DIR \
    -I$RAYLIB_DIR \
    -L$RAYLIB_DIR \
    -lraylib \
    -lopengl32 -lgdi32 -lwinmm \
    -static \
    -o "$EXE_NAME"

# Cleanup temporary files
rm -f "$RC_FILE" "$RES_FILE"

echo "Built: $EXE_NAME"