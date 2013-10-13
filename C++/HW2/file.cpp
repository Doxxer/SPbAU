#include "file.hpp"
#include <cstdio>
#include <cstring>

File::File() : file_(NULL), mode_(File::Read), name_("")
{
}

File::File(std::string const &name, open_mode mode)
    : file_(0), mode_(mode), name_(name)
{
    open(name_, mode_);
}

File::~File()
{
    close();
}

int File::position() const
{
    return ftell(file_);
}

void File::open(std::string const &name, open_mode mode)
{
    close();
    mode_ = mode;
    name_ = name;
    switch (mode_) {
        case File::Rewrite:
            file_ = fopen(name.c_str(), "w");
            break;
        case File::Update:
            file_ = fopen(name.c_str(), "r+");
            break;
        default:
            file_ = fopen(name.c_str(), "r");
            break;
    }
}

bool File::readable() const
{
    return opened() && !eof() && mode_ == File::Read;
}

bool File::writable() const
{
    return opened() && (mode_ == File::Rewrite || mode_ == File::Update);
}

void File::read(std::string &value)
{
    if (!readable()) return;

    std::string s;
    char c;
    while ((c = fgetc(file_)) == ' ')
        ;

    s += c;
    c = fgetc(file_);
    while (!eof() && c != ' ' && c != '\r' && c != '\n') {
        s += c;
        c = fgetc(file_);
    }
    value = s;
}

void File::read(char &value)
{
    if (readable()) fscanf(file_, "%c", &value);
}

void File::read(long &value)
{
    if (readable()) fscanf(file_, "%ld", &value);
}

void File::read(int &value)
{
    if (readable()) fscanf(file_, "%d", &value);
}

void File::read(double &value)
{
    if (readable()) fscanf(file_, "%lf", &value);
}

void File::readline(std::string &value)
{
    if (!readable()) return;

    std::string s;
    char c = fgetc(file_);

    while (!eof() && c != '\r' && c != '\n') {
        s += c;
        c = fgetc(file_);
    }
    value = s;
}

void File::write(int value)
{
    if (writable()) fprintf(file_, "%d", value);
}

void File::write(long value)
{
    if (writable()) fprintf(file_, "%ld", value);
}

void File::write(double value)
{
    if (writable()) fprintf(file_, "%lf", value);
}

void File::write(char value)
{
    if (writable()) fprintf(file_, "%c", value);
}

void File::newline()
{
    return write('\n');
}

void File::write(std::string const &str)
{
    if (writable()) fputs(str.c_str(), file_);
}

void File::close()
{
    if (opened()) {
        fclose(file_);
        file_ = NULL;
    }
}

File::open_mode File::mode() const
{
    return mode_;
}

bool File::opened() const
{
    return file_ != NULL;
}

int File::eof() const
{
    return file_ ? feof(file_) : 0;
}

int File::error() const
{
    return file_ ? ferror(file_) : 0;
}

std::string File::name() const
{
    return name_;
}
