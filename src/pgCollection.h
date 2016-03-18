/*
Copyright (c) 2014 Bas Timmer/NTAuthority et al.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once

namespace rage {
    template<typename T> class pgCollection {
    private:
        T*			m_pData;
        UINT16		m_pCount;
        UINT16		m_pSize;

    public:
        T* begin() {
            return m_pData;
        }

        T* end() {
            return (m_pData + m_pCount);
        }

        T* at(UINT16 index) {
            return &m_pData[index];
        }
    };

    template<typename T> class pgPtrCollection {
    private:
        T**			m_pData;
        UINT16		m_pCount;
        UINT16		m_pSize;

    public:
        T** begin() {
            return m_pData;
        }

        T** end() {
            return (m_pData + m_pCount);
        }

        T* at(UINT16 index) {
            return m_pData[index];
        }

        UINT16 count() {
            return m_pCount;
        }

        void set(UINT16 index, T* ptr) {
            m_pData[index] = ptr;
        }
    };
}