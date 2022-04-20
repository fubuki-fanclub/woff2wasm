cmake_minimum_required(VERSION 3.22)

project(woff2wasm)

# ???
include_directories(woff2wasm include brotli/c/include )

# muh performance
set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_C_FLAGS "-O3")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# i love 900 column lines
add_executable(woff2wasm src/woff2wasm.cc src/table_tags.cc src/woff2_dec.cc src/transform.cc src/glyph.cc src/font.cc src/woff2_common.cc src/variable_length.cc src/woff2_out.cc src/woff2_enc.cc src/normalize.cc brotli/c/common/transform.c brotli/c/common/dictionary.c brotli/c/dec/huffman.c brotli/c/dec/bit_reader.c brotli/c/dec/state.c brotli/c/dec/decode.c brotli/c/fuzz/decode_fuzzer.cc brotli/c/enc/utf8_util.c brotli/c/enc/compress_fragment_two_pass.c brotli/c/enc/block_splitter.c brotli/c/enc/literal_cost.c brotli/c/enc/backward_references_hq.c brotli/c/enc/memory.c brotli/c/enc/encoder_dict.c brotli/c/enc/entropy_encode.c brotli/c/enc/cluster.c brotli/c/enc/metablock.c brotli/c/enc/encode.c brotli/c/enc/brotli_bit_stream.c brotli/c/enc/compress_fragment.c brotli/c/enc/dictionary_hash.c brotli/c/enc/static_dict.c brotli/c/enc/histogram.c brotli/c/enc/backward_references.c brotli/c/enc/bit_cost.c)
# ???
set_target_properties(woff2wasm PROPERTIES LINK_FLAGS "-s ALLOW_MEMORY_GROWTH=1 -s WASM=1 -s EXPORTED_RUNTIME_METHODS='[\"cwrap\"]'")
