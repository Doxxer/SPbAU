#!/bin/bash
# 4. Создать файл, содержащий список процессов, начинающихся на r:

ps -Ao comm | grep ^r > processes.txt