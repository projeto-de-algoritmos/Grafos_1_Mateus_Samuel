from graph import linked_list
from graph import print_graph

def getinput():
    i=0
    data = list()
    file = open('map.txt')
    for line in file:
        data.append(list(map(list,line.split())))
        data[i] = data[i][0]
        i+=1
    data.pop(0)
    file.close()
    return data


def get_start_end(adjacency_list):
    start = end = i = 0
    for node in adjacency_list:
        if(node.get_value() == "S"):
            start = i
        elif(node.get_value() == "E"):
            end = i
        i += 1
    return [start, end]


def main():
    array = getinput()
    graph = linked_list(array)
    print_graph(graph)

    
if __name__=="__main__":
    main()