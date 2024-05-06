#ifndef MIDDLEWARE_OS_FILE_INCLUDE_FSTREAMMIX_HPP_
#define MIDDLEWARE_OS_FILE_INCLUDE_FSTREAMMIX_HPP_

#include <iostream>
#include <fstream>
namespace file_operation
{
class FileBufMix : public std::filebuf
{
public:

protected:
    int_type sync() override
    {
        return std::filebuf::sync();
    };

    std::streamsize xsputn(const char_type *p, std::streamsize n) override
    {
        std::string str;
        for (int i = 0; i < n; i++)
        {
            str.push_back(_mix(*p++));
        }
        return std::filebuf::xsputn(str.c_str(), str.length());
    };

    int_type overflow(int_type c = traits_type::eof()) override
    {
        return std::filebuf::overflow(c);
    };

    int_type underflow() override
    {
        int rc = std::filebuf::underflow();
        char_type *pbuf = eback();
        while (pbuf < egptr())
        {
            *pbuf = _unmix(*pbuf);
            pbuf++;
        }
        return rc;
    }

private:
    char _mix(char c)
    {
        char mix_map[] = {198, 92, 160, 194, 185, 215, 68, 11, 234, 172, 105, 161, 190, 76, 34, 46, 155, 86, 89, 94, 233, 167, 100, 181, 17, 171, 70, 35, 115, 195, 154, 74, 64, 227, 121, 78, 43, 54, 56, 166, 80, 20, 165, 164, 59, 111, 118, 152, 146, 93, 187, 132, 250, 84, 204, 103, 197, 119, 104, 106, 110, 151, 247, 10, 53, 216, 91, 95, 141, 173, 37, 16, 232, 168, 255, 150, 77, 116, 6, 8, 218, 231, 31, 183, 73, 52, 140, 226, 176, 126, 243, 50, 60, 58, 138, 134, 12, 19, 149, 158, 99, 55, 214, 205, 27, 170, 186, 71, 87, 112, 36, 51, 213, 159, 240, 169, 254, 82, 49, 156, 228, 174, 120, 136, 193, 88, 29, 40, 210, 66, 114, 249, 182, 18, 137, 90, 189, 125, 147, 145, 133, 148, 206, 212, 201, 196, 219, 129, 241, 7, 252, 13, 72, 81, 117, 248, 188, 124, 98, 41, 28, 153, 26, 1, 75, 139, 178, 130, 225, 32, 246, 0, 177, 4, 44, 123, 61, 235, 122, 211, 57, 179, 175, 24, 200, 113, 202, 107, 79, 9, 39, 127, 253, 83, 163, 69, 239, 33, 192, 180, 45, 131, 15, 238, 109, 62, 21, 191, 142, 203, 96, 22, 108, 67, 157, 135, 224, 230, 30, 143, 144, 102, 162, 2, 38, 63, 97, 236, 5, 101, 3, 251, 242, 65, 237, 208, 209, 207, 85, 23, 245, 229, 199, 244, 42, 25, 217, 223, 48, 47, 220, 222, 221, 128, 184, 14};
        return mix_map[static_cast<uint8_t>(c)];
    }

    char _unmix(char c)
    {
        char un_mix_map[] = {171, 163, 223, 230, 173, 228, 78, 149, 79, 189, 63, 7, 96, 151, 255, 202, 71, 24, 133, 97, 41, 206, 211, 239, 183, 245, 162, 104, 160, 126, 218, 82, 169, 197, 14, 27, 110, 70, 224, 190, 127, 159, 244, 36, 174, 200, 15, 249, 248, 118, 91, 111, 85, 64, 37, 101, 38, 180, 93, 44, 92, 176, 205, 225, 32, 233, 129, 213, 6, 195, 26, 107, 152, 84, 31, 164, 13, 76, 35, 188, 40, 153, 117, 193, 53, 238, 17, 108, 125, 18, 135, 66, 1, 49, 19, 67, 210, 226, 158, 100, 22, 229, 221, 55, 58, 10, 59, 187, 212, 204, 60, 45, 109, 185, 130, 28, 77, 154, 46, 57, 122, 34, 178, 175, 157, 137, 89, 191, 253, 147, 167, 201, 51, 140, 95, 215, 123, 134, 94, 165, 86, 68, 208, 219, 220, 139, 48, 138, 141, 98, 75, 61, 47, 161, 30, 16, 119, 214, 99, 113, 2, 11, 222, 194, 43, 42, 39, 21, 73, 115, 105, 25, 9, 69, 121, 182, 88, 172, 166, 181, 199, 23, 132, 83, 254, 4, 106, 50, 156, 136, 12, 207, 198, 124, 3, 29, 145, 56, 0, 242, 184, 144, 186, 209, 54, 103, 142, 237, 235, 236, 128, 179, 143, 112, 102, 5, 65, 246, 80, 146, 250, 252, 251, 247, 216, 168, 87, 33, 120, 241, 217, 81, 72, 20, 8, 177, 227, 234, 203, 196, 114, 148, 232, 90, 243, 240, 170, 62, 155, 131, 52, 231, 150, 192, 116, 74};
        return un_mix_map[static_cast<uint8_t>(c)];
    }
};

class IFStreamMix : public std::istream
{
public:
    IFStreamMix() : std::istream(nullptr) { init(&buf_); };
    explicit IFStreamMix(const char *filename, std::ios_base::openmode mode = std::ios_base::in)
        : std::istream(nullptr)
    {
        init(&buf_);
        this->open(filename, mode);
    }

    explicit IFStreamMix(std::string filename, std::ios_base::openmode mode = std::ios_base::in)
        : std::istream(nullptr)
    {
        init(&buf_);
        this->open(filename, mode);
    }

    bool is_open() const { return buf_.is_open(); };

    void close() { buf_.close(); };

    void open(const char *filename, std::ios_base::openmode mode = std::ios_base::in)
    {
        buf_.open(filename, mode);
    };
    void open(std::string filename, std::ios_base::openmode mode = std::ios_base::in)
    {
        buf_.open(filename, mode);
    };

    std::filebuf *rdbuf() { return &buf_; };

private:
    FileBufMix buf_;
};

class OFStreamMix : public std::ostream
{
public:
    OFStreamMix() : std::ostream(nullptr) { init(&buf_); };
    explicit OFStreamMix(const char *filename, std::ios_base::openmode mode = std::ios::out | std::ios::trunc)
        : std::ostream(nullptr)
    {
        init(&buf_);
        this->open(filename, mode);
    }

    explicit OFStreamMix(std::string filename, std::ios_base::openmode mode = std::ios::out | std::ios::trunc)
        : std::ostream(nullptr)
    {
        init(&buf_);
        this->open(filename, mode);
    }

    bool is_open() const { return buf_.is_open(); };

    void close() { buf_.close(); };

    void open(const char *filename, std::ios_base::openmode mode = std::ios::out | std::ios::trunc)
    {
        buf_.open(filename, mode);
    };
    void open(std::string filename, std::ios_base::openmode mode = std::ios::out | std::ios::trunc)
    {
        buf_.open(filename, mode);
    };

    std::filebuf *rdbuf() { return &buf_; };

private:
    FileBufMix buf_;
};

}
using namespace file_operation;

#endif // MIDDLEWARE_OS_FILE_INCLUDE_FSTREAMMIX_HPP_
