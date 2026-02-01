# import sys

MOD = 10**9 + 7
def compute_dp(lengths):
    m = len(lengths)
    dp = [0] * (m + 1)
    dp[0] = 1
    for L in lengths:
        
        for j in range(m, 0, -1):
            if L - (j - 1) > 0:
                dp[j] = (dp[j] + dp[j-1] * (L - (j - 1))) % MOD
    return dp


# input = sys.stdin.read
# n, k = map(int, input().split())
n ,k  = map(int, input().split())


if k > 2 * n - 2: 
    print(0)
    exit()


len_even_nums , len_odd_nums = [] , []
for i in range(-n + 1, n):
    leng = n - abs(i)
    if i % 2 == 0:
        len_even_nums.append(leng)
    else:
        len_odd_nums.append(leng)


len_even_nums.sort() , len_odd_nums.sort()
dp_1 = compute_dp(len_even_nums) 
dp_2 = compute_dp(len_odd_nums)


resurl = 0
for i in range(k + 1):
    if i < len(dp_1) and k - i < len(dp_2):
        resurl = (resurl + dp_1[i] * dp_2[k - i]) % MOD

print(resurl)

# if __name__ == "__main__":
#     solve()
    
    
    
    
# MOD = 10**9 + 7

# def main():
#     import sys
#     data = sys.stdin.read().strip().split()
#     if not data:
#         return
#     n = int(data[0])
#     k = int(data[1])
    
#     total_diagonals = 2 * n - 1
#     even_lengths = []
#     odd_lengths = []
    
#     for s in range(total_diagonals):
#         if s < n:
#             leng = s + 1
#         else:
#             leng = total_diagonals - s
#         if s % 2 == 0:
#             even_lengths.append(leng)
#         else:
#             odd_lengths.append(leng)
    
#     even_lengths.sort()
#     odd_lengths.sort()
    
#     max_even = min(k, len(even_lengths))
#     max_odd = min(k, len(odd_lengths))
    
#     def compute_ways(lengths, max_j):
#         if max_j < 0:
#             return [1]
#         dp = [0] * (max_j + 1)
#         dp[0] = 1
#         for i, L in enumerate(lengths):
#             upper_bound = min(max_j, i + 1)
#             for j in range(upper_bound, 0, -1):
#                 available = L - (j - 1)
#                 if available <= 0:
#                     continue
#                 dp[j] = (dp[j] + dp[j - 1] * available) % MOD
#         return dp
    
#     ways_even = compute_ways(even_lengths, max_even)
#     ways_odd = compute_ways(odd_lengths, max_odd)
    
#     total = 0
#     start_i = max(0, k - max_odd)
#     end_i = min(k, max_even)
#     for i in range(start_i, end_i + 1):
#         j = k - i
#         if j < 0 or j > max_odd:
#             continue
#         total = (total + ways_even[i] * ways_odd[j]) % MOD
    
#     print(total)

# if __name__ == "__main__":
#     main()
