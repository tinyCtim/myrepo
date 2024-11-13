
# https://www.pythonpool.com/generate-random-sentence-in-python/
# 1/18/22 - lrb

from random import randint

names=["woman","turtle","table","amoeba","lamp","friend","tiger","pterodactyl"]
verbs=["swims","elopes","slithers","sucks","blows","outruns","composes","sings"]
adjectives=["big","thin","plump","thick","round","slimy","jealous","smelly"]
adverbs=["slowly","easily","quickly","anxiously","arrogantly","awkwardly","bashfully","moderately"]

print("The "+adjectives[randint(0,len(adjectives)-1)]+" "+names[randint(0,len(names)-1)]+" "\
+adverbs[randint(0,len(adverbs)-1)]+" "+verbs[randint(0,len(verbs)-1)])

