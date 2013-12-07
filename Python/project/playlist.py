# coding=utf-8
import itertools
import cStringIO
import os


class Playlist(object):
    def __init__(self, player=None, playlist_file=None):
        self._player = player
        self._playlist_file = playlist_file
        self._list = []
        self._order = []
        if self._playlist_file:
            self.load_playlist(self._playlist_file)

        self._play_order_modes = itertools.cycle(['normal', 'shuffle', 'abc'])
        self._play_order_modes_description = {'normal': "как в файле",
                                              'shuffle': "cлучайно",
                                              'abc': "в алфавитном порядке"}
        self._play_order_mode = next(self._play_order_modes)


    @property
    def info(self):
        if not self._init:
            return "Playlist is not initialized!"

        info_string_buffer = cStringIO.StringIO()

        info_string_buffer.write("Порядок воспроизведения: {0}\n".format(self.current_order_mode))

        info_string = info_string_buffer.getvalue()
        info_string_buffer.close()
        return info_string[:-1]

    @property
    def _init(self):
        return self._player and self._playlist_file

    @property
    def current_order_mode(self):
        return self._play_order_modes_description[self._play_order_mode]

    def set_player(self, player):
        self._player = player

    def load_playlist(self, playlist_file):
        self._playlist_file = playlist_file
        with open(playlist_file) as file:
            for song in file.readlines():
                song = song.strip()
                if os.path.isfile(song):
                    self._list.append(song)
        self._init_order()

    def _init_order(self):
        self._order = iter(range(0, len(self._list)))

    def _get_prev_file(self):
        # todo
        pass

    def _get_next_file(self):
        try:
            id_song = next(self._order)
            return self._list[id_song]
        except StopIteration:
            self.stop()

    def next(self):
        if not self._init:
            return False
        s = self._get_next_file()
        if s:
            self._player.play(s)
        return True

    def previous(self):
        if not self._init:
            return False
        self._player.play(self._get_next_file())
        return True

    def toggle_mode(self):
        if not self._init:
            return False
        self._play_order_mode = next(self._play_order_modes)
        return True

    def play(self):
        self._init_order()
        self.next()

    def stop(self):
        self._player.stop()