import pyglet


class Player(object):
    def __init__(self, w):
        self._player = pyglet.media.Player()
        self._player.volume = 0.5
        self._player.eos_action = self._player.EOS_STOP
        self._player.push_handlers(on_eos=self._eos)
        self._w = w
        self._is_on = False

    def _eos(self):
        self._is_on = False
        self._w("%%%%%% eos occured!")

    def set_volume(self, value):
        self._player.volume = value

    def add(self, song):
        if self._is_on: return
        self._player.queue(pyglet.media.load(song))
        self._is_on = True
        self._player.play()

    @property
    def playing(self):
        return self._player.playing

    @property
    def volume(self):
        return self._player.volume

    def toggle_pause(self):
        if self._is_on:
            if self._player.playing:
                self._player.pause()
            else: self._player.play()