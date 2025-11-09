// very good overall, could be better, let's talk

def calc_numbers(num_count, sum, last_added):
    print(sum)
    sum += last_added
    last_added = sum - last_added
    if num_count > 0:
        num_count -= 1
        calc_numbers(num_count, sum, last_added)

def main():
    num_count = int(input("enter how many fibonnaci numbers you want to get: "))
    sum = 1
    last_added = 0
    calc_numbers(num_count, sum, last_added)
        

if __name__ == "__main__":
    main()
