# coding=utf-8
import threading


class UserInput(threading.Thread):
    """
    Класс, обрабатывающий пользовательский ввод.

    Thread. Call 'start' to run thread

    Features:
    * read from console (throw action-list dictionary: 'action_list'. See also '__init__' function)
    * write to console ('print' function)

    """

    def __init__(self, action_list, quit_list=None, wrong_input_function=None):
        """
        Initialization of UserInput class

        @type action_list: dict
        @param wrong_input_function: optional. function, that processes wrong command input.
        @param action_list: key: expression list of aliases. Value: function to call
        @param quit_list: optional.
        """
        super(UserInput, self).__init__()
        if not quit_list:
            quit_list = ['q', 'quit', 'exit', 'shutdown']

        assert isinstance(action_list, dict)

        self._stop = threading.Event()
        self._quit_list = quit_list
        self._lock = threading.Lock()
        self._action_list = dict()
        for alias_list, function in action_list.iteritems():
            for alias in alias_list:
                self._action_list[alias] = function
        self._wrong_input_function = wrong_input_function

    def run(self):
        while not self._stop.isSet():
            with self._lock:
                cmd = raw_input(">>> ").lower()
            if cmd in self._quit_list:
                self._stop.set()
            else:
                self._parse(cmd)

    def start(self):
        super(UserInput, self).start()
        return self

    def write(self, message):
        if message:
            with self._lock:
                print(message)

    @property
    def lock(self):
        return self._lock

    def _parse(self, command):
        # TODO корректно передать в функцию параметры
        action = self._action_list.get(command)
        if action:
            action()
        elif command and self._wrong_input_function:
            self._wrong_input_function()