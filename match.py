
'''
a program that displays 4 words and 4 other words and asks you to tell
it which word in the second set is related to which word in the first
set.
'''

import random

def display_words(words1, words2):
    print("First set of words:")
    for i, word in enumerate(words1, 1):
        print(f"{i}. {word}")
    
    print("\nSecond set of words:")
    for i, word in enumerate(words2, 1):
        print(f"{i}. {word}")

def get_user_input(num_words):
    matches = {}
    for i in range(num_words):
        print(f"\nMatch word {i + 1} from the second set with a word from the first set.")
        first_set_choice = int(input(f"Choose a word from the first set (1-{num_words}): ")) - 1
        second_set_choice = int(input(f"Choose a word from the second set (1-{num_words}): ")) - 1
        matches[second_set_choice] = first_set_choice
    return matches

def main():
    # Define the sets of words
    words1 = ["apple", "dog", "car", "moon"]
    words2 = ["fruit", "animal", "vehicle", "celestial body"]
    
    # Shuffle the second set of words to make it less predictable
    random.shuffle(words2)
    
    # Display the words to the user
    display_words(words1, words2)
    
    # Get matches from the user
    matches = get_user_input(len(words1))
    
    # Display the results
    print("\nYour matches:")
    for second_word_index, first_word_index in matches.items():
        print(f"{words2[second_word_index]} -> {words1[first_word_index]}")
    
    # Check correctness
    correct_matches = {
        "fruit": "apple",
        "animal": "dog",
        "vehicle": "car",
        "celestial body": "moon"
    }
    
    print("\nCorrect matches:")
    for second_word, first_word in correct_matches.items():
        print(f"{second_word} -> {first_word}")

if __name__ == "__main__":
    main()

