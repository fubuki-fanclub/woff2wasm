const fs = require('fs');
const w2w = require('./cmake-build-wasm/woff2wasm')

setTimeout(() => { //shitty hack instead of awaiting the module load
    const input = fs.readFileSync('r/Roboto-Regular.ttf');

    console.assert(w2w._sizeof_size_t() === 4, "sizeof size_t is not 4");

    const size = input.length;

    console.time('copy to wasm')
    console.log(`[js] Input size: ${size / 1024} KiB`);
    const alloc = w2w._malloc(size);

    console.log(`[js] Allocated buffer: ${alloc / 1024} KiB`);

    const dataOnHeap = new Uint8Array(w2w.HEAPU8.buffer, alloc, size);
    dataOnHeap.set(input);
    console.timeEnd('copy to wasm');

    console.time('convert');
    const r = w2w._convertToWoff(alloc, size);
    console.timeEnd('convert');

    console.time('write to file');
    const returnStatus = new Uint32Array(w2w.HEAPU32.buffer, r, 2);


    const success = returnStatus[0] !== 0, rsize = returnStatus[1];

    if (!success) {
        return;
    }

    console.log(`[js] Output size: ${rsize / 1024} KiB`);

    const outputBuffer = new Uint32Array(w2w.HEAPU32.buffer, r + 4, rsize / 4);

    console.log('[js] Writing output to "out.woff2"');
    fs.writeFileSync("out.woff2", outputBuffer);
    console.timeEnd('write to file');

}, 100);
