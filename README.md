# hls_max_template

An efficient C++14 description of a max process which finds the maximum of a real array.

Used in High Level Synthesis, produce the most efficient maximum possible by doing reduction at compile time.

Currently, it produces log2(*N*) (+1 if *N* is odd) stages of *integer_part(N/2)* comparisons, can be easily unrolled and make use of pipelines.

## Content

This repository provides a [header](sources/modules/max.hpp) which defines two recursive template classes with a `process` public method that find the maximum of an array of any size and any type.
`max_template` can be used for all possible sizes while `max_pow2` works only with sizes that are power of 2. `max_struct` is used to implement `max_template` and may not be used directly.

## Usage

After including the header (with `#include "max.hpp"`), just call the process method like that:

``` C++
const T max_array = max_template<SIZE>::process(array);
```

Where `T` is a comparable class — where operators `<` and `>` are implemented — e.g. `int`, `float` or `ap_uint`, `SIZE` is an unsigned integer known at compile time (e.g. a literal, a `constexpr` or a preprocessor constant) and `array` is a C-style array containing `SIZE` elements `T`.
`max_pow2` is used the same. However, note that it cannot work (even if it compiles) if `SIZE` is not a power of 2. 

It must be compiled with `--std=c++14` (or `gnu++14` or another equivalent).

## Including

Including the `max.hpp` header is all that is needed to use it in another HLS project.

## Testbench

The prototype of a testbench is provided, and the files can be tested with `make testbench`.

## Xilinx® Vitis HLS

A TCL script is provided in [hls_files](hls_files) and can be used with Xilinx® Vitis HLS.
Just do in a shell:

``` sh
cd hls_files
vitis_hls -f script.tcl
```

By default, no IP are created. You may need to adjust the part and the clock targeted. 

It has been successfully tested on Vitis HLS version 2020.2 and may or may not work with other versions.

## Perspectives

A template argument to produce either the current description or a more resources friendly (Higher latency and/or lower throughput) may be added in the future.
Another template argument specifying the most comparisons per stages is also considered.
