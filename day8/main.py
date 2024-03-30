
moves = ""
def read_file(file_path: str):
    nodes = {}
    moves = ""
    i = 0
    content = ""
    # Open the file in read mode ('r')
    with open(file_path, 'r') as file:
        for line in file:
            if i < 2:
                moves += line.strip()
                
                i += 1
            else:
                content += line.strip() + "\n"
      
    # Now, 'content' contains everything after the second line of 'input.in'
    for c in content.split('\n'):
        if len( c.split(" = ")) > 1:
            nodes[c.split(" =")[0]] = c.split(" = ")[1]

  
    return (nodes,moves)
(content,moves) = read_file('./input.in')

road = ""
current = 0
line  = "AAA"
while(True):
    if current == len(moves):
        current = 0
    next = moves[current]
    current +=1
    (L,R) = content[line].split(', ')
    
    if next == "L":
        line = L.split('(')[1]
        road += "L"
        if "ZZZ" in L:
            break
    else:
        line = R.split(')')[0]
        road += "R"
        if "ZZZ" in R:
            break

print(road)
print("Steps: " + str(len(road)))
