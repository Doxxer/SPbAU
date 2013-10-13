#include "file.hpp"
#include <cstdio>

char const *const File::READ = "r";
char const *const File::WRITE = "w";
char const *const File::UPDATE = "r+";

File::File()
    : f(0),
      opened_(false),
      eof_(false),
      error_(false),
      mode_(File::Read),
      name_("")
{
}

File::File(std::string const &name, open_mode mode)
    : f(0), opened_(false), eof_(false), error_(false), mode_(mode), name_(name)
{
    open(name_);
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
    error_ = !opened_;
    eof_ = false;
}

void File::close()
{
    error_ = 0;
    if (opened_) {
        error_ = fclose(f);
        opened_ = false;
    }
    eof_ = false;
}

File::open_mode File::mode() const
{
    return mode_;
}

bool File::opened() const
{
    return opened_;
}

bool File::eof() const
{
    return eof_;
}

int File::error() const
{
    return error_;
}

std::string File::name() const
{
    return name_;
}
