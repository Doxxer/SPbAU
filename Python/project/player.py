# coding=utf-8
import cStringIO
import pyglet
from pyglet.media import SourceInfo
from utilities import sec_to_time


class Player(object):
    def __init__(self, on_sound_end=None):
        self._on_sound_end = on_sound_end
        self._current_file = None
        self._audio_player = None
        self._current_source = None
        self._is_alive = False
        self._volume = 1
        self._invalidate_player()

    def _invalidate_player(self):
        if self._audio_player:
            self._audio_player.remove_handlers()
            self._audio_player.pause()
        self._audio_player = pyglet.media.Player()
        self.set_volume(100)
        self._audio_player.eos_action = self._audio_player.EOS_STOP
        self._audio_player.push_handlers(on_eos=self._on_eos)
        self._is_alive = False

    def _on_eos(self):
        self._is_alive = False
        if self._on_sound_end:
            self._on_sound_end()

    @property
    def info(self):
        if not self._is_alive:
            return "Shhhh! Player is sleeping now..."

        source_info = self._audio_player.source.info
        assert isinstance(source_info, SourceInfo)

        info_string_buffer = cStringIO.StringIO()
        if self._current_file:
            info_string_buffer.write("Имя файла: {0}\n".format(self._current_file))

        song_title = source_info.title if source_info.title else 'Unknown title'
        info_string_buffer.write(
            "Название песни: {0} ({1})\n".format(song_title, sec_to_time(self._audio_player.source.duration)))
        if source_info.author:
            info_string_buffer.write("Автор: {0}\n".format(source_info.author))

        info_string_buffer.write(
            "{0} / {1}\n".format(sec_to_time(self._audio_player.time), sec_to_time(self._audio_player.source.duration)))

        if source_info.album:
            info_string_buffer.write("Альбом: {0}".format(source_info.album))
            if source_info.year:
                info_string_buffer.write(" ({0})".format(source_info.year))
            info_string_buffer.write("\n".format(source_info.year))

        if source_info.track:
            info_string_buffer.write("Трек: {0}\n".format(source_info.track))
        if source_info.genre:
            info_string_buffer.write("Жанр: {0}\n".format(source_info.genre))

        info_string = info_string_buffer.getvalue()
        info_string_buffer.close()

        return info_string[:-1]

    def set_volume(self, value):
        self._volume = value
        self._audio_player.volume = self._volume / 100.0

    def stop(self):
        self._invalidate_player()

    def play(self, song):
        self._invalidate_player()
        self._current_file = song
        self._current_source = pyglet.media.load(song)
        self._audio_player.queue(self._current_source)
        self._is_alive = True
        self._audio_player.play()

    @property
    def playing(self):
        return self._audio_player.playing

    @property
    def volume(self):
        return self._volume

    def toggle_pause(self):
        if self._is_alive:
            if self._audio_player.playing:
                self._audio_player.pause()
            else:
                self._audio_player.play()
            return True
        else:
            return False