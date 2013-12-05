import pyglet


class Player(object):
    def __init__(self):
        self._event_loop = pyglet.app.EventLoop()
        self._player = pyglet.media.Player()
        self._player.volume = 0.5

    def set_volume(self, value):
        assert isinstance(value, float)
        assert 0 <= value <= 1
        self._player.volume = value

    def add(self, song):
        source = pyglet.media.load(song)
        self._player.queue(source)

    def play(self):
        if not self._player.playing:
            self._player.play()

    @property
    def playing(self):
        return self._player.playing

    @property
    def volume(self):
        return self._player.volume

    def start(self):
        self._event_loop.run()
        return self

    def pause(self):
        if self._player.playing:
            self._player.pause()