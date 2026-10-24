function insertion_sort!(A)
    n = length(A)
    for i in 2:n
        key = A[i]
        j = i - 1
        
        while j >= 1 && A[j] > key
            A[j + 1] = A[j]
            j -= 1
        end
        A[j + 1] = key
    end
    return A
end

# Khai báo và chạy thử
A = [8, 3, 5, 1, 9, 2]
insertion_sort!(A)
println("Dãy sau khi sắp xếp: ", A)
