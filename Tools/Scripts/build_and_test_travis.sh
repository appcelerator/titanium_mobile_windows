#!/usr/bin/env bash

# Titanium for Windows
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

set -e

declare -r project_source_dir="${1:?}"

if ! test -d "${project_source_dir}"; then
    echo "Project does not exist at ${project_source_dir}."
    exit 1
fi

# No user-servicable parts below this line.

declare -r APPCELERATOR_S3_BASE_URL="http://s3.amazonaws.com/timobile.appcelerator.com"
declare -r GTEST_ZIP_OSX_DOWNLOAD_URL="${APPCELERATOR_S3_BASE_URL}/gtest-1.7.0-osx.zip"

# Normalize the given pathname by removing /./ and dir/.. sequences
# from it. This was found on
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

# Return the absolute path of this bash script.
#
# @param $1 the script's $0 parameter
#
function get_script_absolute_dir {
    local script_invoke_path="${0}"
  
    # If the first character is not a "/" then it is not an absolute path.
    if ! test "x${script_invoke_path:0:1}" = 'x/'; then
    script_invoke_path="${PWD}/${script_invoke_path}"
    fi
  
  normalize_path "${script_invoke_path}"
    RESULT=$(dirname "${RESULT}")
}

get_script_absolute_dir
declare -r script_absolute_dir="${RESULT}"
declare -r BUILD_DIR="${script_absolute_dir}/build"

# All downloads and build artifacts occur within the BUILD_DIR
# directory.
mkdir -p "${BUILD_DIR}"
pushd "${BUILD_DIR}"

function echo_and_eval {
    #local -r cmd="${1:?}"
    cmd="${1:?}"
    echo "${cmd}" && eval "${cmd}"
}

# This function downloads an archive (e.g. .tar.gz, .zip, etc.) from a
# remote server, extracts it into the cwd, and then returns the full
# path to the extract directory in the global RESULT variable.
function download_and_extract {
    local -r DOWNLOAD_URL="${1:?}"
    local -r FILE_NAME=$(basename "${DOWNLOAD_URL}")
    
    # If required, download the file.
    if ! test -f "${FILE_NAME}"; then
        cmd="curl -sS -# -O \"${DOWNLOAD_URL}\""
        echo_and_eval "${cmd}"
    else
        echo "Skip download of \"${FILE_NAME}\" because it is already downloaded."
    fi
    
    # Get the name of the directory that the archive expands to.
    local -r extract_dir=$(tar -tf "${FILE_NAME}" | head -n1 | awk 'BEGIN {FS="/"} {print $1}')
  
    # If required, extract the archive.
    if ! test -d "${extract_dir}"; then
        cmd="tar xvf \"${FILE_NAME}\""
    echo "${cmd} (this could take a while...)"
    local -r elapsed_time=$((time -p echo_and_eval "${cmd}") 2>&1 >/dev/null | awk '/^real/ {print $2}')
    echo "extraction took ${elapsed_time} seconds"
    else
        echo "Skip extract of \"${FILE_NAME}\" because it is already extracted to \"${extract_dir}\"."
    fi
  
    RESULT="${PWD}/${extract_dir}"
}

# This function installs the OSX version of Google Test.
function setup_gtest {
    echo ""
    echo "########################################################################"
    echo "Setup Google Test"
    echo "########################################################################"
    
  if ! test -d "${GTEST_ROOT}"; then
    download_and_extract "${GTEST_ZIP_OSX_DOWNLOAD_URL}"
    export GTEST_ROOT="${RESULT}"
  fi
  
  echo "GTEST_ROOT=${GTEST_ROOT}"
}

echo ""
echo "########################################################################"
echo "Build and Test ${project_name}"
echo "########################################################################"

echo_and_eval "pushd \"${project_source_dir}\""
echo_and_eval "setup_gtest"
echo_and_eval "./build_and_test.sh"
echo_and_eval "popd"
