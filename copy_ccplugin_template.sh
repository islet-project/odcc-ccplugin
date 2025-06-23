#!/usr/bin/env bash

# Copyright (c) 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0

# Safety flags for robust scripting:
# -e : exit immediately if any command exits with a non-zero status (fail fast)
# -u : treat unset variables as an error and exit
# -o pipefail : make pipelines fail if any command in the pipeline fails
# Rationale: fail fast and prevent incomplete/partial copies.
set -euo pipefail

# Source directory to copy from (relative to current working directory)
SRC="./template"

# 0) Validate source directory presence
if [[ ! -d "$SRC" ]]; then
  echo "Error: Source directory not found: $SRC" >&2
  exit 1
fi

# 1) Read destination repo path (argument takes priority; otherwise prompt)
DEST_INPUT="${1:-}"
if [[ -z "${DEST_INPUT}" ]]; then
  read -r -p "Enter destination Git repo path: " DEST_INPUT
fi
if [[ -z "${DEST_INPUT}" ]]; then
  echo "Error: Destination path is empty." >&2
  exit 1
fi

# 2) Expand '~' (only current user's home)
case "$DEST_INPUT" in
  ~*) DEST="${DEST_INPUT/#\~/$HOME}" ;;
  *)  DEST="$DEST_INPUT" ;;
esac

# 2.1) Normalize to absolute paths when possible (linux: coreutils realpath; macOS may not have it)
if command -v realpath >/dev/null 2>&1; then
  DEST="$(realpath -m "$DEST")"
  SRC_ABS="$(realpath -m "$SRC")"
else
  # Fallback: keep as-is (less robust for self-copy detection)
  SRC_ABS="$SRC"
fi

# 3) Validate destination directory
if [[ ! -d "$DEST" ]]; then
  echo "Error: Destination path does not exist or is not a directory: $DEST" >&2
  exit 1
fi

DEST_DIR="$DEST/ccplugin_template"

# 3.1) Guard against copying into itself (same directory) or into a subdir of itself
if command -v realpath >/dev/null 2>&1; then
  DEST_DIR_ABS="$(realpath -m "$DEST_DIR")"
  # Reject same path
  if [[ "$DEST_DIR_ABS" == "$SRC_ABS" ]]; then
    echo "Error: Destination equals source; refusing to copy into itself." >&2
    exit 1
  fi
  # Reject if DEST_DIR is inside SRC (would recurse endlessly)
  case "$DEST_DIR_ABS" in
    "$SRC_ABS"/*)
      echo "Error: Destination resides inside source; refusing to recurse into itself." >&2
      exit 1
      ;;
  esac
fi

# 4) Confirm behavior if target already exists
if [[ -e "$DEST_DIR" ]]; then
  # Important note about behavior: this is a MERGE/overwrite, not a mirror (no deletions).
  read -r -p "Target '$DEST_DIR' already exists. Proceed to merge/overwrite (no deletions)? [y/N] " ans
  case "${ans:-N}" in
    [yY]*) ;;
    *) echo "Aborted by user."; exit 1 ;;
  esac
fi

# 5) Perform copy
#    Prefer rsync for clean exclude and metadata preservation
if command -v rsync >/dev/null 2>&1; then
  mkdir -p "$DEST_DIR"
  # Copy the CONTENTS of $SRC into $DEST_DIR, excluding ONLY the top-level '.find-ignore'
  # The leading slash anchors the pattern to the transfer root (i.e., '$SRC/.find-ignore').
  rsync -a --exclude='/.find-ignore' "$SRC"/ "$DEST_DIR"/
fi

echo "Done: Copied '$SRC' to '$DEST_DIR' (excluded './template/.find-ignore')."
