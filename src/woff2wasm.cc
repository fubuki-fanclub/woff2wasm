#ifdef FONT_COMPRESSION_DEBUG
#pragma message "FONT_COMPRESSION_DEBUG is defined"
#endif
#include "emscripten.h"
#include "stdio.h"
#include <woff2/encode.h>

using namespace woff2;

constexpr auto sz = sizeof(size_t);

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    int version()
    {
        return 1;
    }

    EMSCRIPTEN_KEEPALIVE
    int sizeof_size_t()
    {
        return sz;
    }

    EMSCRIPTEN_KEEPALIVE
    void free_buffer(uint8_t *buffer)
    {
        free(buffer);
    }

    struct WoffOutput
    {
        bool success;
        uint8_t *buffer;
        size_t size;
    };

    EMSCRIPTEN_KEEPALIVE
    void *convertToWoff(uint8_t *input, size_t size)
    {
        printf("[wasm] input size: %zu\n", size);
        size_t maxSize = MaxWOFF2CompressedSize(input, size);
        printf("[wasm] max size: %zu\n", size);

        auto buffer = (uint8_t *)malloc(maxSize + 2 * sz);

        auto r = ConvertTTFToWOFF2(input, size, buffer + (2 * sz), &maxSize);

        if (!r)
        {
            printf("[wasm] ConvertTTFToWOFF2 failed\n");
        }

        auto bufferAsSizeT = (size_t *)buffer;
        bufferAsSizeT[0] = r;
        bufferAsSizeT[1] = maxSize;

        return buffer;
    }
}