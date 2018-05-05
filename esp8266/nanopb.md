# Nanopb

Nanopb is a procol buffers compiler plugin to generate lightweight C which can be loaded and run on small resource constrained devices.

The followings are notes for setting up nanopb for small footprint protocol buffers which can be used in micro controllers using the Arduino core libraries or any environment capable of running C code.

> Read about Nanopb - https://github.com/nanopb/nanopb

## Installation

1) Install the *gRPC* tooling for python.  This will automatically fetch needed Python dependencies for Google protocol buffers used by Nanopb .

```shell
$> pip install --user grpcio-tools
```

2) Clone the nanopb source code form https://github.com/nanopb/nanopb
into a knwon location (say `nanopb-src`).  Instead of compiling the nanopb binary, we will use the protoc plugin.

## Compiling proto files

Define a proto file in an arbitrary location. 

>Nanopb seems to support both protobuf version 2 and 3.

While still in the directory with the proto files, run the following command to compile the proto IDL into C code:

```shell
$> protoc \
   --plugin=protoc-gen-nanopb=/Users/someuser/nanopb-src/generator/protoc-gen-nanopb \
   --nanopb_out=. *.proto
```

The previous command uses the nanopb protoc plugin by specifying its full path where it was cloned (above).  Make sure to use a fully-qualified path and not a relative path for the plugin.

## Deploy to Aurduino library

If protoc works ok, the directory (from above) will now have `.c` and `.h` files. To use these files in your code, you must add them,  and other C files that come with nanopb, to Arduino's library directory (usually located somewhere like `/Documents/Arduino/libraries/<your-own-library-directory>`)

### Copy generate protobufs C and header files

Copy the generated C and header files to Arduino's library directory.

### Copy nanopb C and header files

Besides the generated C files above, you will also need to copy the nanopb libraries into the Arduino library directory (see above).  These files are found in the cloned directory of nanopb location:
 
   - `pb.h`
   - `nanopb-src/pb_encode.c, pb_encode.h`
   - `nanopb-src/pb_decode.c, pb_decode.h`
   - `nanopb-src/pb_common.c, pb_common.h`

Now, you should see the library listed in Arduino's `Include library` menu.