############################################################
#
# Copyright © 2021 "DrasLorus"
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this
# file and associated documentation files (the “Software”),
# to deal in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all 
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
# CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
# OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
############################################################

open_project -reset max_template
set_top do_max_64
add_files ../sources/modules/max.hpp
add_files ../sources/modules/max.cpp  -cflags "--std=c++14 -Wno-unknown-pragmas -D_MAX_IS_TOP_" 
add_files -tb ../sources/testbenches/max_tb.cpp -cflags "--std=c++14 -Wno-unknown-pragmas -D_MAX_IS_TOP_"
open_solution -reset "solution" -flow_target vivado
set_part {xczu7ev-ffvf1517-3-e}
create_clock -period 10 -name default
config_export -format ip_catalog -rtl verilog
set_directive_top -name do_max_64 "do_max_64"
csim_design -O
csynth_design
cosim_design 
#export_design -flow impl -rtl verilog -format ip_catalog
