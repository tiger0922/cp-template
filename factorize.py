def factorize(num):
    primes = []
    i = 2
    while i*i <= num:
        if num % i == 0:
            primes.append(i)
        while num % i == 0:
            num = num//i
        i += 1
    if num > 1:
        primes.append(num)
    return primes
