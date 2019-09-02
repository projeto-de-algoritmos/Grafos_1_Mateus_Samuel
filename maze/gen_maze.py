from mazelib import Maze
from mazelib.generate.BacktrackingGenerator import BacktrackingGenerator

from sys import argv

def main():
    x = int(argv[1])
    y = int(argv[2])
    maze = Maze()
    maze.generator = BacktrackingGenerator(x, y)
    maze.generate()

    aux = maze.tostring().split('\n')
    print(len(aux), len(aux[0]))
    for i, l in enumerate(aux):
        if i == 1:
            print('S' + l[1:])
        elif i == x*2-1:
            print(l[:-1] + 'E')
        else:
            print(l)

if __name__ == '__main__':
    main()
