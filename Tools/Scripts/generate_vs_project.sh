#!/usr/bin/env bash

# Titanium for Windows
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

# This bash script generates Visual Studio 2013 project files using
# CMake. To use it simply run it from any directory where you want
# your VS 2013 project files.
#
# pushd " /cygdrive/c/Users/matt/Documents/build/"
# /cygdrive/c/Users/matt/Documents/GitHub/titanium_mobile_windows/Source/Titanium//generate_vs_project.sh

declare -rx VERBOSE=1

declare -r EXAMPLE_NAME="${1:?}"
declare -r PROJECT_SOURCE_DIR="../../Examples/${EXAMPLE_NAME}"

#declare -r TARGET_PLATFORM_LIST="WindowsStore WindowsPhone"
declare -r TARGET_PLATFORM_LIST="WindowsPhone"
#declare -r TARGET_ARCHITECTURE_LIST="Win32 ARM"
declare -r TARGET_ARCHITECTURE_LIST="ARM"
declare -r CMAKE_GENERATOR_NAME="Visual Studio 12 2013"

# No user-servicable parts below this line.

function cmake_build_cmd {
    local -r target_platform="${1:?}"
    local -r target_architecture="${2:?}"
    
    case "${target_platform}" in
        "WindowsStore")
            ;;
        "WindowsPhone")
            ;;
        *)
            echo "ERROR: Unrecognized target_platform \"${target_platform}\""
            exit 1
            ;;
    esac
    
    local cmake_generator_name="${CMAKE_GENERATOR_NAME}"
    case "${target_architecture}" in
        "Win32")
            ;;
        "ARM")
            cmake_generator_name+=" ${target_architecture}"
            ;;
        *)
            echo "ERROR: Unrecognized target_architecture \"${target_architecture}\""
            exit 1
            ;;
    esac
    
    getScriptAbsoluteDir
    local -r script_absolute_dir="${RESULT}"
    
    normalize_path "${script_absolute_dir}/${PROJECT_SOURCE_DIR}"
    local -r project_source_dir=$(cygpath -m "${RESULT}")
    
    local cmd=""
    cmd=""
    cmd+=" cmake"
    cmd+=" -G \"${cmake_generator_name}\""
    cmd+=" -DCMAKE_SYSTEM_NAME=${target_platform}"
    cmd+=" -DCMAKE_SYSTEM_VERSION=8.1"
    cmd+=" -DTitaniumWindows_DISABLE_TESTS=${OFF}"
    cmd+=" -DTitaniumWindows_Global_DISABLE_TESTS=ON"
    cmd+=" -DTitaniumWindows_API_DISABLE_TESTS=ON"
    cmd+=" -DTitaniumWindows_UI_DISABLE_TESTS=ON"
    cmd+=" -DTitaniumKit_DISABLE_TESTS=ON"
    cmd+=" -DHAL_DISABLE_TESTS=ON"
    cmd+=" \"${project_source_dir}\""
    
    RESULT="${cmd}"
}

function generate_project_files {
    local -r target_platform="${1:?}"
    local -r target_architecture="${2:?}"

    getScriptAbsoluteDir
    local -r script_absolute_dir="${RESULT}"
    
    normalize_path "${script_absolute_dir}/${PROJECT_SOURCE_DIR}"
    local -r project_source_dir=$(cygpath -m "${RESULT}")
    
    local -r project_name=$(grep -E '^\s*project[(][^)]+[)]\s*$' "${project_source_dir}/CMakeLists.txt" | awk 'BEGIN {FS="[()]"} {printf "%s", $2}')
    local -r build_dir="${project_name}.${target_platform}.${target_architecture}"
    
    local cmd=""
    local RESULT=""
    
    cmake_build_cmd "${target_platform}" "${target_architecture}"
    cmd="(time"
    cmd+="${RESULT}"
    cmd+=")"
    # cmd+=" 2>&1 | tee ${LOG_FILE_PATH}"
    
    echo_and_eval "mkdir -p \"${build_dir}\""
    echo_and_eval "pushd \"${build_dir}\""
    
    echo_and_eval "${cmd}"
    echo_and_eval "popd"
}

# @description Normalize the given pathname by removing /./ and
# dir/.. sequences from it. This was found on
# http://www.linuxjournal.com/content/normalizing-path-names-bash
#
# Usage: normalize_path PATH
#
# @param $1 the pathname to normalize
#
function normalize_path() {
    # Remove all /./ sequences.
    local path=${1//\/.\//\/}
    
    # Remove dir/.. sequences.
    while [[ $path =~ ([^/][^/]*/\.\./) ]]
    do
        path=${path/${BASH_REMATCH[0]}/}
    done
    RESULT="$path"
}

# @description Private helper function for the "import" function
# documented below.
#
# @param $1 the script's $0 parameter
#
function getScriptAbsoluteDir {
    local script_invoke_path=$(cygpath -u "${0}")

    # If the first character is not a "/" then it is not an absolute path.
    if ! test "x${script_invoke_path:0:1}" = 'x/'; then
        script_invoke_path="${PWD}/${script_invoke_path}"
    fi
    
    normalize_path "${script_invoke_path}"
    RESULT=$(dirname "${RESULT}")
}

function echo_and_eval {
    local -r cmd="${1:?}"
    echo "${cmd}" && eval "${cmd}"
}

for target_platform in ${TARGET_PLATFORM_LIST}; do
    for target_architecture in ${TARGET_ARCHITECTURE_LIST}; do
        generate_project_files "${target_platform}" "${target_architecture}"
    done
done
