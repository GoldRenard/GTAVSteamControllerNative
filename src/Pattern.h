#pragma once

struct PatternByte {
    PatternByte() : ignore(true) {
        //
    }

    PatternByte(std::string byteString, bool ignoreThis = false) {
        data = StringToUint8(byteString);
        ignore = ignoreThis;
    }

    bool ignore;
    UINT8 data;

private:
    UINT8 StringToUint8(std::string str) {
        std::istringstream iss(str);

        UINT32 ret;

        if (iss >> std::hex >> ret) {
            return (UINT8) ret;
        }

        return 0;
    }
};

struct Pattern {
    static DWORD64 Scan(DWORD64 dwStart, DWORD64 dwLength, std::string s) {
        std::vector<PatternByte> p;
        std::istringstream iss(s);
        std::string w;

        while (iss >> w) {
            if (w.data()[0] == '?') { // Wildcard
                p.push_back(PatternByte());
            }
            else if (w.length() == 2 && isxdigit(w.data()[0]) && isxdigit(w.data()[1])) { // Hex
                p.push_back(PatternByte(w));
            }
            else {
                return NULL; // You dun fucked up
            }
        }

        for (DWORD64 i = 0; i < dwLength; i++) {
            UINT8* lpCurrentByte = (UINT8*) (dwStart + i);

            bool found = true;

            for (size_t ps = 0; ps < p.size(); ps++) {
                if (p[ps].ignore == false && lpCurrentByte[ps] != p[ps].data) {
                    found = false;
                    break;
                }
            }

            if (found) {
                return (DWORD64) lpCurrentByte;
            }
        }

        return NULL;
    }

    static DWORD64 Scan(MODULEINFO mi, std::string s) {
        return Scan((DWORD64) mi.lpBaseOfDll, (DWORD64) mi.SizeOfImage, s);
    }
};