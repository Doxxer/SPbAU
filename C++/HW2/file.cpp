#include "file.hpp"
#include <cstdio>

char const *const File::READ = "r";
char const *const File::WRITE = "w";
char const *const File::UPDATE = "r+";

File::File()
    : buffer_size(100), f(0), opened_(false), mode_(File::Read), name_("")
{
}

File::File(std::string const &name, open_mode mode)
    : buffer_size(100), f(0), opened_(false), mode_(mode), name_(name)
{
    open(name_, mode_);
}

File::~File()
{
    close();
}

void File::open(std::string const &name, open_mode mode)
{
    close();
    char const *smode = File::READ;
    mode_ = mode;
    name_ = name;
    switch (mode_) {
        case File::Rewrite:
            smode = File::WRITE;
            break;
        case File::Update:
            smode = File::UPDATE;
            break;
        default:
            break;
    }
    f = fopen(name.c_str(), smode);
    opened_ = f != NULL;
}

bool File::readable() const
{
    return opened_ && !eof() && mode_ == File::Read;
}

bool File::writable() const
{
    return opened_ && (mode_ == File::Rewrite || mode_ == File::Update);
}

int File::read_format(char const *format, void *value)
{
    int res = 0;
    if (readable()) {
        res = fscanf(f, format, value);
        if (res == EOF) res = 0;
    }
    return res;
}

int File::read(std::string &value)
{
    // magic size =(
    char *buffer = new char[buffer_size];
    int res = read_format("%s", buffer);
    if (res) {
        value = std::string(buffer);
    }
    delete[] buffer;
    return res;
}

int File::read(char &value)
{
    return read_format("%c", &value);
}

int File::read(long &value)
{
    return read_format("%ld", &value);
}

int File::read(int &value)
{
    return read_format("%d", &value);
}

int File::read(double &value)
{
    return read_format("%lf", &value);
}

int File::readline(std::string &value)
{
    // magic size again =(
    if (!readable()) return 0;
    char *buffer = new char[buffer_size];
    size_t i = 0;
    for (; i < buffer_size; ++i) {
        char c = fgetc(f); // File::read(char) maybe?
        if (c == '\r' || c == '\n' || c == EOF)
            break;
        else
            buffer[i] = c;
    }
    if (i) value = std::string(buffer);
    delete[] buffer;
    return i;
}

int File::write(int value)
{
    int res = 0;
    if (writable()) {
        res = fprintf(f, "%d", value);
    }
    return res;
}

int File::write(long value)
{
    int res = 0;
    if (writable()) {
        res = fprintf(f, "%ld", value);
    }
    return res;
}

int File::write(double value)
{
    int res = 0;
    if (writable()) {
        res = fprintf(f, "%lf", value);
    }
    return res;
}

int File::write(char value)
{
    int res = 0;
    if (writable()) {
        res = fprintf(f, "%c", value);
    }
    return res;
}

int File::newline()
{
    return write('\n');
}

int File::write(std::string const &str)
{
    int res = 0;
    if (writable()) {
        res = fputs(str.c_str(), f);
    }
    return res;
}

void File::close()
{
    if (opened_) {
        fclose(f);
        opened_ = false;
    }
}

File::open_mode File::mode() const
{
    return mode_;
}

bool File::opened() const
{
    return opened_;
}

int File::eof() const
{
    return f ? feof(f) : 0;
}

int File::error() const
{
    return f ? ferror(f) : 0;
}

std::string File::name() const
{
    return name_;
}
