            if (formatFlags & AddLevel)
                str << "a/";
            str << fileData.leftFileInfo.fileName << " and ";
            if (formatFlags & AddLevel)
                str << "b/";
            str << fileData.rightFileInfo.fileName << " differ\n";
            str << "--- ";
            if (formatFlags & AddLevel)
                str << "a/";
            str << fileData.leftFileInfo.fileName << "\n+++ ";
            if (formatFlags & AddLevel)
                str << "b/";
            str << fileData.rightFileInfo.fileName << '\n';
            for (int j = 0; j < fileData.chunks.count(); j++) {
                str << makePatch(fileData.chunks.at(j),
                                      (j == fileData.chunks.count() - 1)
                                      && fileData.lastChunkAtTheEndOfFile);
    const QRegularExpression chunkRegExp(
                // beginning of the line
                "(?:\\n|^)"
                // @@ -leftPos[,leftCount] +rightPos[,rightCount] @@
                "@@ -(\\d+)(?:,\\d+)? \\+(\\d+)(?:,\\d+)? @@"
                // optional hint (e.g. function name)
                "(\\ +[^\\n]*)?"
                // end of line (need to be followed by text line)
                "\\n");
    bool readOk = false;
    QList<ChunkData> chunkDataList;
    QRegularExpressionMatch match = chunkRegExp.match(patch);
    if (match.hasMatch() && match.capturedStart() == 0) {
        int endOfLastChunk = 0;
        do {
            const int pos = match.capturedStart();
            const int leftStartingPos = match.capturedRef(1).toInt();
            const int rightStartingPos = match.capturedRef(2).toInt();
            const QString contextInfo = match.captured(3);
            if (endOfLastChunk > 0) {
                QStringRef lines = patch.mid(endOfLastChunk,
                                             pos - endOfLastChunk);
                chunkDataList.last().rows = readLines(lines,
                                                      false,
                                                      lastChunkAtTheEndOfFile,
                                                      &readOk);
                if (!readOk)
                    break;
            }
            endOfLastChunk = match.capturedEnd();
            ChunkData chunkData;
            chunkData.leftStartingLineNumber = leftStartingPos - 1;
            chunkData.rightStartingLineNumber = rightStartingPos - 1;
            chunkData.contextInfo = contextInfo;
            chunkDataList.append(chunkData);
            match = chunkRegExp.match(patch, endOfLastChunk);
        } while (match.hasMatch());

        if (endOfLastChunk > 0) {
            QStringRef lines = patch.mid(endOfLastChunk);
            chunkDataList.last().rows = readLines(lines,
                                                  true,
                                                  lastChunkAtTheEndOfFile,
                                                  &readOk);
        }
static bool fileNameEnd(const QChar &c)
{
    return c == QLatin1Char('\n') || c == QLatin1Char('\t');
}

static FileData readGitHeaderAndChunks(QStringRef headerAndChunks,
                                       const QString &fileName,
                                       bool *ok)
    FileData fileData;
    fileData.leftFileInfo.fileName = fileName;
    fileData.rightFileInfo.fileName = fileName;
    QStringRef patch = headerAndChunks;
    bool readOk = false;

    const QString devNull(QLatin1String("/dev/null"));

    // will be followed by: index 0000000..shasha, file "a" replaced by "/dev/null", @@ -0,0 +m,n @@
    // new file mode octal
    const QRegularExpression newFileMode("^new file mode \\d+\\n");
    // will be followed by: index shasha..0000000, file "b" replaced by "/dev/null", @@ -m,n +0,0 @@
    // deleted file mode octal
    const QRegularExpression deletedFileMode("^deleted file mode \\d+\\n");

    const QRegularExpression modeChangeRegExp("^old mode \\d+\\nnew mode \\d+\\n");

    // index cap1..cap2(optionally: octal)
    const QRegularExpression indexRegExp("^index (\\w+)\\.{2}(\\w+)(?: \\d+)?(\\n|$)");

    QString leftFileName = QLatin1String("a/") + fileName;
    QString rightFileName = QLatin1String("b/") + fileName;

    const QRegularExpressionMatch newFileMatch = newFileMode.match(patch);
    if (newFileMatch.hasMatch() && newFileMatch.capturedStart() == 0) {
        fileData.fileOperation = FileData::NewFile;
        leftFileName = devNull;
        patch = patch.mid(newFileMatch.capturedEnd());
    } else {
        const QRegularExpressionMatch deletedFileMatch = deletedFileMode.match(patch);
        if (deletedFileMatch.hasMatch() && deletedFileMatch.capturedStart() == 0) {
            fileData.fileOperation = FileData::DeleteFile;
            rightFileName = devNull;
            patch = patch.mid(deletedFileMatch.capturedEnd());
        } else {
            const QRegularExpressionMatch modeChangeMatch = modeChangeRegExp.match(patch);
            if (modeChangeMatch.hasMatch() && modeChangeMatch.capturedStart() == 0) {
                patch = patch.mid(modeChangeMatch.capturedEnd());
            }
        }
    const QRegularExpressionMatch indexMatch = indexRegExp.match(patch);
    if (indexMatch.hasMatch() && indexMatch.capturedStart() == 0) {
        fileData.leftFileInfo.typeInfo = indexMatch.captured(1);
        fileData.rightFileInfo.typeInfo = indexMatch.captured(2);

        patch = patch.mid(indexMatch.capturedEnd());
    const QString binaryLine = QString::fromLatin1("Binary files ") + leftFileName
            + QLatin1String(" and ") + rightFileName + QLatin1String(" differ");
    const QString leftStart = QString::fromLatin1("--- ") + leftFileName;
    QChar leftFollow = patch.count() > leftStart.count() ? patch.at(leftStart.count()) : QLatin1Char('\n');
    // empty or followed either by leftFileRegExp or by binaryRegExp
    if (patch.isEmpty() && (fileData.fileOperation == FileData::NewFile
                         || fileData.fileOperation == FileData::DeleteFile)) {
        readOk = true;
    } else if (patch.startsWith(leftStart) && fileNameEnd(leftFollow)) {
        patch = patch.mid(patch.indexOf(QLatin1Char('\n'), leftStart.count()) + 1);
        const QString rightStart = QString::fromLatin1("+++ ") + rightFileName;
        QChar rightFollow = patch.count() > rightStart.count() ? patch.at(rightStart.count()) : QLatin1Char('\n');
        // followed by rightFileRegExp
        if (patch.startsWith(rightStart) && fileNameEnd(rightFollow)) {
            patch = patch.mid(patch.indexOf(QLatin1Char('\n'), rightStart.count()) + 1);
            fileData.chunks = readChunks(patch,
                                         &fileData.lastChunkAtTheEndOfFile,
                                         &readOk);
        }
    } else if (patch == binaryLine) {
        readOk = true;
        fileData.binaryFiles = true;
    }
    if (ok)
        *ok = readOk;
    if (!readOk)
        return FileData();
    return fileData;
static FileData readCopyRenameChunks(QStringRef copyRenameChunks,
                                     FileData::FileOperation fileOperation,
                                     const QString &leftFileName,
                                     const QString &rightFileName,
                                     bool *ok)
    FileData fileData;
    fileData.fileOperation = fileOperation;
    fileData.leftFileInfo.fileName = leftFileName;
    fileData.rightFileInfo.fileName = rightFileName;
    QStringRef patch = copyRenameChunks;
    bool readOk = false;
    // index cap1..cap2(optionally: octal)
    const QRegularExpression indexRegExp("^index (\\w+)\\.{2}(\\w+)(?: \\d+)?(\\n|$)");
    if (fileOperation == FileData::CopyFile || fileOperation == FileData::RenameFile) {
        const QRegularExpressionMatch indexMatch = indexRegExp.match(patch);
        if (indexMatch.hasMatch() && indexMatch.capturedStart() == 0) {
            fileData.leftFileInfo.typeInfo = indexMatch.captured(1);
            fileData.rightFileInfo.typeInfo = indexMatch.captured(2);
            patch = patch.mid(indexMatch.capturedEnd());
            const QString leftStart = QString::fromLatin1("--- a/") + leftFileName;
            QChar leftFollow = patch.count() > leftStart.count() ? patch.at(leftStart.count()) : QLatin1Char('\n');
            // followed by leftFileRegExp
            if (patch.startsWith(leftStart) && fileNameEnd(leftFollow)) {
                patch = patch.mid(patch.indexOf(QLatin1Char('\n'), leftStart.count()) + 1);
                // followed by rightFileRegExp
                const QString rightStart = QString::fromLatin1("+++ b/") + rightFileName;
                QChar rightFollow = patch.count() > rightStart.count() ? patch.at(rightStart.count()) : QLatin1Char('\n');
                // followed by rightFileRegExp
                if (patch.startsWith(rightStart) && fileNameEnd(rightFollow)) {
                    patch = patch.mid(patch.indexOf(QLatin1Char('\n'), rightStart.count()) + 1);
                    fileData.chunks = readChunks(patch,
                                                 &fileData.lastChunkAtTheEndOfFile,
                                                 &readOk);
                }
            }
        } else if (copyRenameChunks.isEmpty()) {
            readOk = true;
        }
    }
    if (ok)
        *ok = readOk;
    if (!readOk)
        return FileData();
    return fileData;
    const QRegularExpression simpleGitRegExp(
          "^diff --git a/([^\\n]+) b/\\1\\n" // diff --git a/cap1 b/cap1
          , QRegularExpression::MultilineOption);
    const QRegularExpression similarityRegExp(
          "^diff --git a/([^\\n]+) b/([^\\n]+)\\n" // diff --git a/cap1 b/cap2
          "(?:dis)?similarity index \\d{1,3}%\\n"  // similarity / dissimilarity index xxx% (100% max)
          "(copy|rename) from \\1\\n"              // copy / rename from cap1
          "\\3 to \\2\\n"                          // copy / rename (cap3) to cap2
          , QRegularExpression::MultilineOption);
    bool readOk = false;
    QList<FileData> fileDataList;
    bool simpleGitMatched;
    int pos = 0;
    QRegularExpressionMatch simpleGitMatch = simpleGitRegExp.match(patch);
    QRegularExpressionMatch similarityMatch = similarityRegExp.match(patch);
    auto calculateGitMatchAndPosition = [&]() {
        if (pos > 0) { // don't advance in the initial call
            if (simpleGitMatch.hasMatch() && similarityMatch.hasMatch()) {
                const int simpleGitPos = simpleGitMatch.capturedStart();
                const int similarityPos = similarityMatch.capturedStart();
                if (simpleGitPos <= similarityPos)
                    simpleGitMatch = simpleGitRegExp.match(patch, simpleGitMatch.capturedEnd() - 1); // advance only simpleGit
                else
                    similarityMatch = similarityRegExp.match(patch, similarityMatch.capturedEnd() - 1); // advance only similarity
            } else if (simpleGitMatch.hasMatch()) {
                simpleGitMatch = simpleGitRegExp.match(patch, simpleGitMatch.capturedEnd() - 1);
            } else if (similarityMatch.hasMatch()) {
                similarityMatch = similarityRegExp.match(patch, similarityMatch.capturedEnd() - 1);
            }
        }
        if (simpleGitMatch.hasMatch() && similarityMatch.hasMatch()) {
            const int simpleGitPos = simpleGitMatch.capturedStart();
            const int similarityPos = similarityMatch.capturedStart();
            pos = qMin(simpleGitPos, similarityPos);
            simpleGitMatched = (pos == simpleGitPos);
            return;
        }
        if (simpleGitMatch.hasMatch()) {
            pos = simpleGitMatch.capturedStart();
            simpleGitMatched = true;
            return;
        }
        if (similarityMatch.hasMatch()) {
            pos = similarityMatch.capturedStart();
            simpleGitMatched = false;
            return;
        }
        pos = -1;
        simpleGitMatched = true;
    };
    // Set both pos and simpleGitMatched according to the first match:
    calculateGitMatchAndPosition();
    if (pos >= 0) { // git style patch
        readOk = true;
        int endOfLastHeader = 0;
        QString lastLeftFileName;
        QString lastRightFileName;
        FileData::FileOperation lastOperation = FileData::ChangeFile;

        auto collectFileData = [&]() {
            if (endOfLastHeader > 0 && readOk) {
                const int end = pos < 0 ? patch.count() : pos;
                QStringRef headerAndChunks = patch.mid(endOfLastHeader,
                                                       qMax(end - endOfLastHeader - 1, 0));

                FileData fileData;
                if (lastOperation == FileData::ChangeFile) {
                    fileData = readGitHeaderAndChunks(headerAndChunks,
                                                      lastLeftFileName,
                                                      &readOk);
                } else {
                    fileData = readCopyRenameChunks(headerAndChunks,
                                                    lastOperation,
                                                    lastLeftFileName,
                                                    lastRightFileName,
                                                    &readOk);
                }
                if (readOk)
                    fileDataList.append(fileData);
            }
        };
        do {
            if (jobController && jobController->isCanceled())
            collectFileData();
            if (!readOk)
                break;
            if (simpleGitMatched) {
                const QString fileName = simpleGitMatch.captured(1);
                pos = simpleGitMatch.capturedEnd();
                lastLeftFileName = fileName;
                lastRightFileName = fileName;
                lastOperation = FileData::ChangeFile;
            } else {
                lastLeftFileName = similarityMatch.captured(1);
                lastRightFileName = similarityMatch.captured(2);
                const QString operation = similarityMatch.captured(3);
                pos = similarityMatch.capturedEnd();
                if (operation == QLatin1String("copy"))
                    lastOperation = FileData::CopyFile;
                else if (operation == QLatin1String("rename"))
                    lastOperation = FileData::RenameFile;
                else
                    break; // either copy or rename, otherwise broken
            }
            endOfLastHeader = pos;

            // give both pos and simpleGitMatched a new value for the next match
            calculateGitMatchAndPosition();
        } while (pos != -1);
        if (readOk)
            collectFileData();