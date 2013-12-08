# coding=utf-8
import itertools
import cStringIO
import os

import random


class PlayerNotInitializedException(Exception):
    def __str__(self):
        return "Ошибка! Плеер не установлен или плейлист пуст"


class PlaylistIsOverException(Exception):
    def __str__(self):
        return "Плейлист кончился..."


class Playlist(object):
    def __init__(self, player=None, playlist_file=None):
        self._player = player
        self._list = []
        self._order = []
        self._current_track = None
        self._order_modes = itertools.cycle(['normal', 'shuffle', 'abc'])
        self._repeat_modes = itertools.cycle(['no', 'all_playlist', 'current_track'])
        self._order_modes_description = {'normal': "как в файле",
                                         'shuffle': "cлучайно",
                                         'abc': "в алфавитном порядке"}
        self._repeat_modes_description = {'current_track': "повторять текущий трек",
                                          'all_playlist': "повторить весь плейлист",
                                          'no': "нет повтора"}
        self._current_order_mode = next(self._order_modes)
        self._current_repeat_mode = next(self._repeat_modes)
        if playlist_file:
            self.load_playlist(playlist_file)

    @property
    def info(self):
        if not self._init:
            return "Playlist is not initialized!"

        info_string_buffer = cStringIO.StringIO()

        info_string_buffer.write("Порядок воспроизведения: {0}\n".format(self.current_order_mode))
        info_string_buffer.write("Режим повтора: {0}\n".format(self.current_repeat_mode))

        info_string = info_string_buffer.getvalue()
        info_string_buffer.close()
        return info_string[:-1]

    @property
    def _init(self):
        return self._player and self._list

    @property
    def current_order_mode(self):
        return self._order_modes_description[self._current_order_mode]

    @property
    def current_repeat_mode(self):
        return self._repeat_modes_description[self._current_repeat_mode]

    def set_player(self, player):
        self._player = player

    def load_playlist(self, playlist_file):
        with open(playlist_file) as plst_file:
            for song in plst_file.readlines():
                song = song.strip()
                if os.path.isfile(song):
                    self._list.append(song)
        self._init_order()

    def _init_order(self):
        def find_current_track():
            if self._current_track:
                while self._current_track != next(self._order):
                    pass

        if self._current_order_mode == 'normal':
            self._order = iter(self._list)
            find_current_track()
        elif self._current_order_mode == 'abc':
            sorted_list = sorted(self._list, key=lambda track: str(track).split("/")[-1])
            self._order = iter(sorted_list)
            find_current_track()
        else:
            shuffled_list = self._list[:]
            if self._current_track and self._current_track in shuffled_list:
                shuffled_list.remove(self._current_track)
            random.shuffle(shuffled_list)
            self._order = iter(shuffled_list)

    def _get_next_file(self):
        try:
            if self._current_repeat_mode == 'current_track':
                if not self._current_track:
                    self._current_track = next(self._order)
                return self._current_track
            self._current_track = None
            self._current_track = next(self._order)
            return self._current_track
        except StopIteration:
            if self._current_repeat_mode == 'all_playlist':
                self._current_track = None
                self._init_order()
                return self._get_next_file()
            else:
                self.stop()
                raise PlaylistIsOverException()

    def next(self):
        if not self._init:
            raise PlayerNotInitializedException()
        next_track = self._get_next_file()
        if next_track:
            self._player.play(next_track)

    def toggle_order_mode(self):
        if not self._init:
            raise PlayerNotInitializedException()
        self._current_order_mode = next(self._order_modes)
        self._init_order()

    def toggle_repeat_mode(self):
        if not self._init:
            raise PlayerNotInitializedException()
        self._current_repeat_mode = next(self._repeat_modes)

    def play(self):
        if not self._init:
            raise PlayerNotInitializedException()
        self._init_order()
        self.next()

    def stop(self):
        if not self._init:
            raise PlayerNotInitializedException()
        self._player.stop()