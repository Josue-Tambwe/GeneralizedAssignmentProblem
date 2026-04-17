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


set -e

if [ ! -d "build" ]
# case of a NON-existing build folder
then 
    meson setup build --prefix="$PWD" \
                      --buildtype=debug \
                      -DNUMBER_PHYSICAL_CORES="$NUMBER_PHYSICAL_CORES" \
                      || exit 1
else
# when the folder build already exists
    meson setup --reconfigure build \
                --prefix="$PWD" \
                --buildtype=debug \
                -DNUMBER_PHYSICAL_CORES="$NUMBER_PHYSICAL_CORES" \
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