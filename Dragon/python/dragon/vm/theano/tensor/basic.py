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

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

from dragon import ops as _ops
from dragon.core.tensor import Tensor as _Tensor
from dragon.vm.theano.configdefaults import config as _cfg


def scalar(name=None, dtype=None):
    """Return a scalar variable.

    If dtype is ``None``, use ``config.floatX``.

    Parameters
    ----------
    name : str, optional
        The name of Tensor.
    dtype : str, optional
        The data type of Tensor.

    Return
    ------
    Tensor
        The scalar variable.

    """
    if dtype is None: dtype = _cfg.floatX
    return _Tensor(name=name, dtype=dtype)


def iscalar(name=None):
    """Return a int32 scalar variable.

    Parameters
    ----------
    name : str, optional
        The name of Tensor.

    Return
    ------
    Tensor
        The scalar variable.

    """
    return scalar(name, 'int32')


def zeros(shape, dtype=None):
    """Initialize a tensor with zeros.

    If dtype is *None*, use *config.floatX*.

    Parameters
    ----------
    shape : sequence of int
        The shape of Tensor.
    dtype : str, optional
        The data type of Tensor.

    Returns
    -------
    Tensor
        The initialized tensor.

    """
    if dtype is None: dtype = _cfg.floatX
    return _ops.Fill(shape=shape, value=0, dtype=dtype)


def zeros_like(model, dtype=None, **kwargs):
    """Initialize a tensor with zeros, refer the shape of another tensor.

    The values can be access only after the run of graph.

    If dtype is *None*, use *config.floatX*.

    Parameters
    ----------
    model : Tensor
        The tensor to refer shape.
    dtype : str, optional
        The data type of Tensor.

    Returns
    -------
    Tensor
        The initialized tensor.

    """
    return zeros(shape=model.shape, dtype=dtype)


def ones(shape, dtype=None):
    """Initialize a tensor with ones.

    If dtype is *None*, use *config.floatX*.

    Parameters
    ----------
    shape : sequence of int
        The shape of Tensor.
    dtype : str, optional
        The data type of Tensor.

    Returns
    -------
    Tensor
        The initialized tensor.

    """
    if dtype is None: dtype = _cfg.floatX
    return _ops.Fill(shape=shape, value=1, dtype=dtype)


def ones_like(model, dtype=None, **kwargs):
    """Initialize a tensor with ones, refer the shape of another tensor.

    The values can be access only after the run of graph.

    If dtype is *None*, use *config.floatX*.

    Parameters
    ----------
    model : Tensor
        The tensor to refer shape.
    dtype : str
        The data type of Tensor.

    Returns
    -------
    Tensor
        The initialized tensor.

    """
    return ones(shape=model.shape, dtype=dtype)


def cast(x, dtype):
    """Cast input to the tensor of specific data type.

    If dtype is *None*, use *config.floatX*.

    Parameters
    ----------
    x : Tensor
        The input tensor.
    dtype : str
        The data type.

    Returns
    -------
    Tensor
        The output tensor.

    """
    if dtype is None: dtype = _cfg.floatX
    return x.astype(dtype)


def dot(a, b):
    """Calculate A dot B.

    This operator can trigger ``Matrix Multiplication`` or ``Matrix Vector Multiplication`` also.

    Parameters
    ----------
    a : Tensor
        The input, represents as A.
    b : Tensor
        The input, represents as B.

    Returns
    -------
    Tensor
        The output tensor.

    """
    return _ops.Dot([a, b])


def batched_tensordot(x, y, axes=2):
    raise NotImplementedError()


def transpose(x, axes=None):
    """Transpose the input according to the given permutations.

    Parameters
    ----------
    x : Tensor
        The input tensor.
    axes : sequence of int, optional
        The permutations. Default is ``None`` (Reverse Dimensions).

    Returns
    -------
    Tensor
        The output tensor.

    """
    return _ops.Transpose(x, perm=axes)


