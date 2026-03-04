#pragma once

#include "util/console/ArrayWithLength.h"
class CompoundTag;
class DataInput;
class DataOutput;
class InputStream;
class OutputStream;

class NbtIo {
public:
    static CompoundTag* readCompressed(InputStream* in);
    static void         writeCompressed(CompoundTag* tag, OutputStream* out);
    static CompoundTag* decompress(byteArray buffer);
    static byteArray    compress(CompoundTag* tag);
    static CompoundTag* read(DataInput* dis);
    static void         write(CompoundTag* tag, DataOutput* dos);
};
