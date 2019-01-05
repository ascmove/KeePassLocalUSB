#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>

void copy(char *src, char *dst);

std::ostringstream GetFileTime(HANDLE hFile);

int main() {
    using namespace std;
    char src[100] = "";
    char dst[100] = "";
    ifstream config("config.ini");
    ifstream version("version.ini");
    string temp;
    int verlog;
    int nowver;
    if (!config.is_open()) {
        return 401;
    }
    if (!version.is_open()) {
        return 402;
    }
    while (getline(config, temp)) {
        if (temp.substr(0, 5) == "from=") {
            std::strcpy(src, temp.substr(5).data());
        }
        if (temp.substr(0, 3) == "to=") {
            std::strcpy(dst, temp.substr(3).data());
        }
    }
    config.close();
    while (getline(version, temp)) {}
    verlog = atoi(temp.c_str());
    version.close();

    ifstream in(dst, ios::binary);
    if (!in.is_open()) {
        exit(403);
    } else {
        in.close();
    }

    HANDLE hFile;
    ostringstream LastWriteTime;
    hFile = CreateFile(src, 0, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    LastWriteTime = GetFileTime(hFile);
    if (hFile == INVALID_HANDLE_VALUE) {
        return 404;
    }
    CloseHandle(hFile);
    nowver = atoi(LastWriteTime.str().c_str());
    if (nowver <= verlog) {
        return 200;
    }
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y%m%d%H%M", localtime(&timep));

    char bak[100];
    sprintf_s(bak, "%s%s", dst, tmp);
    copy(dst, bak);
    copy(src, dst);
    ofstream wversion("version.ini", ios::out);
    wversion << nowver;
    wversion.close();
    return 1;
}

std::ostringstream GetFileTime(HANDLE hFile) {
    using namespace std;
    ostringstream LastWriteTime;
    FILETIME ftCreate, ftAccess, ftWrite;
    SYSTEMTIME stUTC1, stLocal1, stUTC2, stLocal2, stUTC3, stLocal3;
    if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)) {
        return LastWriteTime;
    }
    FileTimeToSystemTime(&ftCreate, &stUTC1);
    FileTimeToSystemTime(&ftAccess, &stUTC2);
    FileTimeToSystemTime(&ftWrite, &stUTC3);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC3, &stLocal3);
    LastWriteTime << stLocal3.wYear << stLocal3.wMonth << stLocal3.wDay << stLocal3.wHour << stLocal3.wMinute;
    return LastWriteTime;
}

void copy(char *src, char *dst) {
    using namespace std;
    ifstream in(src, ios::binary);
    ofstream out(dst, ios::binary);
    if (!in.is_open()) {
        exit(501);
    }
    if (!out.is_open()) {
        exit(502);
    }
    if (src == dst) {
        exit(503);
    }
    char buf[2048];
    long long totalBytes = 0;
    while (in) {
        in.read(buf, 2048);
        out.write(buf, in.gcount());
        totalBytes += in.gcount();
    }
    in.close();
    out.close();
}