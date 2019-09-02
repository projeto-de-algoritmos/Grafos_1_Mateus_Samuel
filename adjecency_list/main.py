from graph import linked_list

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


def main():
    array = getinput()
    graph = linked_list(array)
    

if __name__=="__main__":
    main()