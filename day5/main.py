# Function to parse the input file
def parse_input(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
   
    
    # Initializing variables
    seeds = []
    maps = []
    current_map = []

    for line in lines:
        # Splitting the line into words
        words = line.split()

        # Checking for the seeds or map headers
        if 'seeds:' in line:
            seeds = [int(x) for x in words if x.isdigit()]
        elif 'map:' in line:
            if current_map:
                maps.append(current_map)
                current_map = []
        else:
            # Adding rows to the current map
            current_map.append([int(x) for x in words])

    # Adding the last map if it exists
    if current_map:
        maps.append(current_map)

    return seeds, maps

def is_iterable(obj):
    try:
        obj[0]
        return True
    except TypeError:
        return False

def find_intervals(pair1, pair2):
    # Extract start points and lengths
    newstart, start1, length1 = pair1
    start2, length2 = pair2[0]


    # Calculate end points
    end1 = start1 + length1 - 1
    end2 = start2 + length2 - 1

    # Find overlapping interval
    overlap_start = max(start1, start2)
    overlap_end = min(end1, end2)

    # Determine if intervals are overlapping
    if overlap_start <= overlap_end:
        # Overlapping case
        result = []

        # if the second interval is included in the first interval
        if overlap_end == end2:
            if  overlap_start == start2:
                return [(newstart - start1 + start2, length2)]
            else:
                # Add the non-overlapping part
                result.append((start2, length2 - (overlap_end -  overlap_start) - 1))
                # Add the overlapping part
                result.append((overlap_start, overlap_end - overlap_start + 1))
        
                
                return result

        
        # Add the remaining part of the 
        result.append((overlap_end, length2 - (overlap_end -  overlap_start)))
        # Add the overlapping part
        result.append((overlap_start, overlap_end - overlap_start + 1))
        
        return result
    else:
        # print("HERE",pair1,pair2)
        # Non-overlapping case
        return [(pair2)]

def replace_elements(array, index, new_elements):
    # Ensure index is within the range of the array
    if index >= len(array) or index < 0:
        return array  # Return the original array if index is out of bounds

    # Remove the element at the specified index and insert new elements
    return array[:index] + new_elements + array[index+1:]

def print_range_to_map(seed,map):
    
    for step in map:
        if len(step)<2:
            continue
            
        # check if the range is not mapped at all
        result = find_intervals(step,seed)
        #Creating an array of the first elements of each pair
        print("\nStep:",step)
        print("Seeds:",seed," -> ",result)
            
        # Check if there is a difference in the values
        seed = result
        

    # print("Final:",ran)       
    return seed

def WalkTroughMaps(seed,maps):
    for i, map_matrix in enumerate(maps):
        print(f"Map {i+1}:", map_matrix)
        seed = print_range_to_map(seed,map_matrix)
    return seed

# Replace 'input.txt' with the actual path of your file
file_path = 'input.txt' # Update this path as per your file location

# Parsing the input file
seeds, maps = parse_input(file_path)
seeds = [(seeds[i],seeds[i+1]) for i in range(0,len(seeds),2)]

minimum = 99999999999
for seed in seeds:
    result = WalkTroughMaps([seed],maps)
    #Creating an array of the first elements of each pair
    first_elements = [pair[0] for pair in seeds]
    
    minimum = min(minimum,first_elements) 
    print("Minimum:",minimum)

print("FINAL Seeds:",minimum)

