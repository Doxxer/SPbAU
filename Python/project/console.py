# coding=utf-8
import threading

import pyglet


class Console(threading.Thread):
    """
    I/O helper
    Thread. Call 'start' to run thread

    Features:
    * read from console (throw action-list dictionary: 'action_list'. See also '__init__' function)
    * _write_force to console ('print' function)

    """

    def __init__(self, action_list, quit_list=None, wrong_input_action=None):
        """
        Initialization of Console class

        @type action_list: dict
        @param wrong_input_action: optional. function, that processes wrong command input.
        @param action_list: key: expression list of aliases. Value: function to call
        @param quit_list: optional.
        """
        super(Console, self).__init__()
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
        self._wrong_input_function = wrong_input_action

    def run(self):
        while not self._stop.isSet():
            # with self._lock:
            cmd = raw_input(">>> ").lower().strip()
            # select([sys.stdin], [], [])
            # cmd = sys.stdin.readline().lower().strip()
            if cmd in self._quit_list:
                self._stop.set()
            else:
                self._parse(cmd)
        pyglet.app.exit()

    def start(self):
        super(Console, self).start()
        pyglet.app.run()
        return self

    def write(self, message, end='\n'):
        with self._lock:
            if message:
                print message

    @property
    def lock(self):
        return self._lock

    def _parse(self, command):
        command = command.split()
        for cnt in range(1, len(command) + 1):
            if self._action_list.get(" ".join(command[:cnt])):
                action = self._action_list.get(" ".join(command[:cnt]))
                try:
                    params = tuple(command[cnt:])
                    action(*params)
                except TypeError as ex:
                    self.write("Incorrect params. Type 'help' to bla-bla-bla...")
                    self.write(ex)
                break
        else:
            if command and self._wrong_input_function:
                self._wrong_input_function()