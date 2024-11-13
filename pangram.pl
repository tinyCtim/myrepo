echo "Blah blah foobar" | perl -e '$/=undef;$_=lc<>;tr/a-z//cd;for(split""){$h{$_}=1};print scalar keys %h'

all my shortest solutions built a set, then compared the set to 26. The
keys of a hashtable act like a set. In this case, lc converts to
lowercase, tr removes all but lowercase letters, split"" converts the
string to an array of one character strings, the for loops fills the
hashtable, and scalar keys %h gets the count of distinct letters in the
hashtable.