def max(x, axis=None, keepdims=False):
    """Compute the values of maximum elements along the given axis.

    Parameters
    ----------
    x : Tensor
        The input tensor.
    axis : int
        The axis to compute. Default is ``None`` (Along all axes).
    keep_dims : boolean
        Whether to keep dims after computing.

    Returns
    -------
    Tensor
        The values.

    """
    if axis is None: axis = -1
    return _ops.Max(x, axis=axis, keep_dims=keepdims)


def min(x, axis=None, keepdims=False):
    """Compute the values of minimum elements along the given axis.

    Parameters
    ----------
    x : Tensor
        The input tensor.
    axis : int
        The axis to compute. Default is ``None`` (Along all axes).
    keep_dims : boolean
        Whether to keep dims after computing.

    Returns
    -------
    Tensor
        The values.

    """
    if axis is None: axis = -1
    return _ops.Min(x, axis=axis, keep_dims=keepdims)


def sum(input, axis=None, keepdims=False, **kwargs):
    """Compute the sum along the given axis.

    Parameters
    ----------
    input : Tensor
        The input tensor.
    axis : int
        The axis to compute. Default is ``None`` (Along all axes).
    keep_dims : boolean
        Whether to keep dims after computing.

    Returns
    -------
    Tensor
        The sum result.

    """
    if axis is None: axis = -1
    return _ops.Sum(input, axis=axis, keep_dims=keepdims)


def mean(input, axis=None, keepdims=False, **kwargs):
    """Compute the mean along the given axis.

    Parameters
    ----------
    input : Tensor
        The input tensor.
    axis : int
        The axis to compute. Default is ``None`` (Along all axes).
    keep_dims : boolean
        Whether to keep dims after computing.

    Returns
    -------
    Tensor
        The mean result.

    """
    if axis is None: axis = -1
    return _ops.Mean(input, axis=axis, keep_dims=keepdims)


def prod(input, axis=None, keepdims=False, **kwargs):
    """Compute the product along the given axis.

    Parameters
    ----------
    input : Tensor
        The input tensor.
    axis : int
        The axis to compute. Default is ``None`` (Along all axes).
    keep_dims : boolean
        Whether to keep dims after computing.

    Returns
    -------
    Tensor
        The product result.

    """
    if axis is None: axis = -1
    raise NotImplementedError()


def argmax(x, axis=None, keepdims=False):
    """Compute the indices of maximum elements along the given axis.

    Parameters
    ----------
    x : Tensor
        The input tensor.
    axis : int
        The axis to compute. Default is ``None`` (Along all axes).
    keep_dims : boolean
        Whether to keep dims after computing.

    Returns
    -------
    Tensor
        The indices.

    """
    if axis is None: axis = -1
    return _ops.ArgMax(x, axis=axis, keep_dims=keepdims)


def argmin(x, axis=None, keepdims=False):
    """Compute the indices of minimum elements along the given axis.

    Parameters
    ----------
    x : Tensor
        The input tensor.
    axis : int
        The axis to compute. Default is ``None`` (Along all axes).
    keep_dims : boolean
        Whether to keep dims after computing.

    Returns
    -------
    Tensor
        The indices.

    """
    if axis is None: axis = -1
    return _ops.ArgMin(x, axis=axis, keep_dims=keepdims)


def square(a):
    """Calculate the square of input.

    Parameters
    ----------
    a : Tensor
        The input tensor.

    Returns
    -------
    Tensor
        The square result.

    """
    return _ops.Square(a)


def sqrt(a):
    """Calculate the sqrt of input.

    Parameters
    ----------
    a : Tensor
        The input tensor.

    Returns
    -------
    Tensor
        The sqrt result.

    """
    return _ops.Sqrt(a)


def pow(a, power):
    """Calculate the power of input.

    Parameters
    ----------
    a : Tensor
        The input tensor.

    Returns
    -------
    Tensor
        The pow result.

    """
    return _ops.Pow(a, power)


