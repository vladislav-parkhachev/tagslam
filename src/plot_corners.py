#!/usr/bin/env python3
# -----------------------------------------------------------------------------
# Copyright 2024 Bernd Pfrommer <bernd.pfrommer@gmail.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#
# plot image corners
#
# example usage:
#
# rosrun tagslam plot_corners.py -t 1541778008.167207032 1541778008.217120032 1541778008.316867032
#

import argparse
from os.path import expanduser

import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='plot tag corners')
    parser.add_argument(
        '-t', '--times', nargs='+', help='<Required> ros times to plots', required=True
    )
    parser.add_argument(
        '--cx', '-x', action='store', type=float, default=0, help='principal point u coordinate.'
    )
    parser.add_argument(
        '--cy', '-y', action='store', type=float, default=0, help='principal point v coordinate.'
    )
    parser.add_argument(
        '--file',
        '-f',
        action='store',
        default=expanduser('~') + '/.ros/tag_corners.txt',
        help='file with corners.',
    )
    args = parser.parse_args()

    colors = ['red', 'blue', 'green', 'black', 'purple']
    col = {}
    for i in range(len(args.times)):
        col[float(args.times[i])] = colors[i]

    v = []
    with open(args.file) as file:
        for line in file.readlines():
            arr = line.strip().split(' ')
            if arr[0] in args.times:
                v.append([float(x) for x in arr[0:6]])
    va = np.array(v)

    fig, ax = plt.subplots()
    for i in range(va.shape[0]):
        ax.scatter(va[i, 4] - args.cx, args.cx - va[i, 5], color=col[va[i, 0]])
        ax.annotate(
            '%d:%d:%d' % (int(va[i, 1]), int(va[i, 2]), int(va[i, 3])), (va[i, 4], -va[i, 5])
        )
    ax.set_aspect('equal', adjustable='box')
    plt.show()
