# hls_max_template

A max function in C++14 using recursive templates for High-Level Synthesis.

## Content

This repository provides a [header](sources/modules/max.hpp) which defines two recursive template classes with a `process` public method that find the maximum of an array of any size and any type.
`max_template` can be used for all possible sizes while `max_pow2` works only with sizes that are power of 2. `max_struct` is used to implement `max_template` and may not be used directly.

## Usage

something like:

    const T max_array = max_template<SIZE>::process(array);
  
where `T` is a correct type (e.g. `int`, `float`, `ap_uint`, ...), `SIZE` is an unsigned integer known at compile time (e.g. a literal, a constexpr or a preprocessor constant) and `array` is an C-style array of `T` of length `SIZE`.
`max_pow2` is used the same way but won't work (even if it compiles) if `SIZE` is not a power of 2. 

It must be compiled with `--std=c++14` (or `gnu++14` or another equivalent).

## Including

Including the `max.hpp` header is all that is needed to use it in another HLS project.

## Testbench

The prototype of a testbench is provided and the files can be tested with `make testbench`.

## Xilinx® Vitis HLS

A TCL script is provided in [hls_files](hls_files) and can be used with Xilinx® Vitis HLS.
Just do in a shell:
    
    cd hls_files
    vitis_hls -f script.tcl
    
By default, no IP are created. You may need to adjust the part and the clock targeted. 

It as been successfully tested on Vitis HLS version 2020.2 and may or may not work with other versions.
