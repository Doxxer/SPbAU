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
    bool eof() const;
    int error() const;
    std::string name() const;

    // size_t write(char const *buf, size_t size);
    // 	size_t write(std::string const &str);
    // 	size_t write(char value);
    // 	size_t write(long value);
    // 	size_t write(unsigned long value);
    // 	size_t write(double value);
    //
    // 	size_t newline();
    //
    // 	size_t read(char *buf, size_t size);
    // 	size_t read(std::string &word);
    // 	size_t read(char &c);
    // 	size_t read(long &value);
    // 	size_t read(unsigned long &value);
    // 	size_t read(double &value);
    // 	size_t readline(std::string &line);

private:
    static char const *const READ;
    static char const *const WRITE;
    static char const *const UPDATE;
    FILE *f;
    bool opened_;
    bool eof_;
    int error_;
    open_mode mode_;
    std::string name_;
    File(const File &);
    File &operator=(const File &);
};
#endif /*__FILE_H__*/
