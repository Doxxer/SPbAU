#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <fstream>
#include <cstdint>
#include <cstddef>

class BitFile {
public:
    enum Mode {
        Read,
        Write
    };
    explicit BitFile(std::string fileName, Mode mode = Read);
    ~BitFile();

    void read(size_t &n);
    bool readBit();

    void write(size_t n);
    void writeBit(bool bit);

private:
    class Buffer {
    public:
        Buffer();

        void writeBit(bool bit);
        bool readBit();

        bool empty() const;
        bool eof() const;

        unsigned char getChar() const;
        void setChar(unsigned char c);
        void reset(int position = MAX_POSITION);

    private:
        unsigned char data_;
        static int const MIN_POSITION = 0;
        static int const MAX_POSITION = 7;
        int current_position;
    } buffer_;

    std::fstream stream_;
    Mode mode_;

    void flush_buffer();

    void writeblock(uint64_t n);
    uint64_t readblock();
};

#endif /* end of include guard: FILE_HPP */
