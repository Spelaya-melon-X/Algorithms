import sys

# def main():

# data = sys.stdin.read().strip().split()
# if not data:
# n = int(data[0])
# a = list(map(int, data[1:1 + n]))

n = int(input()) 
a = list(map(int, input().split()))

min_elem ,max_elem  = min(a) , max(a)
q = {}
for x in a:
    q[x] = q.get(x, 0) + 1

resultat = {}
for v, k in q.items():
    if k >= 2:
        resultat[v] = n - k
    else:
        if ( max_elem > v and min_elem < v and n == 3 ):
            resultat[v] = 3
        else:
            resultat[v] = n - 1


ans = []
for x in a : 
    ans.append(str(resultat[x]))
print(' '.join(ans))

# if __name__ == "__main__":
#     main()
    
# #  
# def solve():
#     import sys
#     data = sys.stdin.read().strip().split()
#     if not data:
#         return
#     n = int(data[0])
#     a = list(map(int, data[1:1+n]))
    
#     min_val = min(a)
#     max_val = max(a)
    
#     result = []
#     for x in a:
#         if x == min_val or x == max_val:
#             count_non_x = n - a.count(x)
#             result.append(str(count_non_x))
#         else:
#             result.append(str(n - a.count(x) + 1))
    
#     sys.stdout.write(" ".join(result))

# if __name__ == "__main__":
#     solve()