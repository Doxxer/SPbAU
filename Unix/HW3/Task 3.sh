#/bin/bash

# 3. CSV to HTML

$ cat csv2html.ss

1i<!DOCTYPE html>\n<html>\n<head>\n\t<title>Phonebook</title>\n</head>\n<body>\n\t<table border=1><tr align=center>\n\t\t<th>First name</th><th>Second name</th><th>Phone number</th></tr>
s/^/\t\t<tr><td>/
s/,/<\/td><td>/g
s/$/<\/td><\/tr>/
$a\\t</table>\n</body>\n</html>


$ sed --file=csv2html.ss input.csv > output.html