def exp(a):
    """Calculate the exponential of input.

    Parameters
    ----------
    a : Tensor
        The input tensor.

    Returns
    -------
    Tensor
        The exponential result.

    """
    return _ops.Exp(a)


def log(a):
    """Calculate the logarithm of input.

    Parameters
    ----------
    a : Tensor
        The input tensor.

    Returns
    -------
    Tensor
        The logarithm result.

    """
    return _ops.Log(a)


def clip(x, min=None, max=None):
    """Clip the input to be between min and max.

    Parameters
    ----------
    x : Tensor
        The input tensor.
    min : number, optional
        The min bound. Default is ``None`` (Ignore).
    max : number, optional
        The max bound. Default is ``None`` (Ignore).

    Returns
    -------
    Tensor
        The clip result.

    """
    return _ops.Clip(x, low=min, high=max)


def join(axis, *tensors_list):
    """Convenience function to concatenate along the given axis.

    Parameters
    ----------
    axis : int
        The axis to concatenate.
    tensor_list : list of Tensor
        The inputs to concatenate.

    Returns
    -------
    Tensor
        The output tensor.

    """
    return _ops.Concat(list(tensors_list), axis=axis)


def stack(*tensors, **kwargs):
    """Stack the inputs along the given axis.

    All dimensions of inputs should be same.

    The ``axis`` can be negative.

    Parameters
    ----------
    tensors : list of Tensor
        The inputs.
    axis : int
        The axis to stack.

    Returns
    -------
    Tensor
        The output tensor.

    """
    if not 'axis' in kwargs: axis = 0
    else: axis = kwargs['axis']
    return _ops.Stack(list(tensors), axis=axis)


def concatenate(tensor_list, axis=0):
    """Concatenate the inputs along the given axis.

    All dimensions except specific ``axis`` should be same.

    Parameters
    ----------
    tensor_list : list of Tensor
        The inputs to concatenate.
    axis : int
        The axis to concatenate.

    Returns
    -------
    Tensor
        The output tensor.

    """
    return _ops.Concat(tensor_list, axis=axis)


def reshape(x, newshape, **kwargs):
    """Reshape the dimensions of input.

    Parameters
    ----------
    x : Tensor
        The input tensor.
    newshape : list or tuple
        The new shape.

    Returns
    -------
    Tensor
        The output tensor.

    """
    return _ops.Reshape(x, shape=newshape)


def flatten(x, outdim=1):
    """Flatten the input by keeping the specific dimensions.

    Parameters
    ----------
    x : Tensor
        The input tensor.
    outdim : int
        The number of dimensions to keep.

    Returns
    -------
    Tensor
        The output tensor.

    """
    return _ops.Flatten(x, keep_axes=outdim)


def repeat(x, repeats, axis=None):
    """Repeat the input along the given axis.

    Parameters
    ----------
    x : Tensor
        The input tensor.
    repeats : int
        The magnitude of repeating.
    axis : int
        The axis to repeat. Defaults is ``-1`` (Repeat as Scalar).

    Returns
    -------
    Tensor
        The output tensor.

    """
    if axis is None: axis = -1
    return _ops.Repeat(x, axis=axis, repeats=repeats)


def tile(x, reps, **kwargs):
    """Tile the input according to the given multiples.

    Parameters
    ----------
    x : Tensor
        The input tensor.
    reps : list of int
        The multiple of each axis.

    Returns
    -------
    Tensor
        The output tensor.

    """
    return _ops.Tile(x, multiples=reps)


def arange(start, stop=None, step=1, dtype=None):
    """Return a vector of elements by arange.

    If ``stop`` is None, use the range: [0, start).

    Parameters
    ----------
    start : int or Tensor
        The start of the range.
    stop : int or Tensor
        The stop of range.
    step : int or Tensor
        The interval between two elements.
    dtype : str
        The data type. ``float32`` or ``int32``.

    Returns
    -------
    Tensor
        The vector.

    """
    return _ops.Arange(start=start, stop=stop, step=step, dtype=dtype)