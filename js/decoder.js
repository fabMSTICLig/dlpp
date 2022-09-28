function Decoder(bytes, fPort) {
    var obj = new Object();
    var cursor = 0;
    while (cursor < bytes.length) {
        var index = bytes[cursor];
        obj[index] = [];
        cursor++;
        var signed = (bytes[cursor] & 0x80) != 0;
        var sb = (bytes[cursor] & 0x70) >> 4;
        var len = bytes[cursor] & 0x0F;
        var nb = len / sb;
        cursor++;
        var value = 0;
        while (nb != 0) {
            if (sb == 1) {
                value = bytes[cursor];
                cursor++;
                if (signed && value > 0x80) value - 0x80;
            } else if (sb == 2) {
                value = bytes[cursor];
                cursor++;
                value = (value << 8) + bytes[cursor];
                cursor++;
                if (signed && value > 0x8000) value -= 0x8000;
            } else if (sb == 4) {
                value = bytes[cursor];
                cursor++;
                value = (value << 8) + bytes[cursor];
                cursor++;
                value = (value << 8) + bytes[cursor];
                cursor++;
                value = (value << 8) + bytes[cursor];
                cursor++;
                if (signed && value > 0x80000000) value -= 0x80000000;
            }
            obj[index].push(value);
            nb--;
        }
    }
    return obj;
}

function Decode(fPort, bytes, variables) {
    return Decoder(bytes, fPort)
}
