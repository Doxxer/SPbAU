class MegaDictionary(dict):
    def __init__(self, denied=None, *args, **kwargs):
        if not denied: denied = []
        super(MegaDictionary, self).__init__(*args, **kwargs)
        self.__dict__["_denied"] = denied
        self.__dict__["_added"] = []

    def __getitem__(self, key):
        try:
            return super(MegaDictionary, self).__getitem__(key)
        except KeyError:
            try:
                return super(MegaDictionary, self).__getitem__(self._added[key])
            except:
                raise KeyError("%s" % key)

    def __setitem__(self, key, value):
        if key in self._denied:
            raise DeniedKeyException()
        super(MegaDictionary, self).__setitem__(key, value)
        if not key in self._added:
            self._added.append(key)

    def __delitem__(self, key):
        super(MegaDictionary, self).__delitem__(key)
        self._added.remove(key)

    def __getattr__(self, name):
        try:
            return self[name]
        except KeyError:
            try:
                return self[name.replace("_", " ")]
            except:
                raise AttributeError("attr %s is not in dictionary" % name)

    def __setattr__(self, name, value):
        self[name] = value


class DeniedKeyException(Exception):
    pass


d = MegaDictionary(["four"], {1: "1", 2: "2"})
d["one"] = 1
d["two"] = 2
d.three = 3
# d.four = 15 // error!
d.five = 5
print(d)
