using std::cout;
using std::endl;
using std::string;

class BaseHolder {
public:
    virtual ~BaseHolder()
    {
    }
};

template <typename T> class HoldData : public BaseHolder {
public:
    HoldData(T const &data) : data_(data)
    {
    }

    T GetData() const
    {
        return data_;
    }

private:
    T data_;
};

class Variant {
public:
    template <typename T> Variant(T const &t) : data(new HoldData<T>(t))
    {
    }

    template <typename T> operator T()
    {
        typedef HoldData<T> assign_type;
        assign_type &type = dynamic_cast<assign_type &>(*data);
        return type.GetData();
    }

    template <typename T> Variant& operator=(T const& t)
    {
        data = new HoldData<T>(t);
        cout << "11111111111" << endl;
        return *this;
    }

    ~Variant()
    {
        delete data;
    }

private:
    BaseHolder *data;
};
