from node import Node
    
def is_valid(array, x, y):
    if(x >= 0 and x < len(array)):
        if(y >= 0 and y < len(array[x])):
            if(array[x][y] != "#"):
                return True
            else:
                return False
        else:
            return False
    else:
        return False

    
                    

def linked_list(array):
    i = j = 0
    adjacency_list = []

    for lines in array:
        for digit in lines:
            if(digit != "#"):
                head_node = Node(i,j)
                aux_node = head_node

                if(is_valid(array,i-1,j)):
                    new_node = Node(i-1,j)
                    aux_node.set_next(new_node)
                    aux_node = new_node

                if(is_valid(array,i,j-1)):
                    new_node = Node(i,j-1)
                    aux_node.set_next(new_node)
                    aux_node = new_node

                if(is_valid(array,i,j+1)):
                    new_node = Node(i,j+1)
                    aux_node.set_next(new_node)
                    aux_node = new_node

                if(is_valid(array,i+1,j)):
                    new_node = Node(i+1,j)
                    aux_node.set_next(new_node)
                
                adjacency_list.append(head_node)

            j += 1

        i += 1
        j = 0

    return adjacency_list

     

        

            
            



