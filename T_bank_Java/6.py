
# ОК
import sys

# def main():
data = sys.stdin.read().split()
iterator = iter(data)
n,q ,s  = int(next(iterator)) , int(next(iterator)),next(iterator)

opers , itog_out = [] ,  []

for i in range(q):
    t = int(next(iterator))
    if t == 1:
        l,r = int(next(iterator)) , int(next(iterator))
        opers.append((l, r))
    else:
        i = int(next(iterator))
        position = i
        
        for l, r in reversed(opers):
            len_op = r - l + 1
            if position < l:
                continue
            elif position >= l + 2 * len_op:
                position -= len_op
            else:
                position = l + (position - l) // 2
        itog_out.append(s[position - 1])  

sys.stdout.write('\n'.join(itog_out))

# if __name__ == "__main__":
#     main()

# import sys

# def main():
#     data = sys.stdin.read().split()
#     if not data:
#         return
#     n = int(data[0])
#     q = int(data[1])
#     s = data[2].strip()
    
#     ops = []
#     current_len = n
#     index = 3
#     output_lines = []
    
#     for _ in range(q):
#         t = int(data[index]); index += 1
#         if t == 1:
#             l = int(data[index]); r = int(data[index+1]); index += 2
#             len_sub = r - l + 1
#             ops.append((l, r, len_sub, current_len))
#             current_len += len_sub
#         else:
#             i_val = int(data[index]); index += 1
#             cur = i_val
#             for j in range(len(ops)-1, -1, -1):
#                 if cur <= n:
#                     break
#                 l, r, len_sub, prev_len = ops[j]
#                 total_after = prev_len + len_sub
#                 if cur > total_after:
#                     continue
#                 if cur < l:
#                     pass
#                 elif cur < l + 2 * len_sub:
#                     offset = cur - l
#                     cur = l + (offset // 2)
#                 else:
#                     cur = cur - len_sub
#             output_lines.append(s[cur-1])
    
#     sys.stdout.write("\n".join(output_lines))

# if __name__ == "__main__":
#     main()