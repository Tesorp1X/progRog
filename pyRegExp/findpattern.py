import re

def appendNewSymbol(pattern, s):
    new_pattern = r""
    for symbol in pattern:
        if symbol == ')':
            break
        new_pattern += symbol
    new_pattern += s + ")+"
    return new_pattern

def pupaAndLupa(line):
    flag = False
    pattern = r"()+"
    #line = input()
    for symbol in line:
        patLength = len(pattern) - 3
        if patLength > (len(line)/2 + 1):
            break
        pattern = appendNewSymbol(pattern, symbol)
        #print("Pattern is ", pattern)
        match = re.fullmatch(pattern, line)
        #print(re.fullmatch(pattern, line))
        if match:
            #print("YES")
            flag = True
            return "YES"
            break
            
        
    if not flag:
        #print("NO")
        return "NO"
    

test = ["abcabcabcabcabc", "abcabcabcfdfsf", "aaaaaaaaaaaaa", "aaaaaaaaaaaaaabbbbaaaaaaaa", "abcabcabcf"]
i = 1
for word in test:
    #pupaAndLupa(word)
    answ = pupaAndLupa(word)
    print("Test no. %d: %s - %s" %(i, word, answ))
    i += 1