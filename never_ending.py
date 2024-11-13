
'''
written by ChatGPT - examples from French Braid by Anne Tyler
lee bradley - 8/22/24 - for not just tiny-c Programming Group
'''

def play_song(song, times):
    for _ in range(times):
        print(f"Playing: {song}")

def main():
    print("Welcome to the song player!")
    print("Choose a song:")
    print("1. Some people started singing it not knowing what it was, And they'll continue singing it forever just because")
    print("2. This is a song that never ends. Yes, it goes on and on, my friend.")

    try:
        choice = int(input("Enter the number of the song you want (1 or 2): "))
        if choice not in [1, 2]:
            raise ValueError("Invalid choice. Please choose 1 or 2.")
        
        song = "Some people started singing it not knowing what it was, And they'll continue singing it forever just because" if choice == 1 else "This is a song that never ends. Yes, it goes on and on, my friend."

        times = int(input("How many times do you want to play the song? "))
        if times <= 0:
            raise ValueError("Number of times must be greater than 0.")

        play_song(song, times)
    
    except ValueError as e:
        print(f"Error: {e}")
        print("Please enter valid input and try again.")

if __name__ == "__main__":
    main()
