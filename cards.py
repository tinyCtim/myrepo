import random

def shuffle_deck():
    ranks = ['2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A']
    suits = ['Hearts', 'Diamonds', 'Clubs', 'Spades']
    deck = [{'rank': rank, 'suit': suit} for rank in ranks for suit in suits]
    random.shuffle(deck)
    return deck

def draw_cards(deck):
    drawn_cards = set()
    required_ranks = set(['2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A'])
    required_suits = set(['Hearts', 'Diamonds', 'Clubs', 'Spades'])
    drawn_ranks = set()
    drawn_suits = set()
    num_drawn_cards = 0

    while drawn_ranks != required_ranks or drawn_suits != required_suits:
        card = deck.pop()
        print(card) #lrb
        num_drawn_cards += 1
        drawn_cards.add((card['rank'], card['suit']))
        drawn_ranks.add(card['rank'])
        drawn_suits.add(card['suit'])

    return num_drawn_cards, drawn_cards

# Shuffle the deck
shuffled_deck = shuffle_deck()

# Draw cards until all ranks and suits are present
num_drawn_cards, drawn_cards = draw_cards(shuffled_deck)

# Print the result
print("Number of cards drawn:", num_drawn_cards)

