#!/usr/bin/python3

from random import randint

#function to roll single die and adjust tokens between players/center
def roll(player_index, player_scores, player_count):
	x = randint(1,6)
	if x < 4:
		die = '\tRoll: DOT'
	elif x == 4:
		die = '\tRoll: L'
		player_scores[player_index] -= 1 
		player_scores[(player_index + 1) % player_count] += 1
	elif x == 5:
		die = '\tRoll: R'
		player_scores[player_index] -= 1 
		player_scores[player_index - 1] += 1
	elif x == 6:
		die = '\tRoll: C'
		player_scores[player_index] -= 1 
	else:
		die = 'ERROR'
	print(die)
	return player_scores

#Introduction
print("We are going to play dots (aka LCR or Left Center Right)!")
num_players = input("How many players are playing today? ")

#Create lists for player names and scores
player_names = []
player_scores = []
player_count = 0
plays = 0 # lrb

#loop to allow users to enter player names, add to list, 
for player_count in range(int(num_players)):
	name = input("Enter Player " + str(player_count + 1) + "'s name (surround in quotes) : ")
	name = name.title()
	player_names.append(name)
	player_scores.append(3)
	player_count += 1

print("\nAll players have been entered, let's play!")

#while loop until all but one player has no tokens
while player_scores.count(0) < (player_count-1):
	player_index = 0
	#while loop to go through players in order
	while player_index < player_count:
		#if to determine if someone on previous roll ended game
		if player_scores.count(0) == (player_count-1):
			break
		#elifs to determine how many rolls
		elif player_scores[player_index] == 0:
			print(player_names[player_index] + " is skipped")
		elif player_scores[player_index] >= 3:
			print(player_names[player_index] + " gets to roll 3 dice with " + str(player_scores[player_index]) + " tokens.")
			for roll_count in range(3):
				roll(player_index, player_scores, player_count)
		elif player_scores[player_index] == 2:
			print(player_names[player_index] + " gets to roll 2 dice")
			for roll_count in range(player_scores[player_index]):
				roll(player_index, player_scores, player_count)
		elif player_scores[player_index] == 1:
			print(player_names[player_index] + " gets to roll 1 die")
			for roll_count in range(player_scores[player_index]):
				roll(player_index, player_scores, player_count)
		else:
			print("ERROR")

		player_index += 1
		plays += 1 #lrb

winner_index = 0
#finding the winner 
while winner_index < player_count:
	if player_scores[winner_index] > 0:
		winner = player_names[winner_index]
		break
	winner_index += 1
	
print("\n")
print("Contratulations " + winner + " has won DOTS!")
print("It took " + str(plays) + " plays.") #lrb
