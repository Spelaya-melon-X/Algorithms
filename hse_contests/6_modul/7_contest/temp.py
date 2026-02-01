

first_player , second_player = 0 ,0 
streak_1 , streak_2 = 0  , 0 
res_1 , res_2 = 0 , 0 
rounds = 0 


while (True)  : 
    s = input().strip()
    if (s == "END") : 
        break 
    rounds+=1 
    
    a ,b = s.split()


    if ( a == b ) : 
        first_player += 1
        streak_2 = 0 
        streak_1 += 1
        res_1 = max(res_1 , streak_1) 


        
    else : 
        second_player+= 1

        streak_2 += 1
        streak_1 = 0 
        res_2 = max(res_2 , streak_2) 

print(f"Rounds: {4}" )
print(f"Score: {first_player}-{second_player}")
if ( first_player == second_player) :
    print("Winner:" , "Draw" )
elif (first_player > second_player) : 
    print("Winner:" , "Player 1" )   
else : 
    print("Winner:" , "Player 2 " )
    
print("Max streak Player 1:" , res_1 )
print("Max streak Player 2:" , res_2 )
    