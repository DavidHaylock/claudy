#!/usr/bin/env bash
set -euo pipefail

VALID_COMMANDS="start attention idle done fail ratelimit danger subagent end"
BAUD=115200
PORT=""
WAIT=0.2

usage() {
  echo "Usage: $(basename "$0") [-p PORT] [-b BAUD] [-w SECONDS] COMMAND" >&2
  echo "  COMMAND: $VALID_COMMANDS" >&2
  echo "  -p PORT     serial device (default: first /dev/cu.usbmodem*)" >&2
  echo "  -b BAUD     baud rate (default: 115200)" >&2
  echo "  -w SECONDS  delay after opening the port before writing (default: 0.3)" >&2
  exit 1
}

while getopts "p:b:w:h" opt; do
  case "$opt" in
    p) PORT="$OPTARG" ;;
    b) BAUD="$OPTARG" ;;
    w) WAIT="$OPTARG" ;;
    h) usage ;;
    *) usage ;;
  esac
done
shift $((OPTIND - 1))

[ $# -eq 1 ] || usage
CMD="$1"

if [[ ! " $VALID_COMMANDS " == *" $CMD "* ]]; then
  echo "Warning: \"$CMD\" isn't one of: $VALID_COMMANDS" >&2
  echo "         (the firmware falls back to \"idle\" for unknown commands)" >&2
fi

if [ -z "$PORT" ]; then
  PORT=$(ls /dev/cu.usbmodem* 2>/dev/null | head -n1 || true)
  if [ -z "$PORT" ]; then
    echo "No /dev/cu.usbmodem* serial port found. Is the board plugged in?" >&2
    echo "Pass one explicitly: $(basename "$0") -p /dev/cu.usbmodemXXXX $CMD" >&2
    exit 1
  fi
fi

if [ ! -e "$PORT" ]; then
  echo "Serial port $PORT does not exist." >&2
  exit 1
fi

stty -f "$PORT" "$BAUD" raw -echo

sleep "$WAIT"

printf '%s\n' "$CMD" > "$PORT"
echo "Sent \"$CMD\" to $PORT"
