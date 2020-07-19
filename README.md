# C++ interface of RTE+RRTMGP

[![Build Status](https://travis-ci.org/earth-system-radiation/rte-rrtmgp-cpp.svg?branch=master)](https://travis-ci.org/earth-system-radiation/rte-rrtmgp-cpp)

This is a C++ interface to the Radiative Transfer for Energetics (RTE)
and Rapid Radiative Transfer Model for GCM applications Parallel (RRTMGP).

The original code is found at https://github.com/earth-system-radiation/rte-rrtmgp.

Contacts: Robert Pincus and Eli Mlawer
email: rrtmgp@aer.com

This C++ interface can be downloaded from https://github.com/earth-system-radiation/rte-rrtmgp-cpp

Contact: Chiel van Heerwaarden
email: chiel.vanheerwaarden@wur.nl

Use and duplication is permitted under the terms of the
BSD 3-clause license, see http://opensource.org/licenses/BSD-3-Clause

The source code of the testing executable in the `src_test` and
`include_test` directory is released under the GPLv3 license,
see https://www.gnu.org/licenses/gpl-3.0.en.html

In order to check out the code including the `rte-rrtmgp` submodule, use:

    git clone --recurse-submodules https://github.com/earth-system-radiation/rte-rrtmgp-cpp

In case you had already checked out the repository, use:

    git submodule update --init


# Basic instructions
Building the source creates an executable `test_rte_rrtmgp`.
Three test cases are provided in directories `rfmip`, `allsky`, and `rcemip`.
In order to run those cases follow the instructions in the `README.md` of those respective directories.

In general, in order to run a test case, make sure the following files are present in the
directory from which `test_rte_rrtmgp` is triggered:
1. Input file `rte_rrtmgp_input.nc` with atmospheric profiles of pressure, temperature, and gases.
2. Long wave coefficients file from original RTE+RRTMGP repository (in `rrtmgp/data`) as `coefficients_lw.nc`
3. Short wave coefficients file from original RTE+RRTMGP repository (in `rrtmgp/data`) as `coefficients_sw.nc`

# Instructions for neural network-based gas optics parametrization
Obtain repository https://github.com/MennoVeerman/machinelearning-gasoptics to generate training data for neural networks, to train neural networks and to generate testing data.
Then run with ./test\_rte\_rrtmgp --nn-gas-optics

