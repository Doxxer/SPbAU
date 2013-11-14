#include "BitFile.hpp"

BitFile::BitFile(std::string BitFileName, Mode mode) : stream_(), mode_(mode)
{
    switch (mode) {
        case Read:
            stream_.open(BitFileName.c_str(), std::ifstream::binary | std::ifstream::in);
            buffer_.reset(-1);
            break;
        case Write:
            stream_.open(BitFileName.c_str(), std::ofstream::binary | std::ofstream::out);
            break;
    }
}

BitFile::~BitFile()
{
    if (mode_ == Write && !buffer_.empty()) {
        flush_buffer();
    }
    stream_.close();
}

uint64_t BitFile::readblock()
{
    uint64_t n = 0;
    for (int i = 0; i < 64; ++i) {
        bool bit = readBit();
        n += (bit << i);
    }
    return n;
}

void BitFile::read(size_t &n)
{
    n = size_t(readblock());
}

bool BitFile::readBit()
{
    if (buffer_.eof())
        buffer_.setChar((unsigned char)(stream_.get()));
    return buffer_.readBit();
}

void BitFile::writeblock(uint64_t n)
{
    int writtenBits = 0;
    while (n) {
        writeBit(n & 1);
        n >>= 1;
        writtenBits++;
    }
    for (; writtenBits < 64; writtenBits++) {
        writeBit(0);
    }
}

void BitFile::write(size_t n)
{
    writeblock(uint64_t(n));
}

void BitFile::writeBit(bool bit)
{
    buffer_.writeBit(bit);
    if (buffer_.eof())
        flush_buffer();
}

void BitFile::flush_buffer()
{
    stream_ << buffer_.getChar();
}

BitFile::Buffer::Buffer() : data_(0), current_position(MAX_POSITION)
{
}

void BitFile::Buffer::writeBit(bool bit)
{
    if (eof())
        reset();
    if (bit)
        data_ |= (1 << current_position);
    current_position--;
}

bool BitFile::Buffer::readBit()
{
    if (eof())
        reset();
    bool result = bool(data_ & (1 << current_position));
    current_position--;
    return result;
}

bool BitFile::Buffer::empty() const
{
    return current_position == MAX_POSITION;
}

bool BitFile::Buffer::eof() const
{
    return current_position < MIN_POSITION;
}

unsigned char BitFile::Buffer::getChar() const
{
    return data_;
}

void BitFile::Buffer::setChar(unsigned char c)
{
    reset();
    data_ = c;
}

void BitFile::Buffer::reset(int position)
{
    current_position = position;
    data_ = 0;
}
