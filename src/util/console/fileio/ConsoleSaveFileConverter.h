#pragma once

#include "util/java/File.h"

class ConsoleSaveFile;
class FileEntry;
class ProgressListener;

// 4J Stu - This code is taken from the standalone save converter tool, and
// modified slightly
class ConsoleSaveFileConverter {
private:
    static void ProcessSimpleFile(
        ConsoleSaveFile* sourceSave,
        FileEntry*       sourceFileEntry,
        ConsoleSaveFile* targetSave,
        FileEntry*       targetFileEntry
    );
    static void ProcessStandardRegionFile(
        ConsoleSaveFile* sourceSave,
        File             sourceFile,
        ConsoleSaveFile* targetSave,
        File             targetFile
    );

public:
    static void ConvertSave(
        ConsoleSaveFile*  sourceSave,
        ConsoleSaveFile*  targetSave,
        ProgressListener* progress
    );
};
