====================
:mod:`dragon.config`
====================

.. toctree::
   :hidden:

Quick Reference
---------------

===============================    =============================================================================
List                               Brief
===============================    =============================================================================
`EnableCPU`_                       Enable CPU mode globally.
`EnableCUDA`_                      Enable CUDA mode globally.
`SetRandomSeed`_                   Set the global random seed.
`GetRandomSeed`_                   Get the global random seed.
`SetGPU`_                          Set the global id GPU.
`GetGPU`_                          Get the global id of GPU.
`SetGraphOptimizationLevel`_       Set the default level of graph optimization.
`LogMetaGraph`_                    Enable to log meta graph globally.
`LogOptimizedGraph`_               Enable to log optimized graph globally.
`ExportMetaGraph`_                 Enable to export all runnable meta graphs into text files.
`SetLoggingLevel`_                 Set the minimum level of Logging.
`SetLoggingFile`_                  Redirect the logging into the specific file.
===============================    =============================================================================

API Reference
-------------

.. automodule:: dragon.config
    :members:

.. _EnableCPU: #dragon.config.EnableCPU
.. _EnableCUDA: #dragon.config.EnableCUDA
.. _SetRandomSeed: #dragon.config.SetRandomSeed
.. _GetRandomSeed: #dragon.config.GetRandomSeed
.. _SetGPU: #dragon.config.SetGPU
.. _GetGPU: #dragon.config.GetGPU
.. _SetGraphOptimizationLevel: #dragon.config.SetGraphOptimizationLevel
.. _LogMetaGraph: #dragon.config.LogMetaGraph
.. _LogOptimizedGraph: #dragon.config.LogOptimizedGraph
.. _ExportMetaGraph: #dragon.config.ExportMetaGraph
.. _SetLoggingLevel: #dragon.config.SetLoggingLevel
.. _SetLoggingFile: #dragon.config.SetLoggingFile