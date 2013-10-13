#ifndef __FILE_H__
#define __FILE_H__

#include <string>

class File {
public:
    enum open_mode {
        Read,
        Rewrite,
        Update
    };
    File();
    explicit File(std::string const &fname, open_mode mode = Read);
    ~File();

    void open(std::string const &name, open_mode mode = Read);
    void close();

    open_mode mode() const;
    bool opened() const;
    int eof() const;
    int error() const;
    std::string name() const;

    int write(std::string const &str);
    int write(char value);
    int write(int value);
    int write(long value);
    int write(double value);
    int newline();

    int read(std::string &value);
    int read(char &value);
    int read(long &value);
    int read(int &value);
    int read(double &value);
    int readline(std::string &value);

private:
    size_t const buffer_size;
    static char const *const READ;
    static char const *const WRITE;
    static char const *const UPDATE;
    FILE *f;
    bool opened_;
    open_mode mode_;
    std::string name_;
    File(const File &);
    File &operator=(const File &);
    int read_format(char const *format, void *value);
    bool readable() const;
    bool writable() const;
};
#endif /*__FILE_H__*/
