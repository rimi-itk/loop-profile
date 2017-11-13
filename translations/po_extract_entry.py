# coding: utf-8

"""Extract entries from GetText (.po) file.

usage:

    print __script__ in.po filter.txt > out.po

- standard input: not used.
- standard output: filtered po file content.
- standard error: filters unmatched.
- arguments: 1) original po file, 2) filters for msgids.
"""


import sys
import argparse
from pathlib import Path

import polib


def main():
    args = get_args()
    po_file = args.po_file
    filter_file = args.filter_file

    validate_file([po_file, filter_file])

    po_filtered = extract_po(po_file, filter_file)

    print(po_filtered)


def get_args():
    """Define and get command line arguments/parameters.
    """
    parser = argparse.ArgumentParser('Extract entries in .po file.')
    parser.add_argument('po_file', help='Source po file.')
    parser.add_argument('filter_file', help='File with filter info.')

    args = parser.parse_args()

    return args


def validate_file(paths):
    """Check if files exist.
    """
    for path in paths:
        p = Path(path)
        if p.exists() and p.is_file():
            continue

        raise FileNotFoundError('File not found: {}'.format(path))


def extract_po(po_file, filter_file):
    """Extract entries whose msgid is in filter from .po file.
    """
    filters = extract_file_lines(filter_file)

    # Look through all entries in po file and pick entries which match filters.
    po = polib.pofile(po_file)
    po_filtered = polib.POFile()

    po_filtered.metadata = po.metadata

    filters_matched = []
    for entry in po:
        if not entry.obsolete:
            if True or entry.msgid in filters:
                po_filtered.append(entry)
                filters_matched.append(entry.msgid)

    # Show all unmatched filters with standard error.
    filters_unmatched = [f for f in filters if not f in filters_matched]
    if filters_unmatched:
        print('Entries not found:', file=sys.stderr)
        print_lines_to_stderr(filters_unmatched)

    return po_filtered


def extract_file_lines(path):
    """Extract all lines in a file.
    """
    with open(path) as f:
        lines = list(map(lambda x: x.strip(), f))
        return lines


def print_lines_to_stderr(lines):
    """Print all lines in a list of string.
    """
    for l in lines:
        print(l, file=sys.stderr)


if __name__ == '__main__':
    main()
