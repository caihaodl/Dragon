# ------------------------------------------------------------
# Copyright (c) 2017-present, SeetaTech, Co.,Ltd.
#
# Licensed under the BSD 2-Clause License.
# You should have received a copy of the BSD 2-Clause License
# along with the software. If not, See,
#
#      <https://opensource.org/licenses/BSD-2-Clause>
#
# ------------------------------------------------------------

"""Define the common thread local structures."""

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import threading
import contextlib


class Constant(threading.local):
    def __init__(self, **attrs):
        super(Constant, self).__init__()
        self.__dict__.update(attrs)


class Stack(threading.local):
    def __init__(self):
        super(Stack, self).__init__()
        self._enforce_nesting = True
        self.stack = []

    def get_default(self):
        return self.stack[-1] if len(self.stack) >= 1 else None

    def reset(self):
        self.stack = []

    def is_cleared(self):
        return not self.stack

    @property
    def enforce_nesting(self):
        return self._enforce_nesting

    @enforce_nesting.setter
    def enforce_nesting(self, value):
        self._enforce_nesting = value

    @contextlib.contextmanager
    def get_controller(self, default):
        """A context manager for manipulating a default stack."""
        self.stack.append(default)
        try:
            yield default
        finally:
            # stack may be empty if reset() was called
            if self.stack:
                if self._enforce_nesting:
                    if self.stack[-1] is not default:
                        raise AssertionError(
                            "Nesting violated for default stack of %s objects" %
                            type(default))
                    self.stack.pop()
                else:
                    self.stack.remove(default)