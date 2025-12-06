n = int(input())

def play(n, sourse, receiver, storage):
    if n <= 0: return
    play(n-1, sourse, storage, receiver)
    print("Переместите диск с", sourse, "на", receiver)
    play(n-1, storage, receiver, sourse)

play (n, '1', '3', '2')