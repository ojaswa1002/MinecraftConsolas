#include "InputStream.h"

#include "util/java/File.h"

#include "FileInputStream.h"

InputStream* InputStream::getResourceAsStream(const std::wstring& fileName) {
    return new FileInputStream(File(fileName));
}
