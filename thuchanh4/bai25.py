def push_max(a, value):
    a.append(value)
    i = len(a) - 1
    while i > 0:
        p = (i - 1) // 2
        if a[p] >= a[i]:
            break
        a[p], a[i] = a[i], a[p]
        i = p

def pop_max(a):
    if not a:
        raise ValueError('Đống rỗng')
    result = a[0]
    last = a.pop()
    if not a:
        return result
    a[0] = last
    i = 0
    while 2*i + 1 < len(a):
        left = 2*i + 1
        right = left + 1
        child = left
        if right < len(a) and a[right] > a[left]:
            child = right
        if a[i] >= a[child]:
            break
        a[i], a[child] = a[child], a[i]
        i = child
    return result

a = [20, 9, 15, 3, 7, 1, 2]
c0 = a.copy()
push_max(a, 18)
print('Sau thêm:', a)
c1 = a.copy()
print('Lấy:', pop_max(a), 'còn:', a)
# c2: lấy từ đống ban đầu (con phải 15 > con trái 9)
b = c0.copy()
print('Lấy từ đống ban đầu:', pop_max(b), 'còn:', b)
# ca tự kiểm: con phải lớn hơn con trái → phải chọn con phải
t = [20, 9, 15, 3, 7]
print(pop_max(t), t)
t = [20]; print(pop_max(t), t)
