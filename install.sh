#!/usr/bin/env bash

clear 

# detecting the Operating System (Linux or MacOS)
# and the number of physical cores

KERNEL_NAME=$(uname -s)

case "$KERNEL_NAME" in 

    *Linux*)
        OS_TYPE='Linux'
        NUMBER_PHYSICAL_CORES=$(lscpu -p=core | grep -v '^#' | sort -u | wc -l)
        ARCH_TYPE=$(uname -m)
        CPU_FLAGS=$(lscpu)
        ;;

    *Darwin*)
        OS_TYPE='MacOS'
        NUMBER_PHYSICAL_CORES=$(sysctl -n hw.physicalcpu)
        ARCH_TYPE=$(uname -m)
        CPU_FLAGS=$(sysctl -a)
        ;;
    *)
        echo " Unsupported Operating System"
        echo " Operating System found : $KERNEL_NAME"
        exit 1
        ;;
esac

# CPU architecture (logical abstraction)

case "$ARCH_TYPE" in
    x86_64|amd64)
        CPU_ARCH="x86"
        ;;
    arm64|aarch64)
        CPU_ARCH="ARM"
        ;;
    *)
        echo " Unsupported CPU architecture: $ARCH_TYPE"
        exit 1
        ;;
esac

# Single Instruction Multiple Data (SIMD) flags

# Initialization
HAS_SSE=false
HAS_AVX2=false
HAS_FMA=false
HAS_AVX512F=false
HAS_AVX512FMA=false
HAS_ASIMD=false
HAS_ARMV8=false
HAS_X86=false

if [ "$CPU_ARCH" = "x86" ]; then
    HAS_X86=true
    echo "$CPU_FLAGS" | grep -qi sse      && HAS_SSE=true
    echo "$CPU_FLAGS" | grep -qi avx2      && HAS_AVX2=true
    echo "$CPU_FLAGS" | grep -qi fma      && HAS_FMA=true
    echo "$CPU_FLAGS" | grep -qi avx512f  && HAS_AVX512F=true
fi

if [ "$CPU_ARCH" = "ARM" ]; then
    HAS_ARMV8=true
    echo "$CPU_FLAGS" | grep -qiE 'asimd|neon' && HAS_ASIMD=true
fi

# Reject ARMv7 or older
if [ "$CPU_ARCH" = "ARM" ] && [ "$ARCH_TYPE" != "aarch64" ] && [ "$ARCH_TYPE" != "arm64" ]; then
    echo "ERROR: ARMv7 or older is not supported. ARMv8+ (aarch64) required."
    exit 1
fi


set -e

if [ ! -d "build" ]
# case of a NON-existing build folder
then 
    meson setup build --prefix="$PWD" \
                      --buildtype=debug \
                      -DNUMBER_PHYSICAL_CORES="$NUMBER_PHYSICAL_CORES" \
                      -DHAS_SSE="$HAS_SSE" \
                      -DHAS_AVX2="$HAS_AVX2" \
                      -DHAS_FMA="$HAS_FMA" \
                      -DHAS_AVX512F="$HAS_AVX512F" \
                      -DHAS_AVX512FMA="$HAS_AVX512FMA" \
                      -DHAS_ARMV8="$HAS_ARMV8" \
                      -DHAS_X86="$HAS_X86" \
                      -DHAS_ASIMD="$HAS_ASIMD" \
                      || exit 1
else
# when the folder build already exists
    meson setup --reconfigure build \
                --prefix="$PWD" \
                --buildtype=debug \
                -DNUMBER_PHYSICAL_CORES="$NUMBER_PHYSICAL_CORES" \
                -DHAS_SSE="$HAS_SSE" \
                -DHAS_AVX2="$HAS_AVX2" \
                -DHAS_FMA="$HAS_FMA" \
                -DHAS_AVX512F="$HAS_AVX512F" \
                -DHAS_AVX512FMA="$HAS_AVX512FMA" \
                -DHAS_ARMV8="$HAS_ARMV8" \
                -DHAS_X86="$HAS_X86" \
                -DHAS_ASIMD="$HAS_ASIMD" \
                || exit 1
fi

echo " "
echo " --- project configuration..."
echo " "
echo "      CPU architecture         : $ARCH_TYPE"
echo "      Operating System found   : $OS_TYPE"
echo "      Number of physical cores : $NUMBER_PHYSICAL_CORES"
echo " "
echo " --- compiling..."
echo " "
meson compile -C build
echo " "
echo " --- the solver is installed in $PWD/bin/ "
echo " "
meson install -C build
echo " "
echo " --- Installation completed. the GAP-solver is ready!"
echo " "