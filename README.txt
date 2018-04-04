# Notes for setting up nanopb for small footprint
# protocol buffers which can be used in arduino-class
# micro controller

# 0) Install grpc tooling for python.  This will fetch needed
#    Python dependencies for Google protocol buffers tools.

$> pip install --user grpcio-tools

# 1) download nanopb source code form https://github.com/nanopb/nanopb
#    in a knwon location (like nanopb-src). 

# 2) Next run make to compile proto definition for nanopb 

$> cd nanopb-src/generator/proto
$> make

# 3) Next, define a proto file (see example from repo). Nanopb seems
     to support both protobuf version 2 and 3.

# 4) While in dir with proto files, run the following to

$> protoc \
   --plugin=protoc-gen-nanopb=/Users/vladimir/DEV/tools/nanopb-src/generator/protoc-gen-nanopb \
   --nanopb_out=. *.proto

# If everything compiles ok, the directory will now have *.c and .h files.

# 5) Copy the C files to Arduino's libraries directory.
#    - pb.h
#    - nanopb-src/pb_encode.c, pb_encode.h
#    - nanopb-src/pb_decode.c, pb_decode.h
#    - nanopb-src/pb_common.c, pb_common.h
# Then, copy the generated c files by protoc as well.
