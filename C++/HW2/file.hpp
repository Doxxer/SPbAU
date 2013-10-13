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

    size_t position() const;

    open_mode mode() const;
    bool opened() const;
    int eof() const;
    int error() const;
    std::string name() const;

    void write(std::string const &str);
    void write(char value);
    void write(int value);
    void write(long value);
    void write(double value);
    void newline();

    void read(std::string &value);
    void read(char &value);
    void read(long &value);
    void read(double &value);
    void readline(std::string &value);

private:
    FILE *file_;
    open_mode mode_;
    std::string name_;

    File(const File &);
    File &operator=(const File &);

    bool readable() const;
    bool writable() const;
};
#endif /*__FILE_H__*/
