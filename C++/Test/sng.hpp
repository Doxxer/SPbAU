template <class T> class Singleton {
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

protected:
    Singleton() {};
    Singleton(Singleton const&);
    Singleton& operator=(Singleton const&);
};

class My : public Singleton<My> {
public:
    int x;
};
